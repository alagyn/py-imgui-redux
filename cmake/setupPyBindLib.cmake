#[[
Setup standard things for libs
Args:
LIB libname
SRCS srcs...
LINKS link libs...
INCS include dirs...
]]
function(setupPyBindLib)
    #set(options)
    set(single_args LIB)
    set(multivalue_args SRCS LINKS INCS)

    cmake_parse_arguments(ARGS "" "${single_args}" "${multivalue_args}" ${ARGN})

    Python3_add_library(${ARGS_LIB} ${ARGS_SRCS})
    set_target_properties(${ARGS_LIB}
        PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION ON
        VISIBILITY_INLINES_HIDDEN ON
        CXX_STANDARD 17
    )

    target_link_libraries(${ARGS_LIB}
        PRIVATE pybind11::headers ${ARGS_LINKS}
    )

    target_include_directories(${ARGS_LIB}
        PRIVATE ${ARGS_INCS}
    )

    target_compile_definitions(${ARGS_LIB}
        PRIVATE PYBIND11_DETAILED_ERROR_MESSAGES
    )

    if(${MSVC})
    else()
        target_compile_options(${ARGS_LIB}
            PRIVATE
            -Wno-format-security
            -fvisibility=hidden
        )
    endif()

endfunction()