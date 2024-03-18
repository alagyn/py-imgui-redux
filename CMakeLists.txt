cmake_minimum_required(VERSION 3.25.2)

project(imgui)

set(CMAKE_DEBUG_POSTFIX, "-d")
set(Python3_FIND_REGISTRY NEVER)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

if(${MSVC})
    set(PY_COMPONENTS Interpreter Development)
else()
    set(PY_COMPONENTS Interpreter Development.Module)
endif()

find_package(Python3
    COMPONENTS
    REQUIRED
    ${PY_COMPONENTS}
)

add_subdirectory(third-party)

set(INCLUDE_DIR source/inc)

include(setupPyBindLib)
include(imgui-srcs)
include(glfw-srcs)

setupPyBindLib(
    LIB imgui
    SRCS ${IMGUI_SRCS}
    LINKS
        imgui-cpp
        glfw
        glad
        stb
    INCS ${INCLUDE_DIR}
)
