#include <binder/inc/wraps.h>
#include <imgui-core/inc/imgui-modules.h>

void init_widgets_tree(py::module& m)
{
    m.def("TreeNode", py::overload_cast<const char*>(ImGui::TreeNode), "label"_a);
    // Leaving formatting to python
    m.def(
        "TreeNode",
        [](const char* str_id, const char* fmt)
        {
            return ImGui::TreeNode(str_id, fmt);
        },
        "str_id"_a,
        "fmt"_a
    );
    m.def(
        "TreeNodeEx",
        py::overload_cast<const char*, int>(ImGui::TreeNodeEx),
        "label"_a,
        "flags"_a = 0
    );
    // Leave formatting to python
    m.def(
        "TreeNodeEx",
        [](const char* str_id, const int flags, const char* fmt)
        {
            return ImGui::TreeNodeEx(str_id, flags, fmt);
        },
        "str_id"_a,
        "flags"_a,
        "fmt"_a
    );
    m.def("TreePush", py::overload_cast<const char*>(ImGui::TreePush), "str_id"_a);
    QUICK(TreePop);
    QUICK(GetTreeNodeToLabelSpacing);
    m.def(
        "CollapsingHeader",
        py::overload_cast<const char*, int>(ImGui::CollapsingHeader),
        "label"_a,
        "flags"_a = 0
    );
    m.def(
        "CollapsingHeader",
        [](const char* label, BoolRef p_visible, int flags)
        {
            return ImGui::CollapsingHeader(label, &p_visible->val, flags);
        },
        "label"_a,
        "p_visible"_a,
        "flags"_a = 0
    );
    m.def(IMFUNC(SetNextItemOpen), "is_open"_a, "cond"_a = 0);
}