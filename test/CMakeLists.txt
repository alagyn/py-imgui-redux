
Python3_add_library(test
    src/test.cpp
    src/bind-test1.cpp
    src/bind-test2.cpp
    src/bind-main.cpp
)

target_include_directories(test PRIVATE inc)

target_link_libraries(test PRIVATE pybind11::headers)

set_target_properties(test PROPERTIES
    INTERPROCEDURAL_OPTIMIZATION ON
    CXX_VISIBILITY_PRESET ON
    VISIBILITY_INLINES_HIDDEN ON)