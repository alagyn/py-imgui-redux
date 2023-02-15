# Third Party Libraries
add_subdirectory(pybind11)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw)

# -------------- imgui --------------
set(imgui_SRCS
    imgui/imgui.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/backends/imgui_impl_glfw.cpp
    imgui/backends/imgui_impl_opengl3.cpp

    # imnodes
    imnodes/imnodes.cpp
)

add_library(imgui-cpp
    STATIC
    ${imgui_SRCS}
)

target_include_directories(imgui-cpp
    PUBLIC
    imgui
    imnodes
)

target_link_libraries(imgui-cpp
    PRIVATE
    glfw
    opengl32.lib
    gdi32.lib
    shell32.lib
)

# --------------- imnodes -------------
set(imnodes_SRCS
    imnodes/imnodes.cpp
)

add_library(imnodes-cpp
    STATIC
    ${imnodes_SRCS}
)

target_include_directories(imnodes-cpp
    PUBLIC
    imnodes
)

target_link_libraries(imnodes-cpp
    PRIVATE
    imgui-cpp
)