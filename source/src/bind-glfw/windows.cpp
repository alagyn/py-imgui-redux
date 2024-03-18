#include <bind-glfw/modules.h>

static py::object windowPosCallback;
static py::object windowSizeCallback;
static py::object windowCloseCallback;
static py::object windowRefreshCallback;
static py::object windowFocusCallback;
static py::object windowIconifyCallback;
static py::object windowMaximizeCallback;
static py::object framebufferSizeCallback;
static py::object windowContentScaleCallback;

void windowPosCallbackFunc(GLFWwindow* window, int xpos, int ypos)
{
    if(!windowPosCallback.is_none())
    {
        windowPosCallback(window, xpos, ypos);
    }
}

void windowSizeCallbackFunc(GLFWwindow* window, int width, int height)
{
    if(!windowSizeCallback.is_none())
    {
        windowSizeCallback(window, width, height);
    }
}

void windowCloseCallbackFunc(GLFWwindow* window)
{
    if(!windowCloseCallback.is_none())
    {
        windowCloseCallback(window);
    }
}

void windowRefreshCallbackFunc(GLFWwindow* window)
{
    if(!windowRefreshCallback.is_none())
    {
        windowRefreshCallback(window);
    }
}

void windowFocusCallbackFunc(GLFWwindow* window, int focused)
{
    if(!windowFocusCallback.is_none())
    {
        windowFocusCallback(window, static_cast<bool>(focused));
    }
}

void windowIconifyCallbackFunc(GLFWwindow* window, int iconified)
{
    if(!windowIconifyCallback.is_none())
    {
        windowIconifyCallback(window, static_cast<bool>(iconified));
    }
}

void windowMaximizeCallbackFunc(GLFWwindow* window, int maximized)
{
    if(!windowMaximizeCallback.is_none())
    {
        windowMaximizeCallback(window, static_cast<bool>(maximized));
    }
}

void framebufferSizeCallbackFunc(GLFWwindow* window, int width, int height)
{
    if(!framebufferSizeCallback.is_none())
    {
        framebufferSizeCallback(window, width, height);
    }
}

void windowContentScaleCallbackFunc(GLFWwindow* window, float xscale, float yscale)
{
    if(!windowContentScaleCallback.is_none())
    {
        windowContentScaleCallback(window, xscale, yscale);
    }
}

void init_windows(py::module& m)
{
    windowPosCallback = py::none();
    windowSizeCallback = py::none();
    windowCloseCallback = py::none();
    windowRefreshCallback = py::none();
    windowFocusCallback = py::none();
    windowIconifyCallback = py::none();
    windowMaximizeCallback = py::none();
    framebufferSizeCallback = py::none();

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

    m.def("Destroywindow", glfwDestroyWindow, "window"_a);

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

    m.def(
        "SetWindowPosCallback",
        [](GLFWwindow* window, py::object callback)
        {
            py::object out = windowPosCallback;
            windowPosCallback = callback;
            glfwSetWindowPosCallback(window, windowPosCallbackFunc);
            return out;
        },
        "window"_a,
        "callback"_a
    );

    m.def(
        "SetWindowSizeCallback",
        [](GLFWwindow* window, py::object callback)
        {
            py::object out = windowSizeCallback;
            windowSizeCallback = callback;
            glfwSetWindowSizeCallback(window, windowSizeCallbackFunc);
            return out;
        },
        "window"_a,
        "callback"_a
    );

    m.def(
        "SetWindowCloseCallback",
        [](GLFWwindow* window, py::object callback)
        {
            py::object out = windowCloseCallback;
            windowCloseCallback = callback;
            glfwSetWindowCloseCallback(window, windowCloseCallbackFunc);
            return out;
        },
        "window"_a,
        "callback"_a
    );

    m.def(
        "SetWindowRefreshcallback",
        [](GLFWwindow* window, py::object callback)
        {
            py::object out = windowRefreshCallback;
            windowRefreshCallback = callback;
            glfwSetWindowRefreshCallback(window, windowRefreshCallbackFunc);
            return out;
        },
        "window"_a,
        "callback"_a
    );

    m.def(
        "SetWindowFocusCallback",
        [](GLFWwindow* window, py::object callback)
        {
            py::object out = windowFocusCallback;
            windowFocusCallback = callback;
            glfwSetWindowFocusCallback(window, windowFocusCallbackFunc);
            return out;
        },
        "window"_a,
        "callback"_a
    );

    m.def(
        "SetWindowIconifyCallback",
        [](GLFWwindow* window, py::object callback)
        {
            py::object out = windowIconifyCallback;
            windowIconifyCallback = callback;
            glfwSetWindowIconifyCallback(window, windowIconifyCallbackFunc);
            return out;
        },
        "window"_a,
        "callback"_a
    );

    m.def(
        "SetWindowMaximizeCallback",
        [](GLFWwindow* window, py::object callback)
        {
            py::object out = windowMaximizeCallback;
            windowMaximizeCallback = callback;
            glfwSetWindowMaximizeCallback(window, windowMaximizeCallbackFunc);
            return out;
        },
        "window"_a,
        "callback"_a
    );

    m.def(
        "SetFramebufferSizeCallback",
        [](GLFWwindow* window, py::object callback)
        {
            py::object out = framebufferSizeCallback;
            framebufferSizeCallback = callback;
            glfwSetFramebufferSizeCallback(window, framebufferSizeCallbackFunc);
            return out;
        },
        "window"_a,
        "callback"_a
    );

    m.def(
        "SetWindowContentScaleCallback",
        [](GLFWwindow* window, py::object callback)
        {
            py::object out = windowContentScaleCallback;
            windowContentScaleCallback = callback;
            glfwSetWindowContentScaleCallback(
                window,
                windowContentScaleCallbackFunc
            );
            return out;
        },
        "window"_a,
        "callback"_a
    );
}