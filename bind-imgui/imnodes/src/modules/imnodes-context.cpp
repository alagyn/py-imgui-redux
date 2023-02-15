#include <imnodes/inc/imnodes-modules.h>
#include <imnodes_internal.h>

void init_imnodes_context(py::module& m)
{
    QUICK(CreateContext);
    m.def(IMFUNC(DestroyContext), "ctx"_a = nullptr);
    QUICK(GetCurrentContext);
    m.def(IMFUNC(SetCurrentContext), "ctx"_a);

    QUICK(EditorContextCreate);
    m.def(IMFUNC(EditorContextFree), "ctx"_a);
    m.def(IMFUNC(EditorContextSet), "ctx"_a);
    QUICK(EditorContextGetPanning);
    m.def(IMFUNC(EditorContextResetPanning), "pos"_a);
    m.def(IMFUNC(EditorContextMoveToNode), "node_id"_a);

    QUICK(GetIO);
    QUICK(GetStyle);
    m.def(IMFUNC(StyleColorsDark), "dest"_a = nullptr);
    m.def(IMFUNC(StyleColorsClassic), "dest"_a = nullptr);
    m.def(IMFUNC(StyleColorsLight), "dest"_a = nullptr);

    QUICK(BeginNodeEditor);
    QUICK(EndNodeEditor);

    // TODO wrap callbacks
    m.def(
        "MiniMap",
        [](float size_fraction, ImNodesMiniMapLocation loc)
        {
            ImNodes::MiniMap(size_fraction, loc);
        },
        "size_fraction"_a = 0.2f,
        "location"_a = ImNodesMiniMapLocation_TopLeft
    );

    m.def(IMFUNC(PushColorStyle), "item"_a, "color"_a);
    QUICK(PopColorStyle);
    m.def(
        "PushStyleVar",
        py::overload_cast<ImNodesStyleVar, float>(ImNodes::PushStyleVar),
        "style_item"_a,
        "value"_a
    );
    m.def(
        "PushStyleVar",
        py::overload_cast<ImNodesStyleVar, const ImVec2&>(ImNodes::PushStyleVar),
        "style_item"_a,
        "value"_a
    );
    m.def(IMFUNC(PopStyleVar), "count"_a = 1);

    // Nodes
    m.def(IMFUNC(BeginNode), "id"_a);
    QUICK(EndNode);
    m.def(IMFUNC(GetNodeDimensions), "id"_a);

    QUICK(BeginNodeTitleBar);
    QUICK(EndNodeTitleBar);

    // Attributes
    m.def(
        IMFUNC(BeginInputAttribute),
        "id"_a,
        "shape"_a = ImNodesPinShape_CircleFilled
    );
    QUICK(EndInputAttribute);

    m.def(
        IMFUNC(BeginOutputAttribute),
        "id"_a,
        "shape"_a = ImNodesPinShape_CircleFilled
    );
    QUICK(EndOutputAttribute);

    m.def(IMFUNC(BeginStaticAttribute), "id"_a);
    QUICK(EndStaticAttribute);

    m.def(IMFUNC(PushAttributeFlag), "flags"_a);
    QUICK(PopAttributeFlag);

    // Link
    m.def(IMFUNC(Link), "id"_a, "start_attribute_id"_a, "end_attribute_id"_a);

    m.def(IMFUNC(SetNodeDraggable), "node_id"_a, "draggable"_a);

    // Position
    m.def(IMFUNC(SetNodeScreenSpacePos), "node_id"_a, "scree_space_pos"_a);
    m.def(IMFUNC(SetNodeEditorSpacePos), "node_id"_a, "editor_space_pos"_a);
    m.def(IMFUNC(SetNodeGridSpacePos), "node_id"_a, "grid_pos"_a);

    m.def(IMFUNC(GetNodeScreenSpacePos), "node_id"_a);
    m.def(IMFUNC(GetNodeEditorSpacePos), "node_id"_a);
    m.def(IMFUNC(GetNodeGridSpacePos), "node_id"_a);

    m.def(IMFUNC(SnapNodeToGrid), "node_id"_a);

    // Interactions
    QUICK(IsEditorHovered);
    m.def(IMFUNC(IsNodeHovered), "node_id"_a);
    m.def(IMFUNC(IsLinkHovered), "link_id"_a);
    m.def(IMFUNC(IsPinHovered), "attribute_id"_a);

    QUICK(NumSelectedNodes);
    QUICK(NumSelectedLinks);

    m.def(
        "GetSelectedNodes",
        []()
        {
            std::vector<int> out(ImNodes::NumSelectedNodes(), 0);
            ImNodes::GetSelectedNodes(out.data());
            return out;
        }
    );
    m.def(
        "GetSelectedLinks",
        []()
        {
            std::vector<int> out(ImNodes::NumSelectedLinks(), 0);
            ImNodes::GetSelectedLinks(out.data());
            return out;
        }
    );

    m.def(
        "ClearNodeSelection",
        [](py::int_ node_id)
        {
            if(node_id.is_none())
            {
                ImNodes::ClearNodeSelection();
            }
            else
            {
                ImNodes::ClearNodeSelection(node_id.cast<int>());
            }
        },
        "node_id"_a = py::none()
    );

    m.def(
        "ClearLinkSelection",
        [](py::int_ link_id)
        {
            if(link_id.is_none())
            {
                ImNodes::ClearLinkSelection();
            }
            else
            {
                ImNodes::ClearLinkSelection(link_id.cast<int>());
            }
        },
        "link_id"_a = py::none()
    );

    m.def(IMFUNC(SelectNode), "node_id"_a);
    m.def(IMFUNC(IsNodeSelected), "node_id"_a);

    m.def(IMFUNC(SelectLink), "link_id"_a);
    m.def(IMFUNC(IsLinkSelected), "link_id"_a);

    QUICK(IsAttributeActive);
    m.def(
        "IsAnyAttributeActive",
        []()
        {
            int x = 0;
            bool out = ImNodes::IsAnyAttributeActive(&x);
            return py::make_tuple(out, x);
        }
    );

    m.def(
        "IsLinkStarted",
        []()
        {
            int x = 0;
            bool out = ImNodes::IsLinkStarted(&x);
            return py::make_tuple(out, x);
        }
    );
    m.def(
        "IsLinkDropped",
        [](bool include_detach)
        {
            int x = 0;
            bool out = ImNodes::IsLinkDropped(&x, include_detach);
            return py::make_tuple(out, x);
        },
        "including_detached_links"_a = true
    );
    m.def(
        "IsLinkCreated",
        []()
        {
            int startN = 0, startAttr = 0, endN = 0, endAttr = 0;
            bool createdFromSnap = false;
            bool out = ImNodes::IsLinkCreated(
                &startN,
                &startAttr,
                &endN,
                &endAttr,
                &createdFromSnap
            );

            return py::make_tuple(
                startN,
                startAttr,
                endN,
                endAttr,
                createdFromSnap
            );
        }
    );
    m.def(
        "IsLinkDestroyed",
        []()
        {
            int x = 0;
            bool out = ImNodes::IsLinkDestroyed(&x);
            return py::make_tuple(out, x);
        }
    );

    m.def(
        "SaveCurrentEditorStateToIniString",
        []()
        {
            return ImNodes::SaveCurrentEditorStateToIniString();
        }
    );
    m.def(
        "SaveEditStateToIniString",
        [](const ImNodesEditorContext* editor)
        {
            return ImNodes::SaveEditorStateToIniString(editor);
        }
    );

    m.def(IMFUNC(SaveCurrentEditorStateToIniFile), "file_name"_a);
    m.def(IMFUNC(SaveEditorStateToIniFile), "editor"_a, "file_name"_a);

    m.def(IMFUNC(LoadCurrentEditorStateFromIniFile), "file_name"_a);
    m.def(IMFUNC(LoadEditorStateFromIniFile), "editor"_a, "file_name"_a);
}