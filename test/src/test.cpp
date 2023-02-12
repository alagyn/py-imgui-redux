#include <iostream>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

std::string test(char* str, unsigned len)
{
    std::string x(10, '\0');
    for(int i = 0; i < 8; ++i)
    {
        x[i] = '0' + i;
    }

    return x;
}

PYBIND11_MODULE(bdd, m)
{
    m.def("test", test, "str"_a, "len"_a, py::return_value_policy::reference);
}