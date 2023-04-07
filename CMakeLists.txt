cmake_minimum_required(VERSION 3.25.2)

project(imgui)

set(Python3_FIND_REGISTRY NEVER)

find_package(Python3
    COMPONENTS
    REQUIRED
    Interpreter
    Development
)

add_subdirectory(third-party)
add_subdirectory(test)
add_subdirectory(bind-imgui)
