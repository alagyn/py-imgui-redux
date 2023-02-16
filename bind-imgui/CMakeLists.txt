set(${PROJECT_NAME}_SRCS "binder/src/bind-modules.cpp")

include(imgui-core.cmake)
include(imnodes.cmake)
include(implot.cmake)

Python3_add_library(${PROJECT_NAME} ${${PROJECT_NAME}_SRCS})
set_target_properties(${PROJECT_NAME} PROPERTIES
    INTERPROCEDURAL_OPTIMIZATION ON
    CXX_VISIBILITY_PRESET ON
    VISIBILITY_INLINES_HIDDEN ON
    CXX_STANDARD 17
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    pybind11::headers
    imgui-cpp
    glfw
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
    IMGUI_DISABLE_OBSOLETE_KEYIO
    IMGUI_DISABLE_OBSOLETE_FUNCTIONS
)