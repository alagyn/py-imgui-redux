#include "bind-test2.h"
#include "test.h"

namespace py = pybind11;

void init2(py::module m)
{
    m.def("func1", func2, py::arg("str"));
}
