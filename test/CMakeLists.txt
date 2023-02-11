
Python3_add_library(bdd
    src/test.cpp
)

target_include_directories(bdd PRIVATE inc)

target_link_libraries(bdd PRIVATE pybind11::headers)

set_target_properties(bdd PROPERTIES
    INTERPROCEDURAL_OPTIMIZATION ON
    CXX_VISIBILITY_PRESET ON
    VISIBILITY_INLINES_HIDDEN ON
    CXX_STANDARD 17
)