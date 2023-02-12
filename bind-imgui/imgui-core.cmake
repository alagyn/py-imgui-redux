set(MOD imgui-core/src/modules)
set(WID ${MOD}/widgets)

list(APPEND ${PROJECT_NAME}_SRCS
    imgui-core/src/bind-imgui.cpp

    # Modules
    ${MOD}/context.cpp
    ${MOD}/cursor-layout.cpp
    ${MOD}/demos.cpp
    ${MOD}/enums.cpp
    ${MOD}/im-windows.cpp
    ${MOD}/stacks.cpp
    ${MOD}/structs.cpp
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
)
