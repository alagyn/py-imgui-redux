#include <bind-imgui/glfw-modules.h>

namespace bindGLFW {

void init_windows(py::module& m)
{
    QUICK(DefaultWindowHints);

    m.def("WindowHint", glfwWindowHint, "hint"_a, "value"_a);
    m.def("WindowHintString", glfwWindowHintString, "hint"_a, "value"_a);

    m.def(
        "CreateWindow",
        glfwCreateWindow,
        "width"_a,
        "height"_a,
        "title"_a,
        "monitor"_a = nullptr,
        "share"_a = nullptr,
        py::return_value_policy::reference
    );

    m.def(
        "DestroyWindow",
        glfwDestroyWindow,
        "window"_a,
        py::call_guard<py::gil_scoped_release>()
    );

    m.def(
        "WindowShouldClose",
        [](GLFWwindow* window)
        {
            // Force cast this to bool
            return static_cast<bool>(glfwWindowShouldClose(window));
        },
        "window"_a
    );

    m.def("SetWindowShouldClose", glfwSetWindowShouldClose, "window"_a, "value"_a);
    m.def("SetWindowTitle", glfwSetWindowTitle, "window"_a, "title"_a);
    m.def(
        "SetWindowIcon",
        [](GLFWwindow* window, GLFWimage* image)
        {
            // TODO allow this to take a list?
            glfwSetWindowIcon(window, 1, image);
        },
        "window"_a,
        "image"_a
    );

    m.def(
        "GetWindowPos",
        [](GLFWwindow* window)
        {
            int xpos, ypos;
            glfwGetWindowPos(window, &xpos, &ypos);
            return py::make_tuple(xpos, ypos);
        },
        "window"_a
    );

    m.def("SetWindowPos", glfwSetWindowPos, "window"_a, "xpos"_a, "ypos"_a);

    m.def(
        "GetWindowSize",
        [](GLFWwindow* window)
        {
            int width, height;
            glfwGetWindowSize(window, &width, &height);
            return py::make_tuple(width, height);
        },
        "window"_a
    );

    m.def(
        "SetWindowSizeLimits",
        glfwSetWindowSizeLimits,
        "window"_a,
        "minWidth"_a,
        "minHeight"_a,
        "maxWidth"_a,
        "maxHeight"_a
    );

    m.def(
        "SetWindowAspectRatio",
        glfwSetWindowAspectRatio,
        "window"_a,
        "numer"_a,
        "denom"_a
    );

    m.def("SetWindowSize", glfwSetWindowSize, "window"_a, "width"_a, "height"_a);
    m.def(
        "GetFramebufferSize",
        [](GLFWwindow* window)
        {
            int width, height;
            glfwGetFramebufferSize(window, &width, &height);
            return py::make_tuple(width, height);
        },
        "window"_a
    );

    m.def(
        "GetWindowFrameSize",
        [](GLFWwindow* window)
        {
            int left, top, right, bottom;
            glfwGetWindowFrameSize(window, &left, &top, &right, &bottom);
            return py::make_tuple(left, top, right, bottom);
        },
        "window"_a
    );

    m.def(
        "GetWindowContentScale",
        [](GLFWwindow* window)
        {
            float xscale, yscale;
            glfwGetWindowContentScale(window, &xscale, &yscale);
            return py::make_tuple(xscale, yscale);
        },
        "window"_a
    );

    m.def("GetWindowOpacity", glfwGetWindowOpacity, "window"_a);
    m.def("setWindowOpacity", glfwSetWindowOpacity, "window"_a, "opacity"_a);
    m.def("IconifyWindow", glfwIconifyWindow, "window"_a);
    m.def("RestoreWindow", glfwRestoreWindow, "window"_a);
    m.def("MaximizeWindow", glfwMaximizeWindow, "window"_a);
    m.def("ShowWindow", glfwShowWindow, "window"_a);
    m.def("HideWindow", glfwHideWindow, "window"_a);
    m.def("FocusWindow", glfwFocusWindow, "window"_a);
    m.def("RequestWindowAttention", glfwRequestWindowAttention, "window"_a);
    m.def(
        "GetWindowMonitor",
        glfwGetWindowMonitor,
        "window"_a,
        py::return_value_policy::reference
    );
    m.def(
        "SetWindowMonitor",
        glfwSetWindowMonitor,
        "window"_a,
        "monitor"_a,
        "xpos"_a,
        "ypos"_a,
        "width"_a,
        "height"_a,
        "refreshRate"_a
    );
    m.def("GetWindowAttrib", glfwGetWindowAttrib, "window"_a, "attrib"_a);
    m.def(
        "SetWindowAttrib",
        glfwSetWindowAttrib,
        "window"_a,
        "attrib"_a,
        "value"_a
    );

    // TODO glfwSetWindowUserPointer?
    // glfwGetWindowuserPointer
}

} //namespace bindGLFW