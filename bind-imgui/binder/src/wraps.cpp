#include <binder/inc/bind-modules.h>
#include <binder/inc/wraps.h>
#include <pybind11/stl.h>
#include <sstream>

namespace py = pybind11;

StrRef_::StrRef_(size_t maxSize)
    : ImList<char>(std::vector<char>(maxSize + 1))
{
    // Set first char to zero to terminate string
    vals[0] = 0;
}

StrRef_::StrRef_(const char* val, size_t maxSize)
    : ImList<char>(std::vector<char>())
{
    if(maxSize == 0)
    {
        maxSize = std::strlen(val);
    }
    vals.resize(maxSize + 1);
    std::strncpy(vals.data(), val, maxSize);
}

void StrRef_::set(const char* newVal, size_t maxSize)
{
    vals.resize(maxSize + 1);
    std::strncpy(vals.data(), newVal, maxSize);
}

void StrRef_::resize(size_t maxSize)
{
    size_t oldSize = vals.size() - 1;
    vals.resize(maxSize + 1);

    // If we shrunk
    if(maxSize < oldSize)
    {
        // Make sure the str is null terminated
        vals[maxSize] = '\0';
    }
}

size_t StrRef_::strSize()
{
    return vals.size() - 1;
}

void init_wraps(py::module& m)
{
    py::class_<BoolRef_>(m, "BoolRef", "A pass-by-ref wrapper for a bool")
        .def(py::init<bool>(), "val"_a = false)
        .def_readwrite("val", &BoolRef_::val, "The wrapped value")
        .def("__str__", &BoolRef_::toStr);

    py::class_<FloatRef_>(m, "FloatRef", "A pass-by-ref wrapper for a float")
        .def(py::init<float>(), "val"_a = 0.0)
        .def_readwrite("val", &FloatRef_::val, "The wrapped value")
        .def("__str__", &FloatRef_::toStr);

    py::class_<IntRef_>(m, "IntRef", "A pass-by-ref wrapper for an int")
        .def(py::init<int>(), "val"_a = 0)
        .def_readwrite("val", &IntRef_::val, "The wrapped value")
        .def("__str__", &IntRef_::toStr);

    py::class_<IntList_>(m, "IntList", "Thin wrapper over a std::vector<int>")
        .def(py::init<std::vector<int>>(), "vals"_a = std::vector<int>())
        .def("append", &IntList_::append, "val"_a, "Append a value to the end")
        .def("pop", &IntList_::pop, "Pop a value from the end")
        .def(
            "resize",
            &IntList_::resize,
            "size"_a,
            "Resize the vector, dropping any lost values"
        )
        .def("__len__", &IntList_::size)
        .def("__iter__", &IntList_::makeIter)
        .def("__getitem__", &IntList_::getItem, "index"_a)
        .def("__setitem__", &IntList_::setItem, "index"_a, "val"_a);

    py::class_<FloatList_>(m, "FloatList", "Thin wrapper over a std::vector<float>")
        .def(py::init<std::vector<float>>(), "vals"_a = std::vector<float>())
        .def("append", &FloatList_::append, "val"_a, "Append a value to the end")
        .def("pop", &FloatList_::pop, "Pop a value from the end")
        .def(
            "resize",
            &FloatList_::resize,
            "size"_a,
            "Resize the vector, dropping any lost values"
        )
        .def("__len__", &FloatList_::size)
        .def("__iter__", &FloatList_::makeIter)
        .def("__getitem__", &FloatList_::getItem, "index"_a)
        .def("__setitem__", &FloatList_::setItem, "index"_a, "val"_a);

    py::class_<DoubleList_>(
        m,
        "DoubleList",
        "Thin wrapper over a std::vector<double>"
    )
        .def(py::init<std::vector<double>>(), "vals"_a = std::vector<double>())
        .def("append", &DoubleList_::append, "val"_a, "Append a value to the end")
        .def("pop", &DoubleList_::pop, "Pop a value from the end")
        .def(
            "resize",
            &DoubleList_::resize,
            "size"_a,
            "Resize the vector, dropping any lost values"
        )
        .def("__len__", &DoubleList_::size)
        .def("__iter__", &DoubleList_::makeIter)
        .def("__getitem__", &DoubleList_::getItem, "index"_a)
        .def("__setitem__", &DoubleList_::setItem, "index"_a, "val"_a);

    py::class_<StrList_>(
        m,
        "StrList",
        "Thin wrapper over a std::vector<const char*>"
    )
        .def(
            py::init<std::vector<const char*>>(),
            "vals"_a = std::vector<const char*>()
        )
        .def("append", &StrList_::append, "val"_a, "Append a value to the end")
        .def("pop", &StrList_::pop, "Pop a value from the end")
        .def(
            "resize",
            &StrList_::resize,
            "size"_a,
            "Resize the vector, dropping any lost values"
        )
        .def("__len__", &StrList_::size)
        .def("__iter__", &StrList_::makeIter)
        .def("__getitem__", &StrList_::getItem, "index"_a)
        .def("__setitem__", &StrList_::setItem, "index"_a, "val"_a);

    py::class_<StrRef_>(m, "StrRef", "Thin wrapper over a std::vector<char>")
        .def(
            py::init<size_t>(),
            "maxSize"_a,
            "Initialize an empty string with reserved size"
        )
        .def(
            py::init<const char*, size_t>(),
            "value"_a,
            "maxSize"_a = 0,
            "Initialize with an input string. If maxSize=0, then "
            "maxSize=len(val)"
        )
        .def("append", &StrRef_::append, "val"_a, "Append a value to the end")
        .def("pop", &StrRef_::pop, "Pop a value from the end")
        .def(
            "resize",
            &StrRef_::resize,
            "size"_a,
            "Resize the vector, dropping any lost values"
        )
        .def("__len__", &StrRef_::strSize)
        .def("__str__", &StrRef_::data, py::return_value_policy::copy)
        .def(
            "copy",
            &StrRef_::data,
            py::return_value_policy::copy,
            "Get a copy of the string"
        )
        .def(
            "view",
            &StrRef_::data,
            py::return_value_policy::reference,
            "Get a reference to the string, only valid while this object exists"
        )
        .def(
            "set",
            &StrRef_::set,
            "newVal"_a,
            "maxSize"_a = 0,
            "Assign a new value to the string. If maxSize=0,"
            "the maxSize will remain unchanged and extra chars will be dropped"
        );
}