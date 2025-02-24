#pragma once

#include <pybind11/pybind11.h>
#include <stdexcept>

template<class T> class ListWrapper
{
public:
    const T* list;
    size_t size;

    explicit ListWrapper(const T* list, size_t size)
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

template<class T> void initListWrapper(pybind11::module& m, const char* name)
{
    try
    {
        pybind11::class_<ListWrapper<T>>(m, name)
            .def("__getitem__", &ListWrapper<T>::get)
            .def("__len__", &ListWrapper<T>::len)
            .def("__iter__", &ListWrapper<T>::makeIterator);
    }
    catch(...)
    {
        // PASS
        // Silently ignore this if it errors
        // Stops errors if ListWrappers are defined more than once
    }
}