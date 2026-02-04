#pragma once

#include <pybind11/pybind11.h>
#include <stdexcept>

template<class T> class ConstListWrapper
{
public:
    const T* list;
    size_t size;

    explicit ConstListWrapper(const T* list, size_t size)
        : list(list)
        , size(size)
    {
    }

    const T get(size_t index)
    {
        if(index < size)
        {
            return list[index];
        }

        throw std::runtime_error("List index out of bounds");
    }

    size_t len()
    {
        return size;
    }

    pybind11::iterator makeIterator()
    {
        return pybind11::make_iterator(list, list + size);
    }
};

template<class T>
void initConstListWrapper(pybind11::module& m, const char* name)
{
    try
    {
        pybind11::class_<ConstListWrapper<T>>(m, name)
            .def("__getitem__", &ConstListWrapper<T>::get)
            .def("__len__", &ConstListWrapper<T>::len)
            .def("__iter__", &ConstListWrapper<T>::makeIterator);
    }
    catch(...)
    {
        // PASS
        // Silently ignore this if it errors
        // Stops errors if ListWrappers are defined more than once
    }
}

template<class T> class ListWrapper
{
public:
    T* list;
    size_t size;

    explicit ListWrapper(T* list, size_t size)
        : list(list)
        , size(size)
    {
    }

    const T get(size_t index)
    {
        if(index < size)
        {
            return list[index];
        }

        throw std::runtime_error("List index out of bounds");
    }

    const void set(size_t index, const T& val)
    {
        if(index < size)
        {
            list[index] = val;
        }
        else
        {
            throw py::index_error();
        }
    }

    size_t len()
    {
        return size;
    }

    pybind11::iterator makeIterator()
    {
        return pybind11::make_iterator(list, list + size);
    }
};

template<class T> void initListWrapper(pybind11::module& m, const char* name)
{
    try
    {
        pybind11::class_<ListWrapper<T>>(m, name)
            .def("__getitem__", &ListWrapper<T>::get)
            .def("__len__", &ListWrapper<T>::len)
            .def("__iter__", &ListWrapper<T>::makeIterator)
            .def("__setitem__", &ListWrapper<T>::set);
    }
    catch(...)
    {
        // PASS
        // Silently ignore this if it errors
        // Stops errors if ListWrappers are defined more than once
    }
}