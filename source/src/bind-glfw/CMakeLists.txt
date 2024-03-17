set(GLFW_SRCS
    bind-glfw.cpp
)

setupPyBindLib(
    LIB bindglfw
    SRCS ${GLFW_SRCS}
    LINKS
        glfw
        glad
    INCS ${CMAKE_}

)