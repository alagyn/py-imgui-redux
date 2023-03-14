#include <binder/inc/bind-modules.h>
#include <binder/inc/wraps.h>
#include <sstream>

namespace py = pybind11;

void init_wraps(py::module& m)
{
    py::class_<BoolRef>(m, "BoolRef")
        .def(py::init<bool>(), "val"_a = false)
        .def_readwrite("val", &BoolRef::val)
        .def("__str__", &BoolRef::toStr);

    py::class_<FloatRef>(m, "FloatRef")
        .def(py::init<float>(), "val"_a = 0.0)
        .def_readwrite("val", &FloatRef::val)
        .def("__str__", &FloatRef::toStr);

    py::class_<IntRef>(m, "IntRef")
        .def(py::init<int>(), "val"_a = 0)
        .def_readwrite("val", &IntRef::val);

    py::class_<IntList>(m, "IntList")
        .def(py::init<std::vector<int>>(), "vals"_a = std::vector<int>())
        .def("append", &IntList::append, "val"_a)
        .def("pop", &IntList::pop)
        .def("__len__", &IntList::size)
        .def("__iter__", &IntList::makeIter)
        .def("__getitem__", &IntList::getItem, "index"_a)
        .def("__setitem__", &IntList::setItem, "index"_a, "val"_a);

    py::class_<FloatList>(m, "FloatList")
        .def(py::init<std::vector<float>>(), "vals"_a = std::vector<float>())
        .def("append", &FloatList::append, "val"_a)
        .def("pop", &FloatList::pop)
        .def("__len__", &FloatList::size)
        .def("__iter__", &FloatList::makeIter)
        .def("__getitem__", &FloatList::getItem, "index"_a)
        .def("__setitem__", &FloatList::setItem, "index"_a, "val"_a);
}