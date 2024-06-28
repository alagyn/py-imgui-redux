cmake_minimum_required(VERSION 3.25.2)

project(imgui)

set(CMAKE_DEBUG_POSTFIX, "-d")
set(Python_FIND_REGISTRY NEVER)
#set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

if(${MSVC})
    set(PY_COMPONENTS Interpreter Development)
else()
    set(PY_COMPONENTS Interpreter Development.Module)
endif()

find_package(Python
    COMPONENTS
    REQUIRED
    ${PY_COMPONENTS}
)

set(PYBIND11_NOPYTHON ON)

add_subdirectory(third-party)

set(INCLUDE_DIR source/inc)

set(IMGUI_ROOT source/src)

set(IMGUI_CORE_ROOT ${IMGUI_ROOT}/imgui-core)
set(IMGUI_MOD ${IMGUI_CORE_ROOT}/modules)
set(IMGUI_WID ${IMGUI_MOD}/widgets)

set(IMNODES_ROOT ${IMGUI_ROOT}/imnodes)
set(IMNODES_MOD ${IMNODES_ROOT}/modules)

set(IMPLOT_ROOT ${IMGUI_ROOT}/implot)
set(IMPLOT_MOD ${IMPLOT_ROOT}/modules)

set(GLFW_ROOT ${IMGUI_ROOT}/glfw)

set(IMGUI_SRCS
    # Binder
    ${IMGUI_ROOT}/binder/enum-utility.cpp
    ${IMGUI_ROOT}/binder/wraps.cpp

    # Base Module definition
    ${IMGUI_ROOT}/bind-imgui.cpp

    # Imgui Core
    ${IMGUI_CORE_ROOT}/bind-imgui-core.cpp
        # Modules
        ${IMGUI_MOD}/cursor-layout.cpp
        ${IMGUI_MOD}/demos.cpp
        ${IMGUI_MOD}/drawlist.cpp
        ${IMGUI_MOD}/imgui-context.cpp
        ${IMGUI_MOD}/imgui-enums.cpp
        ${IMGUI_MOD}/imgui-structs.cpp
        ${IMGUI_MOD}/im-windows.cpp
        ${IMGUI_MOD}/stacks.cpp
        ${IMGUI_MOD}/styles.cpp

        # Widgets
        ${IMGUI_WID}/colors.cpp
        ${IMGUI_WID}/drag-inputs.cpp
        ${IMGUI_WID}/input.cpp
        ${IMGUI_WID}/main.cpp
        ${IMGUI_WID}/slide-inputs.cpp
        ${IMGUI_WID}/tables.cpp
        ${IMGUI_WID}/tabs.cpp
        ${IMGUI_WID}/text.cpp
        ${IMGUI_WID}/tree.cpp
        ${IMGUI_WID}/images.cpp

        # Backends
        # ${BE}/opengl3.cpp
        ${IMGUI_CORE_ROOT}/bind-backends/glfw.cpp

    # Imnodes
    ${IMNODES_ROOT}/bind-imnodes.cpp
        # Modules
        ${IMNODES_MOD}/imnodes-context.cpp
        ${IMNODES_MOD}/imnodes-enums.cpp
        ${IMNODES_MOD}/imnodes-structs.cpp

    # Implot
    ${IMPLOT_ROOT}/bind-implot.cpp
        # Modules
        ${IMPLOT_MOD}/implot-context.cpp
        ${IMPLOT_MOD}/implot-enums.cpp
        ${IMPLOT_MOD}/implot-structs.cpp
        ${IMPLOT_MOD}/implot-setup-funcs.cpp
        ${IMPLOT_MOD}/implot-plotting.cpp
        ${IMPLOT_MOD}/implot-tools.cpp
        ${IMPLOT_MOD}/implot-utils.cpp
        ${IMPLOT_MOD}/implot-colormap.cpp
        ${IMPLOT_MOD}/implot-misc.cpp

    # GLFW
    ${GLFW_ROOT}/bind-glfw.cpp
        ${GLFW_ROOT}/callbacks.cpp
        ${GLFW_ROOT}/constants.cpp
        ${GLFW_ROOT}/context.cpp
        ${GLFW_ROOT}/input.cpp
        ${GLFW_ROOT}/joystick.cpp
        ${GLFW_ROOT}/monitors.cpp
        ${GLFW_ROOT}/structs.cpp
        ${GLFW_ROOT}/windows.cpp

)

Python_add_library(imgui ${IMGUI_SRCS})
set_target_properties(imgui
    PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION ON
        VISIBILITY_INLINES_HIDDEN ON
        CXX_STANDARD 17
)

target_link_libraries(imgui
    PRIVATE
        pybind11::headers
        imgui-cpp
        glfw
        glad
        stb
)

target_include_directories(imgui
    PRIVATE
        ${INCLUDE_DIR}
)

target_compile_definitions(imgui
    PRIVATE PYBIND11_DETAILED_ERROR_MESSAGES
)

if(${MSVC})
    # PASS
else()
    target_compile_options(imgui
        PRIVATE
        -Wno-format-security
        -fvisibility=hidden
    )
endif()
