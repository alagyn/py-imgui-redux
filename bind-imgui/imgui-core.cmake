set(MOD imgui-core/src/modules)
set(WID ${MOD}/widgets)
set(BE imgui-core/src/bind-backends)

list(APPEND ${PROJECT_NAME}_SRCS
    imgui-core/src/bind-imgui-core.cpp

    # Modules
    ${MOD}/cursor-layout.cpp
    ${MOD}/demos.cpp
    ${MOD}/drawlist.cpp
    ${MOD}/imgui-context.cpp
    ${MOD}/imgui-enums.cpp
    ${MOD}/imgui-structs.cpp
    ${MOD}/im-windows.cpp
    ${MOD}/stacks.cpp
    ${MOD}/styles.cpp

    # Widgets
    ${WID}/colors.cpp
    ${WID}/drag-inputs.cpp
    ${WID}/input.cpp
    ${WID}/main.cpp
    ${WID}/slide-inputs.cpp
    ${WID}/tables.cpp
    ${WID}/tabs.cpp
    ${WID}/text.cpp
    ${WID}/tree.cpp

    # Backends
    # ${BE}/opengl3.cpp
    ${BE}/glfw.cpp
)
