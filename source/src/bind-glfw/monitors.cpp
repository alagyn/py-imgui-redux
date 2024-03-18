#include <bind-glfw/modules.h>
#include <binder/list-wrapper.h>

static py::object monitorCallback;

void monitorSetCallbackFunc(GLFWmonitor* monitor, int event)
{
    if(!monitorCallback.is_none())
    {
        monitorCallback(monitor, event);
    }
}

void init_monitors(py::module& m)
{
    monitorCallback = py::none();

    initListWrapper<GLFWmonitor>(m, "ListWrapperMonitor");

    m.def(
        "GetMonitors",
        []()
        {
            int count;
            GLFWmonitor** monitors = glfwGetMonitors(&count);
            return ListWrapper<GLFWmonitor*>(monitors, count);
        }
    );

    QUICK(GetPrimaryMonitor);

    m.def(
        "GetMonitorPos",
        [](GLFWmonitor* monitor)
        {
            int xpos, ypos;
            glfwGetMonitorPos(monitor, &xpos, &ypos);
            return py::make_tuple(xpos, ypos);
        },
        "monitor"_a
    );

    m.def(
        "GetMonitorWorkarea",
        [](GLFWmonitor* monitor)
        {
            int xpos, ypos, width, height;
            glfwGetMonitorWorkarea(monitor, &xpos, &ypos, &width, &height);
            return py::make_tuple(xpos, ypos, width, height);
        },
        "monitor"_a
    );

    m.def(
        "GetMonitorPhysicalSize",
        [](GLFWmonitor* monitor)
        {
            int width, height;
            glfwGetMonitorPhysicalSize(monitor, &width, &height);
            return py::make_tuple(width, height);
        },
        "monitor"_a
    );

    m.def(
        "GetMonitorContentScale",
        [](GLFWmonitor* monitor)
        {
            float xscale, yscale;
            glfwGetMonitorContentScale(monitor, &xscale, &yscale);
            return py::make_tuple(xscale, yscale);
        },
        "monitor"_a
    );

    m.def("GetMonitorName", glfwGetMonitorName, "monitor"_a);

    // TODO glfwSetMonitorUserPointer? Might not be useful
    // glfwGetMonitorUserPointer

    m.def(
        "SetMonitorCallback",
        [](py::object callback)
        {
            py::object out = monitorCallback;
            monitorCallback = callback;
            glfwSetMonitorCallback(monitorSetCallbackFunc);
            return out;
        },
        "callback"_a
    );

    initListWrapper<GLFWvidmode>(m, "ListWrapperVidmode");

    m.def(
        "GetVideoModes",
        [](GLFWmonitor* monitor)
        {
            int count;
            const GLFWvidmode* modes = glfwGetVideoModes(monitor, &count);
            return ListWrapper<GLFWvidmode>(modes, count);
        },
        "monitor"_a
    );

    m.def(
        "GetVideoMode",
        glfwGetVideoMode,
        "monitor"_a,
        py::return_value_policy::reference
    );

    m.def("SetGamma", glfwSetGamma, "monitor"_a, "gamma"_a);
    m.def(
        "GetGammaRamp",
        glfwGetGammaRamp,
        "monitor"_a,
        py::return_value_policy::reference
    );
    m.def("SetGammaRamp", glfwSetGammaRamp, "monitor"_a, "ramp"_a);
}