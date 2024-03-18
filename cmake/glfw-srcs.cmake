set(BIND_GLFW_ROOT source/src/bind-glfw)

set(BIND_GLFW_SRCS
    ${BIND_GLFW_ROOT}/bind-glfw.cpp
    ${BIND_GLFW_ROOT}/constants.cpp
    ${BIND_GLFW_ROOT}/context.cpp
    ${BIND_GLFW_ROOT}/input.cpp
    #${BIND_GLFW_ROOT}/internal.cpp
    ${BIND_GLFW_ROOT}/joystick.cpp
    ${BIND_GLFW_ROOT}/monitors.cpp
    ${BIND_GLFW_ROOT}/structs.cpp
    ${BIND_GLFW_ROOT}/windows.cpp
)