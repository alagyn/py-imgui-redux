
set(MOD implot/src/modules)

list(APPEND ${PROJECT_NAME}_SRCS
    implot/src/bind-implot.cpp

    ${MOD}/implot-enums.cpp
    ${MOD}/implot-structs.cpp
)