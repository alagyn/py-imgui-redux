if(NOT pyglfw_ROOT OR NOT EXISTS ${pyglfw_ROOT})
    set(pyglfw_ROOT ${Python3_SITELIB} CACHE STRING "python sitelib")
endif()

if(MSVC)
    set(pyglfw_GLOB "${pyglfw_ROOT}/py_glfw_redux.libs/glfw*.dll")
else()
    set(pyglfw_GLOB "${pyglfw_ROOT}/py_glfw_redux.libs/libglfw*.so.*")
endif()

file(GLOB pyglfw_LIBRARY "${pyglfw_GLOB}")

find_path(pyglfw_INCLUDE
    GLFW/glfw3.h
    PATHS ${pyglfw_ROOT}/pyglfw/include
    REQUIRED
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    pyglfw
    REQUIRED_VARS
        pyglfw_LIBRARY
        pyglfw_INCLUDE
)

if(pyglfw_FOUND)
    if(NOT TARGET pyglfw)
        add_library(pyglfw INTERFACE)
        target_link_libraries(pyglfw INTERFACE ${pyglfw_LIBRARY})
        target_include_directories(pyglfw INTERFACE ${pyglfw_INCLUDE})
    endif()
endif()
