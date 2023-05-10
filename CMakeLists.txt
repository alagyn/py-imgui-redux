cmake_minimum_required(VERSION 3.25.2)

project(imgui)

set(Python3_FIND_REGISTRY NEVER)

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
add_subdirectory(test)
add_subdirectory(bind-imgui)
