#include <bind-imgui/glfw-modules.h>

#include <binder/list-wrapper.h>

namespace bindGLFW {

void init_input(py::module& m)
{
    QUICK(PollEvents);
    QUICK(WaitEvents);
    m.def("WaitEventsTimeout", glfwWaitEventsTimeout, "timeout"_a);
    QUICK(PostEmptyEvent);

    m.def("GetInputMode", glfwGetInputMode, "window"_a, "mode"_a);
    m.def("SetInputMode", glfwSetInputMode, "window"_a, "mode"_a, "value"_a);

    m.def(
        "RawMouseMotionSupported",
        []()
        {
            return static_cast<bool>(glfwRawMouseMotionSupported());
        }
    );

    m.def("GetKeyName", glfwGetKeyName, "key"_a, "scancode"_a);
    m.def("GetKeyScancode", glfwGetKeyScancode, "key"_a);
    m.def("GetKey", glfwGetKey, "window"_a, "key"_a);
    m.def("GetMouseButton", glfwGetMouseButton, "window"_a, "button"_a);
    m.def(
        "GetCursorPos",
        [](GLFWwindow* window)
        {
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            return py::make_tuple(xpos, ypos);
        },
        "window"_a
    );
    m.def("SetCursorPos", glfwSetCursorPos, "window"_a, "xpos"_a, "ypos"_a);
    m.def(
        "CreateCursor",
        glfwCreateCursor,
        "image"_a,
        "xhot"_a,
        "yhot"_a,
        py::return_value_policy::reference
    );
    m.def(
        "CreateStandardCursor",
        glfwCreateStandardCursor,
        "shape"_a,
        py::return_value_policy::reference
    );
    m.def("DestroyCursor", glfwDestroyCursor, "cursor"_a);
    m.def("SetCursor", glfwSetCursor, "window"_a, "cursor"_a);

    m.def("SetClipboardString", glfwSetClipboardString, "window"_a, "string"_a);
    m.def("GetClipboardString", glfwGetClipboardString, "window"_a);
}

} //namespace bindGLFW