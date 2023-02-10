project(imgui)

set(${PROJECT_NAME}_SRCS
    bind-imgui.cpp
)

Python3_add_library(${PROJECT_NAME} ${${PROJECT_NAME}_SRCS})
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    pybind11::headers
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    INTERPROCEDURAL_OPTIMIZATION ON
    CXX_VISIBILITY_PRESET ON
    VISIBILITY_INLINES_HIDDEN ON)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    pybind11::headers
    imgui-cpp
)