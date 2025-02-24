set(GENERATED_DIR ${CMAKE_BINARY_DIR}/generated)
set(GENERATED_INCLUDE_DIR ${GENERATED_DIR}/include)

file(MAKE_DIRECTORY ${GENERATED_INCLUDE_DIR})

function(AutoGenWrapper)
    set(options NO_FUNCS)
    set(oneValueArgs CONFIG_FILE INPUT_HEADER NAME SRCS)
    set(multiValueArgs DEFINES INCLUDES)
    cmake_parse_arguments(PARSE_ARGV 0 ARG
        "${options}" "${oneValueArgs}" "${multiValueArgs}"
    )

    if(NOT DEFINED ARG_CONFIG_FILE)
        message(FATAL_ERROR "AutoGenWrapper() Please supply arg CONFIG_FILE")
    endif()
    if(NOT DEFINED ARG_INPUT_HEADER)
        message(FATAL_ERROR "AutoGenWrapper() Please supply arg INPUT_HEADER")
    endif()
    if(NOT DEFINED ARG_NAME)
        message(FATAL_ERROR "AutoGenWrapper() Please supply arg NAME")
    endif()
    if(NOT DEFINED ARG_SRCS)
        message(FATAL_ERROR "AutoGenWrapper() Please supply arg SRCS")
    endif()

    message(STATUS "Adding Auto-Gen Name: ${ARG_NAME} Config: ${ARG_CONFIG_FILE} Header: ${ARG_INPUT_HEADER}")

    cmake_path(GET ARG_INPUT_HEADER FILENAME HEADER_BASE)
    set(PREPROC_HEADER ${CMAKE_BINARY_DIR}/generated/preprocessed_${HEADER_BASE})
    set(OUTPUT_ENUM_FILE ${GENERATED_DIR}/${ARG_NAME}-enums.cpp)
    set(OUTPUT_HEADER_FILE ${GENERATED_INCLUDE_DIR}/${ARG_NAME}.h)

    if(ARG_NO_FUNCS)
        unset(OUTPUT_FUNC_FILE)
        unset(OUTPUT_FUNC_ARG)
    else()
        set(OUTPUT_FUNC_FILE ${GENERATED_DIR}/${ARG_NAME}-funcs.cpp)
        set(OUTPUT_FUNC_ARG --func-out ${OUTPUT_FUNC_FILE})
    endif()

    if(MSVC)
        # TODO
    else()
        foreach(INC ${ARG_INCLUDES})
            list(APPEND INCLUDES -I${INC})
        endforeach()
        add_custom_command(
            OUTPUT ${PREPROC_HEADER}
            COMMAND
            ${CMAKE_CXX_COMPILER} -E -w ${ARG_DEFINES} ${INCLUDES} ${ARG_INPUT_HEADER} > ${PREPROC_HEADER}
        )
    endif()

    add_custom_command(
        DEPENDS 
            ${ARG_INPUT_HEADER}
            ${ARG_CONFIG_FILE}
            ${PREPROC_HEADER}
            ${CMAKE_SOURCE_DIR}/autogen/config.py
            ${CMAKE_SOURCE_DIR}/autogen/gen.py
            ${CMAKE_SOURCE_DIR}/autogen/parse_enums.py
            ${CMAKE_SOURCE_DIR}/autogen/parse_funcs.py
        OUTPUT 
            ${GENERATED_INCLUDE_DIR}/${ARG_NAME}.h
            ${OUTPUT_ENUM_FILE}
            ${OUTPUT_FUNC_FILE}
        COMMAND ${Python_EXECUTABLE} ${CMAKE_SOURCE_DIR}/autogen/gen.py
            ${ARG_CONFIG_FILE} ${PREPROC_HEADER}
            --header-out ${OUTPUT_HEADER_FILE}
            --enum-out ${OUTPUT_ENUM_FILE}
            ${OUTPUT_FUNC_ARG}
    )

    add_custom_target(${ARG_NAME}
        DEPENDS
        ${OUTPUT_HEADER_FILE}
        ${OUTPUT_ENUM_FILE}
        ${OUTPUT_FUNC_FILE}
    )

    set(${ARG_SRCS} ${${ARG_SRCS}} ${OUTPUT_ENUM_FILE} ${OUTPUT_FUNC_FILE} PARENT_SCOPE)
endfunction()