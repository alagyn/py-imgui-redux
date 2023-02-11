#include <modules.h>

void init_widgets_main(py::module& m)
{
    m.def(IMFUNC(Button), py::arg("label"), py::arg("size") = ImVec2(0, 0));
    m.def(IMFUNC(SmallButton), py::arg("label"));
    m.def(
        IMFUNC(InvisibleButton),
        py::arg("str_id"),
        py::arg("size"),
        py::arg("flags") = 0
    );
    m.def(IMFUNC(ArrowButton), py::arg("str_id"), py::arg("dir"));
    m.def(
        "CheckBox",
        [](const char* label, bool cur_state) -> py::tuple
        {
            bool pressed = ImGui::Checkbox(label, &cur_state);
            return py::make_tuple(pressed, cur_state);
        },
        py::arg("label"),
        py::arg("cur_state")
    );
    m.def(
        "CheckBoxFlags",
        [](const char* label, int cur_flags, int flags_mask) -> py::tuple
        {
            bool pressed = ImGui::CheckboxFlags(label, &cur_flags, flags_mask);
            return py::make_tuple(pressed, cur_flags);
        },
        py::arg("label"),
        py::arg("cur_flags"),
        py::arg("flags_mask")
    );
    m.def(
        "RadioButton",
        py::overload_cast<const char*, bool>(ImGui::RadioButton),
        py::arg("label"),
        py::arg("value")
    );
    m.def(
        IMFUNC(ProgressBar),
        py::arg("fraction"),
        py::arg("size_arg") = ImVec2(-FLT_MIN, 0),
        py::arg("overlay") = nullptr
    );
    QUICK(Bullet);

    // TODO Images

    // Combo
    m.def(
        IMFUNC(BeginCombo),
        py::arg("label"),
        py::arg("preview_value"),
        py::arg("flag") = 0
    );
    QUICK(EndCombo);
    // Ignoring old Combo() funcs
    // Use Selectable instead

    // Listbox
    m.def(IMFUNC(BeginListBox), py::arg("label"), py::arg("size"));
    QUICK(EndListBox);
    // Ignoreing old ListBox() funcs
    // Use Selectable instead
}