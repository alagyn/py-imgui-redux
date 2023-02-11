
set(MOD src/modules)
set(WID ${MOD}/widgets)

set(${PROJECT_NAME}_SRCS
    src/bind-imgui.cpp

    # Modules
    ${MOD}/context.cpp
    ${MOD}/cursor-layout.cpp
    ${MOD}/demos.cpp
    ${MOD}/im-windows.cpp
    ${MOD}/stacks.cpp
    ${MOD}/structs.cpp
    ${MOD}/styles.cpp

    # Widgets
    ${WID}/drag-inputs.cpp
    ${WID}/input.cpp
    ${WID}/main.cpp
    ${WID}/slide-inputs.cpp
    ${WID}/text.cpp
)

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
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    inc
)