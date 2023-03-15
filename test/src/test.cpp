#include <cstdint>
#include <iostream>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <sstream>

using namespace pybind11::literals;
namespace py = pybind11;

class IntWrap
{
public:
    IntWrap(int val)
        : val(val)
    {
    }

    int val;

    int toInt()
    {
        return val;
    }

    const char* toStr()
    {
        std::stringstream ss;
        ss << "IntWrapper (" << val << ")";
        return ss.str().c_str();
    }
};

typedef int* IntPtr;

struct inty
{
    int val;
};

namespace PYBIND11_NAMESPACE {
    namespace detail {
        template<> struct type_caster<int*>
        {
            // Declares a var named "value"
            PYBIND11_TYPE_CASTER(int*, const_name("int_"));

            bool load(py::handle handle, bool)
            {
                std::cout << "Casting to int\n" << std::flush;

                IntWrap* wrapper = handle.cast<IntWrap*>();
                if(!wrapper)
                {
                    std::cout << "Failed to cast\n" << std::flush;
                    return false;
                }
                std::cout << "CAST\n" << std::flush;
                value = &wrapper->val;
                return true;
            }
        };

        template<> struct type_caster<inty>
        {
            // Declares a var named "value"
            PYBIND11_TYPE_CASTER(inty, const_name("inty"));

            bool load(py::handle handle, bool)
            {
                std::cout << "Casting to inty\n" << std::flush;

                IntWrap* wrapper = handle.cast<IntWrap*>();
                if(!wrapper)
                {
                    std::cout << "Failed to cast\n" << std::flush;
                    return false;
                }
                std::cout << "CAST\n" << std::flush;
                value.val = wrapper->val;
                return true;
            }
        };
    } //namespace detail

} //namespace PYBIND11_NAMESPACE

void normFunc(int num)
{
    num += 5;
}

void ptrFunc(int* num)
{
    *num += 5;
}

void wrapFunc(IntWrap* num)
{
    num->val += 5;
}

void intyFunc(inty num)
{
    num.val += 5;
}

PYBIND11_MODULE(bdd, m)
{
    //py::class_<int*>(m, "__intPtr");
    py::class_<IntWrap>(m, "Wrap")
        .def(py::init<int>(), "val"_a = 0)
        //.def("__int__", &IntWrap::toInt)
        //.def("__float__", &IntWrap::toFloat)
        .def("__str__", &IntWrap::toStr)
        .def_readwrite("val", &IntWrap::val);

    m.def("normal", normFunc, "num"_a);
    m.def("ptr", ptrFunc, "num"_a);
    m.def("wrap", wrapFunc, "num"_a);
    m.def("inty", intyFunc, "num"_a);
}