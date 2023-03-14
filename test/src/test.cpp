#include <iostream>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <sstream>

using namespace pybind11::literals;
namespace py = pybind11;

class Test
{
private:
    int value;

public:
    Test(int value)
        : value(value)
    {
    }

    int inc()
    {
        return ++value;
    }

    int dec(int num)
    {
        value -= num;
        return value;
    }
};

class IntWrap
{
public:
    IntWrap(int val = 0)
        : val(val)
    {
    }

    int toInt()
    {
        return val;
    }

    float toFloat()
    {
        return (float)val;
    }

    const char* toStr()
    {
        std::stringstream ss;
        ss << "IntWrapper (" << val << ")";
        return ss.str().c_str();
    }

    int add(int other)
    {
        return val + other;
    }

    int val;
};

PYBIND11_MODULE(bdd, m)

{
    py::class_<IntWrap>(m, "Wrap")
        .def(py::init<int>(), "val"_a = 0)
        .def("__int__", &IntWrap::toInt)
        .def("__float__", &IntWrap::toFloat)
        .def("__str__", &IntWrap::toStr)
        .def("__add__", &IntWrap::add)
        .def_readwrite("val", &IntWrap::val);

    py::class_<Test>(m, "Test")
        .def(py::init<int>(), "value"_a)
        .def("inc", &Test::inc)
        .def(
            "dec",
            [](Test* self, int num)
            {
                return self->dec(num);
            },
            "num"_a
        )
        .def_property_readonly_static(
            "stat",
            [](py::type)
            {
                return 25;
            }
        );

    m.def(
        "arrint",
        [](std::array<int, 3> vals)
        {
            py::print(vals[0], vals[1], vals[2]);
            vals[0] = 16;
            return vals;
        },
        "arr"_a
    );
    m.def(
        "arrflt",
        [](std::array<float, 3> vals)
        {
            py::print(vals[0], vals[1], vals[2]);
            vals[0] = 16.5;
            return vals;
        },
        "arr"_a
    );
}