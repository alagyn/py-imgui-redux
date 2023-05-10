#include <binder/inc/struct-utility.h>
#include <imnodes/inc/imnodes-modules.h>

bool* getIOPointer(int key)
{
    bool* tgt = nullptr;
    switch(key)
    {
    case ImGuiMod_Ctrl:
        tgt = &ImGui::GetIO().KeyCtrl;
        break;
    case ImGuiMod_Alt:
        tgt = &ImGui::GetIO().KeyAlt;
        break;
    case ImGuiMod_Shift:
        tgt = &ImGui::GetIO().KeyShift;
        break;
    case ImGuiMod_Super:
        tgt = &ImGui::GetIO().KeySuper;
        break;
    default:
        throw std::runtime_error("Invalid modifier key");
    };
    return tgt;
}

void init_imnodes_structs(py::module& m)
{
    py::class_<ImNodesStyle>(m, "Style")
        .RW(ImNodesStyle, GridSpacing)
        .RW(ImNodesStyle, NodeCornerRounding)
        .RW(ImNodesStyle, NodePadding)
        .RW(ImNodesStyle, NodeBorderThickness)
        .RW(ImNodesStyle, LinkThickness)
        .RW(ImNodesStyle, LinkLineSegmentsPerLength)
        .RW(ImNodesStyle, LinkHoverDistance)
        .RW(ImNodesStyle, PinCircleRadius)
        .RW(ImNodesStyle, PinQuadSideLength)
        .RW(ImNodesStyle, PinTriangleSideLength)
        .RW(ImNodesStyle, PinLineThickness)
        .RW(ImNodesStyle, PinHoverRadius)
        .RW(ImNodesStyle, PinOffset)
        .RW(ImNodesStyle, MiniMapPadding)
        .RW(ImNodesStyle, MiniMapOffset)
        .RW(ImNodesStyle, Flags)
        .def(py::init<>());

    // TODO ImNodesIO
    py::class_<ImNodesIO>(m, "IO")
        .def(
            "SetEmulateThreeButtonMouseMod",
            [](ImNodesIO* self, ImGuiKey key)
            {
                self->EmulateThreeButtonMouse.Modifier = getIOPointer(key);
            },
            "key"_a
        )
        .def(
            "UnsetEmulateThreeButtonMouseMod",
            [](ImNodesIO* self)
            {
                self->EmulateThreeButtonMouse.Modifier = nullptr;
            }
        )
        .def(
            "SetLinkDetachedWithModifierClick",
            [](ImNodesIO* self, ImGuiKey key)
            {
                self->LinkDetachWithModifierClick.Modifier = getIOPointer(key);
            },
            "key"_a
        )
        .def(
            "UnsetLinkDetachedWithModifierClick",
            [](ImNodesIO* self)
            {
                self->LinkDetachWithModifierClick.Modifier = nullptr;
            }
        )
        .def(
            "SetMultipleSelectMod",
            [](ImNodesIO* self, ImGuiKey key)
            {
                self->MultipleSelectModifier.Modifier = getIOPointer(key);
            },
            "key"_a
        )
        .def(
            "UnsetMultipleSelectMod",
            [](ImNodesIO* self)
            {
                self->MultipleSelectModifier.Modifier = nullptr;
            }
        )
        .def(py::init<>());
}