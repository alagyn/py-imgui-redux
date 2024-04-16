if(NOT pyglfw_ROOT OR NOT EXISTS ${pyglfw_ROOT})
    set(pyglfw_ROOT ${Python3_SITELIB} CACHE STRING "python sitelib")
endif()

if(NOT pyglfw_VERSION)
    set(pyglfw_VERSION 1.1.0)
endif()

if(MSVC)
    set(pyglfw_GLOB "${pyglfw_ROOT}/glfw3dll.lib")
else()
    set(pyglfw_GLOB "${pyglfw_ROOT}/py*glfw*redux.libs/libglfw*.so.*")
endif()

file(GLOB pyglfw_LIBRARY "${pyglfw_GLOB}")

find_path(pyglfw_INCLUDE
    GLFW/glfw3.h
    PATHS 
        ${pyglfw_ROOT}/py-glfw-redux-${pyglfw_VERSION}.inc/glfw
        ${pyglfw_ROOT}/py_glfw_redux-${pyglfw_VERSION}.inc/glfw
    REQUIRED
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    pyglfw
    REQUIRED_VARS
    pyglfw_LIBRARY
    pyglfw_INCLUDE
    VERSION_VAR
    pyglfw_VERSION
)

if(pyglfw_FOUND)
    if(NOT TARGET pyglfw)
        add_library(pyglfw INTERFACE)
        target_link_libraries(pyglfw
            INTERFACE
            ${pyglfw_LIBRARY}
        )
        target_include_directories(pyglfw
            INTERFACE
            ${pyglfw_INCLUDE}
        )

        if(MSVC)
            target_link_libraries(pyglfw
                INTERFACE
                opengl32.lib
                gdi32.lib
                shell32.lib
            )
        else()
            find_package(OpenGL REQUIRED)
            target_link_libraries(pyglfw
                INTERFACE
                ${OPENGL_LIBRARIES}
            )
        endif()

        target_link_libraries(pyglfw
            INTERFACE
            ${Python3_LIBRARIES}
        )
    endif()
endif()
