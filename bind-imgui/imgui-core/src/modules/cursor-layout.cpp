#include <imgui-core/inc/imgui-modules.h>

void init_cursor_and_layout(py::module& m)
{
    QUICK(Separator);
    m.def(IMFUNC(SameLine), "offset_from_start_x"_a = 0.0f, "spacing"_a = 1.0f);
    QUICK(NewLine);
    QUICK(Spacing);
    m.def(IMFUNC(Dummy), "size"_a);
    m.def(IMFUNC(Indent), "indent_w"_a = 0.0f);
    m.def(IMFUNC(Unindent), "indent_w"_a = 0.0f);
    QUICK(BeginGroup);
    QUICK(EndGroup);
    QUICK(GetCursorPos);
    QUICK(GetCursorPosX);
    QUICK(GetCursorPosY);
    m.def(IMFUNC(SetCursorPos), "pos"_a);
    m.def(IMFUNC(SetCursorPosX), "local_x"_a);
    m.def(IMFUNC(SetCursorPosY), "local_y"_a);
    QUICK(GetCursorStartPos);
    QUICK(GetCursorScreenPos);
    m.def(IMFUNC(SetCursorScreenPos));
    QUICK(AlignTextToFramePadding);
    QUICK(GetTextLineHeight);
    QUICK(GetTextLineHeightWithSpacing);
    QUICK(GetFrameHeight);
    QUICK(GetFrameHeightWithSpacing);
}