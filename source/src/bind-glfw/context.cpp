#include <bind-glfw/modules.h>
#include <binder/list-wrapper.h>

namespace py = pybind11;
using namespace pybind11::literals;

static py::object errorCallback;

void errorCallbackFunc(int error_code, const char* desc)
{
    if(!errorCallback.is_none())
    {
        errorCallback(error_code, desc);
    }
}

void init_context(py::module& m)
{
    errorCallback = py::none();

    py::class_<GLFWwindow>(m, "Window");
    py::class_<GLFWmonitor>(m, "Monitor");
    py::class_<GLFWcursor>(m, "Cursor");

    QUICK(Init);
    QUICK(Terminate);
    m.def("InitHint", glfwInitHint, "hint"_a, "value"_a);
    m.def(
        "GetVersion",
        []()
        {
            int major, minor, rev;
            glfwGetVersion(&major, &minor, &rev);
            py::make_tuple(major, minor, rev);
        }
    );
    QUICK(GetVersionString);
    m.def(
        "GetError",
        []()
        {
            const char* desc;
            int code = glfwGetError(&desc);
            return py::make_tuple(code, desc);
        }
    );
    m.def(
        "SetErrorCallback",
        [](py::object cb)
        {
            py::object out = errorCallback;
            errorCallback = cb;
            glfwSetErrorCallback(errorCallbackFunc);
            return out;
        },
        "callback"_a
    );

    QUICK(GetTime);
    m.def("SetTime", glfwSetTime, "time"_a);
    QUICK(GetTimerValue);
    QUICK(GetTimerFrequency);

    m.def("MakeContextCurrent", glfwMakeContextCurrent, "window"_a);

    m.def(
        "GetCurrentContext",
        glfwGetCurrentContext,
        py::return_value_policy::reference
    );

    m.def("SwapBuffers", glfwSwapBuffers, "window"_a);
    m.def("SwapInterval", glfwSwapInterval, "interval"_a);
    m.def("ExtensionSupported", glfwExtensionSupported, "extension"_a);
    // TODO glfwGetProcAddress?
    QUICK(VulkanSupported);
    // TODO glfwGetRequiredInstanceExtensions?
}