#include <binder/bind-modules.h>
#include <binder/wraps.h>
#include <pybind11/stl.h>
#include <sstream>

namespace py = pybind11;

StrRef::StrRef(size_t maxSize)
    : ImList<char>(std::vector<char>(maxSize + 1))
    , strLen(0)
{
    // Set first char to zero to terminate string
    vals[0] = 0;
}

StrRef::StrRef(const char* val, size_t maxSize)
    : ImList<char>(std::vector<char>())
{
    if(maxSize == 0)
    {
        maxSize = std::strlen(val);
    }
    vals.resize(maxSize + 1);
    std::strncpy(vals.data(), val, maxSize);
}

void StrRef::set(const char* newVal, size_t maxSize)
{
    if(maxSize != 0)
    {
        vals.resize(maxSize + 1);
    }
    std::strncpy(vals.data(), newVal, vals.size());
    strLen = strlen(vals.data());
}

void StrRef::resize(size_t maxSize)
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

size_t StrRef::strSize()
{
    return strLen;
}

void StrRef::calcLen()
{
    this->strLen = strnlen(vals.data(), vals.size());
}

template<class T, class U>
void initRef(py::module& m, const char* name, const char* desc, U defaultVal)
{
    py::class_<T>(m, name, desc)
        .def(py::init<U>(), "val"_a = defaultVal)
        .def_readwrite("val", &T::val, "The wrapped value")
        .def("__str__", &T::toStr);
}

template<class T, class U>
void initList(py::module& m, const char* name, const char* desc)
{
    py::class_<T>(m, name, desc)
        .def(py::init<std::vector<U>>(), "vals"_a = std::vector<U>())
        .def(py::init<>())
        .def("append", &T::append, "val"_a, "Append a value to the end")
        .def("pop", &T::pop, "Pop a value from the end")
        .def(
            "resize",
            &T::resize,
            "size"_a,
            "Resize the vector, dropping any lost values"
        )
        .def("clear", &T::clear)
        .def("__len__", &T::size)
        .def("__iter__", &T::makeIter)
        .def("__getitem__", &T::getItem, "index"_a)
        .def("__setitem__", &T::setItem, "index"_a, "val"_a);
}

void init_wraps(py::module& m)
{
    initRef<BoolRef_>(m, "BoolRef", "A pass-by-ref wrapper for a bool", false);
    initRef<IntRef_>(m, "IntRef", "A pass-by-ref wrapper for an int", 0);
    initRef<FloatRef_>(m, "FloatRef", "A pass-by-ref wrapper for a float", 0.0f);
    initRef<DoubleRef_>(m, "DoubleRef", "A pass-by-ref wrapper for a double", 0.0);

    initList<IntList, int>(m, "IntList", "Thin wrapper over a std::vector<int>");
    initList<WCharList, ImWchar>(
        m,
        "WCharList",
        "Thin wrapper over a std::vector<ImWchar>"
    );
    initList<FloatList, float>(
        m,
        "FloatList",
        "Thin wrapper over a std::vector<float>"
    );
    initList<DoubleList, double>(
        m,
        "DoubleList",
        "Thin wrapper over a std::vector<double>"
    );
    initList<StrList, const char*>(
        m,
        "StrList",
        "Thin wrapper over a std::vector<const char*>"
    );
    initList<Vec2List, ImVec2>(
        m,
        "Vec2List",
        "Thin wrapper over a std::vector<ImVec2>"
    );

    py::class_<StrRef>(m, "StrRef", "Thin wrapper over a std::vector<char>")
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
        .def("append", &StrRef::append, "val"_a, "Append a value to the end")
        .def("pop", &StrRef::pop, "Pop a value from the end")
        .def(
            "resize",
            &StrRef::resize,
            "size"_a,
            "Resize the vector, dropping any lost values"
        )
        .def("__len__", &StrRef::strSize)
        .def("__str__", &StrRef::data, py::return_value_policy::copy)
        .def(
            "copy",
            &StrRef::data,
            py::return_value_policy::copy,
            "Get a copy of the string"
        )
        .def(
            "set",
            &StrRef::set,
            "newVal"_a,
            "maxSize"_a = 0,
            "Assign a new value to the string. If maxSize=0,"
            "the maxSize will remain unchanged and extra chars will be "
            "dropped"
        );
}
