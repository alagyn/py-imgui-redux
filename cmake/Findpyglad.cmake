# this stuff is the same as Findpyglfw because they are packaged together
if(NOT pyglfw_ROOT OR NOT EXISTS ${pyglfw_ROOT})
    set(pyglfw_ROOT ${Python3_SITELIB} CACHE STRING "python sitelib")
endif()

if(NOT pyglad_VERSION)
    set(pyglad_VERSION 1.1.0)
endif()

if(MSVC)
    set(pyglad_GLOB "${pyglfw_ROOT}/glad.lib")
else()
    set(pyglad_GLOB "${pyglfw_ROOT}/py_glfw_redux.libs/libglad*.so")
endif()

file(GLOB pyglad_LIBRARY "${pyglad_GLOB}")

find_path(pyglad_INCLUDE
    glad/gl.h
    PATHS ${pyglfw_ROOT}/py-glfw-redux-${pyglad_VERSION}.inc/glad
    REQUIRED
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    pyglad
    REQUIRED_VARS
    pyglad_LIBRARY
    pyglad_INCLUDE
    VERSION_VAR
    pyglad_VERSION
)

if(pyglad_FOUND)
    if(NOT TARGET pyglad)
        add_library(pyglad INTERFACE)
        target_link_libraries(pyglad
            INTERFACE
            ${pyglad_LIBRARY}
        )
        target_include_directories(pyglad
            INTERFACE
            ${pyglad_INCLUDE}
        )
        target_compile_definitions(pyglad
            INTERFACE
            GLAD_API_CALL_EXPORT=1
        )

        if(MSVC)
            target_link_libraries(pyglad
                INTERFACE
                opengl32.lib
                gdi32.lib
                shell32.lib
            )
        else()
            find_package(OpenGL REQUIRED)
            target_link_libraries(pyglad
                INTERFACE
                ${OPENGL_LIBRARIES}
            )
        endif()
    endif()
endif()
