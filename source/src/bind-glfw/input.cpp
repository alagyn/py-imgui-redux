#include <bind-glfw/modules.h>

#include <binder/list-wrapper.h>

static py::object keyCallback;
static py::object charCallback;
static py::object charModsCallback;
static py::object mouseButtonCallback;
static py::object cursorPosCallback;
static py::object cursorEnterCallback;
static py::object scrollCallback;
static py::object dropCallback;

void keyCallbackFunc(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(!keyCallback.is_none())
    {
        keyCallback(window, key, scancode, action, mods);
    }
}

void charCallbackFunc(GLFWwindow* window, unsigned int codepoint)
{
    if(!charCallback.is_none())
    {
        charCallback(window, codepoint);
    }
}

void charModsCallbackFunc(GLFWwindow* window, unsigned int codepoint, int mods)
{
    if(!charModsCallback.is_none())
    {
        charModsCallback(window, codepoint, mods);
    }
}

void mouseButtonCallbackFunc(GLFWwindow* window, int button, int action, int mods)
{
    if(!mouseButtonCallback.is_none())
    {
        mouseButtonCallback(window, button, action, mods);
    }
}

void cursorPosCallbackFunc(GLFWwindow* window, double xpos, double ypos)
{
    if(!cursorPosCallback.is_none())
    {
        cursorPosCallback(window, xpos, ypos);
    }
}

void cursorEnterCallbackFunc(GLFWwindow* window, int entered)
{
    if(!cursorEnterCallback.is_none())
    {
        cursorEnterCallback(window, static_cast<bool>(entered));
    }
}

void scrollCallbackFunc(GLFWwindow* window, double xoffset, double yoffset)
{
    if(!scrollCallback.is_none())
    {
        scrollCallback(window, xoffset, yoffset);
    }
}

void dropCallbackFunc(GLFWwindow* window, int path_count, const char** paths)
{
    if(!dropCallback.is_none())
    {
        dropCallback(window, ListWrapper<const char*>(paths, path_count));
    }
}

void init_input(py::module& m)
{
    keyCallback = py::none();
    charCallback = py::none();
    charModsCallback = py::none();
    mouseButtonCallback = py::none();
    cursorPosCallback = py::none();
    cursorEnterCallback = py::none();
    scrollCallback = py::none();
    dropCallback = py::none();

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

    m.def(
        "SetKeyCallback",
        [](GLFWwindow* window, py::object callback)
        {
            py::object out = keyCallback;
            keyCallback = callback;
            glfwSetKeyCallback(window, keyCallbackFunc);
            return out;
        },
        "window"_a,
        "callback"_a
    );

    m.def(
        "SetCharCallback",
        [](GLFWwindow* window, py::object callback)
        {
            py::object out = charCallback;
            charCallback = callback;
            glfwSetCharCallback(window, charCallbackFunc);
            return out;
        },
        "window"_a,
        "callback"_a
    );

    m.def(
        "SetCharModsCallback",
        [](GLFWwindow* window, py::object callback)
        {
            py::object out = charModsCallback;
            charModsCallback = callback;
            glfwSetCharModsCallback(window, charModsCallbackFunc);
            return out;
        },
        "window"_a,
        "callback"_a
    );

    m.def(
        "SetMouseButtonCallback",
        [](GLFWwindow* window, py::object callback)
        {
            py::object out = mouseButtonCallback;
            mouseButtonCallback = callback;
            glfwSetMouseButtonCallback(window, mouseButtonCallbackFunc);
            return out;
        },
        "window"_a,
        "callback"_a
    );

    m.def(
        "SetCursorPosCallback",
        [](GLFWwindow* window, py::object callback)
        {
            py::object out = cursorPosCallback;
            cursorPosCallback = callback;
            glfwSetCursorPosCallback(window, cursorPosCallbackFunc);
            return out;
        },
        "window"_a,
        "callback"_a
    );

    m.def(
        "SetCursorEnterCallback",
        [](GLFWwindow* window, py::object callback)
        {
            py::object out = cursorEnterCallback;
            cursorEnterCallback = callback;
            glfwSetCursorEnterCallback(window, cursorEnterCallbackFunc);
            return out;
        },
        "window"_a,
        "callback"_a
    );

    m.def(
        "SetScrollCallback",
        [](GLFWwindow* window, py::object callback)
        {
            py::object out = scrollCallback;
            scrollCallback = callback;
            glfwSetScrollCallback(window, scrollCallbackFunc);
            return out;
        },
        "window"_a,
        "callback"_a
    );

    m.def(
        "SetDropCallback",
        [](GLFWwindow* window, py::object callback)
        {
            py::object out = dropCallback;
            dropCallback = callback;
            glfwSetDropCallback(window, dropCallbackFunc);
            return out;
        },
        "window"_a,
        "callback"_a
    );

    m.def("SetClipboardString", glfwSetClipboardString, "window"_a, "string"_a);
    m.def("GetClipboardString", glfwGetClipboardString, "window"_a);
}