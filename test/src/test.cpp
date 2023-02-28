#include <iostream>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

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

PYBIND11_MODULE(bdd, m)
{
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