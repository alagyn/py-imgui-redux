#include <modules.h>

void init_cursor_and_layout(py::module& m)
{
    QUICK(Separator);
    m.def(
        IMFUNC(SameLine),
        py::arg("offset_from_start_x") = 0.0f,
        py::arg("spacing") = 1.0f
    );
    QUICK(NewLine);
    QUICK(Spacing);
    m.def(IMFUNC(Dummy), py::arg("size"));
    m.def(IMFUNC(Indent), py::arg("indent_w") = 0.0f);
    m.def(IMFUNC(Unindent), py::arg("indent_w") = 0.0f);
    QUICK(BeginGroup);
    QUICK(EndGroup);
    QUICK(GetCursorPos);
    QUICK(GetCursorPosX);
    QUICK(GetCursorPosY);
    m.def(IMFUNC(SetCursorPos), py::arg("pos"));
    m.def(IMFUNC(SetCursorPosX), py::arg("local_x"));
    m.def(IMFUNC(SetCursorPosY), py::arg("local_y"));
    QUICK(GetCursorStartPos);
    QUICK(GetCursorScreenPos);
    m.def(IMFUNC(SetCursorScreenPos));
    QUICK(AlignTextToFramePadding);
    QUICK(GetTextLineHeight);
    QUICK(GetTextLineHeightWithSpacing);
    QUICK(GetFrameHeight);
    QUICK(GetFrameHeightWithSpacing);
}