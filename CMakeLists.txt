cmake_minimum_required(VERSION 3.25.2)

project(imgui)

find_package(Python3 3.11
    REQUIRED
    COMPONENTS
    Interpreter Development
)

add_subdirectory(third-party)
add_subdirectory(test)

set(${PROJECT_NAME}_SRCS
    bind-imgui/bind-imgui.cpp
)

Python3_add_library(${PROJECT_NAME} ${${PROJECT_NAME}_SRCS})
set_target_properties(${PROJECT_NAME} PROPERTIES
    INTERPROCEDURAL_OPTIMIZATION ON
    CXX_VISIBILITY_PRESET ON
    VISIBILITY_INLINES_HIDDEN ON)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    pybind11::headers
    imgui-cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    bind-imgui
)