#include <bind-imgui/glfw-modules.h>

#include <binder/list-wrapper.h>
#include <pybind11/functional.h>

namespace bindGLFW {

namespace CB {
using Error = std::function<void(int, const char*)>;
using Key = std::function<void(GLFWwindow*, int, int, int, int)>;
using Char = std::function<void(GLFWwindow*, unsigned int)>;
using CharMods = std::function<void(GLFWwindow*, unsigned int, int)>;
using MouseButton = std::function<void(GLFWwindow*, int, int, int)>;
using CursorPos = std::function<void(GLFWwindow*, double, double)>;
using CursorEnter = std::function<void(GLFWwindow*, int)>;
using Scroll = std::function<void(GLFWwindow*, double, double)>;
using Drop = std::function<void(GLFWwindow*, ListWrapper<const char*>)>;
using JoyStick = std::function<void(int, int)>;
using Monitor = std::function<void(GLFWmonitor*, int)>;
using WindowPos = std::function<void(GLFWwindow*, int, int)>;
using WindowSize = std::function<void(GLFWwindow*, int, int)>;
using WindowClose = std::function<void(GLFWwindow*)>;
using WindowRefresh = std::function<void(GLFWwindow*)>;
using WindowFocus = std::function<void(GLFWwindow*, int)>;
using WindowIconify = std::function<void(GLFWwindow*, int)>;
using WindowMaximize = std::function<void(GLFWwindow*, int)>;
using FramebufferSize = std::function<void(GLFWwindow*, int, int)>;
using WindowContentScale = std::function<void(GLFWwindow*, float, float)>;
} //namespace CB

// context.cpp
CB::Error Error;

void ErrorCB(int err, const char* msg)
{
    Error(err, msg);
}

// input.cpp
CB::Key Key;

void KeyCB(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Key(window, key, scancode, action, mods);
}

CB::Char Char;

void CharCB(GLFWwindow* window, unsigned int codepoint)
{
    Char(window, codepoint);
}

CB::CharMods CharMods;

void CharModsCB(GLFWwindow* window, unsigned int codepoint, int mods)
{
    CharMods(window, codepoint, mods);
}

CB::MouseButton MouseButton;

void MouseButtonCB(GLFWwindow* window, int button, int action, int mods)
{
    MouseButton(window, button, action, mods);
}

CB::CursorPos CursorPos;

void CursorPosCB(GLFWwindow* window, double xpos, double ypos)
{
    CursorPos(window, xpos, ypos);
}

CB::CursorEnter CursorEnter;

void CursorEnterCB(GLFWwindow* window, int entered)
{
    CursorEnter(window, entered);
}

CB::Scroll Scroll;

void ScrollCB(GLFWwindow* window, double xoffset, double yoffset)
{
    Scroll(window, xoffset, yoffset);
}

CB::Drop Drop;

void DropCB(GLFWwindow* window, int path_count, const char** paths)
{
    Drop(window, ListWrapper<const char*>(paths, path_count));
}

// joystick.cpp
CB::JoyStick JoyStick;

void JoystickCB(int jid, int event)
{
    JoyStick(jid, event);
}

// monitors.cpp
CB::Monitor Monitor;

void monitorCB(GLFWmonitor* monitor, int event)
{
    Monitor(monitor, event);
}

// windows.cpp
CB::WindowPos WindowPos;

void WindowPosCB(GLFWwindow* window, int xpos, int ypos)
{
    WindowPos(window, xpos, ypos);
}

CB::WindowSize WindowSize;

void WindowSizeCB(GLFWwindow* window, int width, int height)
{
    WindowSize(window, width, height);
}

CB::WindowClose WindowClose;

void WindowCloseCB(GLFWwindow* window)
{
    WindowClose(window);
}

CB::WindowRefresh WindowRefresh;

void WindowRefreshCB(GLFWwindow* window)
{
    WindowRefresh(window);
}

CB::WindowFocus WindowFocus;

void WindowFocusCB(GLFWwindow* window, int focused)
{
    WindowFocus(window, focused);
}

CB::WindowIconify WindowIconify;

void WindowIconifyCB(GLFWwindow* window, int iconified)
{
    WindowIconify(window, iconified);
}

CB::WindowMaximize WindowMaximize;

void WindowMaximizeCB(GLFWwindow* window, int maximized)
{
    WindowMaximize(window, maximized);
}

CB::FramebufferSize FramebufferSize;

void FramebufferSizeCB(GLFWwindow* window, int width, int height)
{
    FramebufferSize(window, width, height);
}

CB::WindowContentScale WindowContentScale;

void WindowContentScaleCB(GLFWwindow* window, float xscale, float yscale)
{
    WindowContentScale(window, xscale, yscale);
}

#define QUOTE(X) #X

#define WINDOW_CALLBACK(CB_VAR) \
    m.def( \
        QUOTE(Set##CB_VAR##Callback), \
        [](GLFWwindow* window, CB::CB_VAR callback) \
        { \
            CB::CB_VAR out = CB_VAR; \
            CB_VAR = callback; \
            glfwSet##CB_VAR##Callback(window, CB_VAR##CB); \
            return out; \
        }, \
        "window"_a, \
        "callback"_a \
    )

void init_callbacks(py::module& m)
{
    m.def(
        "SetErrorCallback",
        [](CB::Error callback)
        {
            CB::Error out = Error;
            Error = callback;
            glfwSetErrorCallback(ErrorCB);
            return out;
        },
        "callback"_a
    );

    WINDOW_CALLBACK(Key);
    WINDOW_CALLBACK(Char);
    WINDOW_CALLBACK(CharMods);
    WINDOW_CALLBACK(MouseButton);
    WINDOW_CALLBACK(CursorPos);
    WINDOW_CALLBACK(CursorEnter);
    WINDOW_CALLBACK(Scroll);
    WINDOW_CALLBACK(Drop);

    m.def(
        "SetJoystickCallback",
        [](CB::JoyStick callback)
        {
            CB::JoyStick out = JoyStick;
            JoyStick = callback;
            glfwSetJoystickCallback(JoystickCB);
            return out;
        },
        "callback"_a
    );

    m.def(
        "SetMonitorCallback",
        [](CB::Monitor callback)
        {
            CB::Monitor out = Monitor;
            Monitor = callback;
            glfwSetMonitorCallback(monitorCB);
            return out;
        }
    );

    WINDOW_CALLBACK(WindowPos);
    WINDOW_CALLBACK(WindowSize);
    WINDOW_CALLBACK(WindowClose);
    WINDOW_CALLBACK(WindowRefresh);
    WINDOW_CALLBACK(WindowFocus);
    WINDOW_CALLBACK(WindowIconify);
    WINDOW_CALLBACK(WindowMaximize);
    WINDOW_CALLBACK(FramebufferSize);
    WINDOW_CALLBACK(WindowContentScale);
}

} //namespace bindGLFW