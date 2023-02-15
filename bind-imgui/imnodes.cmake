set(MOD imnodes/src/modules)

list(APPEND ${PROJECT_NAME}_SRCS
    imnodes/src/bind-imnodes.cpp

    ${MOD}/imnodes-context.cpp
    ${MOD}/imnodes-enums.cpp
    ${MOD}/imnodes-structs.cpp
)