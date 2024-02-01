# Set binder srcs
set(${PROJECT_NAME}_SRCS
    binder/src/bind-modules.cpp
    binder/src/enum-utility.cpp
    binder/src/wraps.cpp
)

include(imgui-core.cmake)
include(imnodes.cmake)
include(implot.cmake)

Python3_add_library(${PROJECT_NAME} ${${PROJECT_NAME}_SRCS})
set_target_properties(${PROJECT_NAME} PROPERTIES
    INTERPROCEDURAL_OPTIMIZATION ON
    VISIBILITY_INLINES_HIDDEN ON
    CXX_STANDARD 17
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    pybind11::headers
    imgui-cpp
    glfw
    glad
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
    PYBIND11_DETAILED_ERROR_MESSAGES
)

if(${MSVC})
else()
    target_compile_options(${PROJECT_NAME}
        PRIVATE
        -Wno-format-security
        -fvisibility=hidden
    )
endif()

install(
    TARGETS
    ${PROJECT_NAME}
    LIBRARY
    DESTINATION ${PROJECT_NAME}
)