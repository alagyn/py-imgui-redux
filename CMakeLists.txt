cmake_minimum_required(VERSION 3.25.2)

project(py-imgui-redux)

find_package(Python3 3.11
    REQUIRED
    COMPONENTS
    Interpreter Development
)

add_subdirectory(third-party)

add_subdirectory(bind-imgui)
