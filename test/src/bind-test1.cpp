#include "bind-test1.h"
#include "test.h"

namespace py = pybind11;

void init1(py::module m)
{
    m.def("func1", func1, py::arg("a"), py::arg("b"));
}
