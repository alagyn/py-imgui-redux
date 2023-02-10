#include "bind-test1.h"
#include "bind-test2.h"
#include "test.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(test, m)
{
    init1(m);
    init2(m);
}