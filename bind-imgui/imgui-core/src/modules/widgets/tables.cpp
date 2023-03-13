#include <imgui-core/inc/imgui-modules.h>

void init_widgets_tables(py::module& m)
{
    m.def(
        IMFUNC(BeginTable),
        "str_id"_a,
        "column"_a,
        "flags"_a = 0,
        py::arg_v("outer_size", ImVec2(0, 0), "Vec2(0, 0)"),
        "inner_width"_a = 0.0f
    );
    QUICK(EndTable);
    m.def(IMFUNC(TableNextRow), "row_flags"_a = 0, "mind_row_height"_a = 0.0f);
    QUICK(TableNextColumn);
    m.def(IMFUNC(TableSetColumnIndex), "column_n"_a);

    m.def(
        IMFUNC(TableSetupColumn),
        "label"_a,
        "flags"_a = 0,
        "init_width_or_weight"_a = 0.0f,
        "user_id"_a = 0
    );
    m.def(IMFUNC(TableSetupScrollFreeze), "cols"_a, "rows"_a);
    QUICK(TableHeadersRow);
    m.def(IMFUNC(TableHeader), "label"_a);

    QUICK(TableGetSortSpecs);
    QUICK(TableGetColumnCount);
    QUICK(TableGetColumnIndex);
    QUICK(TableGetRowIndex);
    m.def(IMFUNC(TableGetColumnName), "column_n"_a = -1);
    m.def(IMFUNC(TableGetColumnFlags), "column_n"_a = -1);
    m.def(IMFUNC(TableSetColumnEnabled), "column_n"_a, "v"_a);
    m.def(IMFUNC(TableSetBgColor), "target"_a, "color"_a, "column_n"_a = -1);

    // Ignoring legacy Columns()
}