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
        );
}