
set(MOD implot/src/modules)

list(APPEND ${PROJECT_NAME}_SRCS
    implot/src/bind-implot.cpp

    ${MOD}/implot-context.cpp
    ${MOD}/implot-enums.cpp
    ${MOD}/implot-structs.cpp
    ${MOD}/implot-setup-funcs.cpp
    ${MOD}/implot-plotting.cpp
    ${MOD}/implot-tools.cpp
    ${MOD}/implot-utils.cpp
    ${MOD}/implot-colormap.cpp
    ${MOD}/implot-misc.cpp
)