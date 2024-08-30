#include <bind-imgui/imgui-modules.h>
#include <binder/wraps.h>

void init_widgets_multi_select(py::module& m)
{
    m.def(
        IMFUNC(BeginMultiSelect),
        "flags"_a,
        "selection_size"_a = -1,
        "items_count"_a = -1,
        py::return_value_policy::reference
    );

    m.def(IMFUNC(EndMultiSelect), py::return_value_policy::reference);
    m.def(IMFUNC(SetNextItemSelectionUserData), "selection_user_data"_a);
    QUICK(IsItemToggledSelection);
}