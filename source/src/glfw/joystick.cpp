#include <bind-imgui/glfw-modules.h>

#include <binder/list-wrapper.h>

namespace bindGLFW {

void init_joystick(py::module& m)
{
    m.def(
        "JoystickPresent",
        [](int jid)
        {
            return static_cast<bool>(glfwJoystickPresent(jid));
        },
        "jid"_a
    );

    m.def(
        "GetJoystickAxes",
        [](int jid)
        {
            int count = 0;
            const float* axes = glfwGetJoystickAxes(jid, &count);
            return ListWrapper<float>(axes, count);
        },
        "jid"_a
    );

    m.def(
        "GetJoystickButtons",
        [](int jid)
        {
            int count = 0;
            const unsigned char* buttons = glfwGetJoystickButtons(jid, &count);
            return ListWrapper<unsigned char>(buttons, count);
        },
        "jid"_a
    );

    m.def(
        "GetJoystickHats",
        [](int jid)
        {
            int count = 0;
            const unsigned char* hats = glfwGetJoystickHats(jid, &count);
            return ListWrapper<unsigned char>(hats, count);
        },
        "jid"_a
    );

    m.def("GetJoystickname", glfwGetJoystickName, "jid"_a);
    m.def("GetJoyStickGUID", glfwGetJoystickGUID, "jid"_a);

    // TODO SetJoystickUserPointer?

    m.def(
        "JoystickIsGamepad",
        [](int jid)
        {
            return static_cast<bool>(glfwJoystickIsGamepad(jid));
        },
        "jid"_a
    );

    m.def("UpdateGamepadMappings", glfwUpdateGamepadMappings, "string"_a);
    m.def("GetGamepadName", glfwGetGamepadName, "jid"_a);
    // TODO this might be need to be a lambda
    m.def("GetGamepadState", glfwGetGamepadName, "jid_a", "state"_a);
}

} //namespace bindGLFW