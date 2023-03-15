#include <binder/inc/wraps.h>
#include <imnodes/inc/imnodes-modules.h>
#include <imnodes_internal.h>
#include <pybind11/stl.h>

void init_imnodes_context(py::module& m)
{
    // Define this with no data, it's opaque
    py::class_<ImNodesContext>(m, "Context");

    m.def(IMFUNC(CreateContext), py::return_value_policy::reference);
    m.def(IMFUNC(GetCurrentContext), py::return_value_policy::reference);
    m.def(IMFUNC(SetCurrentContext), "ctx"_a);
    m.def(IMFUNC(DestroyContext), "ctx"_a = nullptr);

    QUICK(EditorContextCreate);
    m.def(IMFUNC(EditorContextFree), "ctx"_a);
    m.def(IMFUNC(EditorContextSet), "ctx"_a);
    QUICK(EditorContextGetPanning);
    m.def(IMFUNC(EditorContextResetPanning), "pos"_a);
    m.def(IMFUNC(EditorContextMoveToNode), "node_id"_a);

    m.def(IMFUNC(GetIO), py::return_value_policy::reference);
    QUICK(GetStyle);
    m.def(IMFUNC(StyleColorsDark), "dest"_a = nullptr);
    m.def(IMFUNC(StyleColorsClassic), "dest"_a = nullptr);
    m.def(IMFUNC(StyleColorsLight), "dest"_a = nullptr);

    QUICK(BeginNodeEditor);
    QUICK(EndNodeEditor);

    // TODO wrap callbacks?
    m.def(
        "MiniMap",
        [](float size_fraction, ImNodesMiniMapLocation loc)
        {
            ImNodes::MiniMap(size_fraction, loc);
        },
        "size_fraction"_a = 0.2f,
        "location"_a = (int)ImNodesMiniMapLocation_TopLeft
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
        "shape"_a = (int)ImNodesPinShape_CircleFilled
    );
    QUICK(EndInputAttribute);

    m.def(
        IMFUNC(BeginOutputAttribute),
        "id"_a,
        "shape"_a = (int)ImNodesPinShape_CircleFilled
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
        [](IntList out)
        {
            out->resize(ImNodes::NumSelectedNodes());
            ImNodes::GetSelectedNodes(out->data());
        },
        "node_ids"_a
    );
    m.def(
        "GetSelectedLinks",
        [](IntList out)
        {
            out->resize(ImNodes::NumSelectedLinks());
            ImNodes::GetSelectedLinks(out->data());
        }
    );

    m.def(
        "ClearNodeSelection",
        [](std::optional<int> node_id)
        {
            if(node_id.has_value())
            {
                ImNodes::ClearNodeSelection(node_id.value());
            }
            else
            {
                ImNodes::ClearNodeSelection();
            }
        },
        "node_id"_a = std::nullopt
    );

    m.def(
        "ClearLinkSelection",
        [](std::optional<int> link_id)
        {
            if(link_id.has_value())
            {
                ImNodes::ClearLinkSelection(link_id.value());
            }
            else
            {
                ImNodes::ClearLinkSelection();
            }
        },
        "link_id"_a = std::nullopt
    );

    m.def(IMFUNC(SelectNode), "node_id"_a);
    m.def(IMFUNC(IsNodeSelected), "node_id"_a);

    m.def(IMFUNC(SelectLink), "link_id"_a);
    m.def(IMFUNC(IsLinkSelected), "link_id"_a);

    QUICK(IsAttributeActive);

    m.def(
        "IsAnyAttributeActive",
        [](IntRef attribute_id)
        {
            int* xxx = nullptr;
            if(attribute_id)
            {
                xxx = &(attribute_id->val);
            }

            return ImNodes::IsAnyAttributeActive(xxx);
        },
        "attribute_id"_a = nullptr,
        R"(
        Returns true if any attribute is active, I.E. clicked on.
        If not None, sets the passed reference to the ID of the active attribute.
        )"
    );

    m.def(
        "IsLinkStarted",
        [](IntRef attrId)
        {
            return ImNodes::IsLinkStarted(&attrId->val);
        },
        "started_at_attribute_id"_a,
        R"(
        Returns true if a new link has been started, but not completed.
        Sets the the passed reference to the ID of the starting attribute.
        )"
    );
    m.def(
        "IsLinkDropped",
        [](IntRef attrID, bool include_detach)
        {
            int* xxx;
            if(attrID)
            {
                xxx = &(attrID->val);
            }
            return ImNodes::IsLinkDropped(xxx, include_detach);
        },
        "started_at_attribute_id"_a = nullptr,
        "including_detached_links"_a = true,
        R"(
        Did the user drop the dragged link before attaching it to a pin?
        There are two different kinds of situations to consider when handling this event:
        1) a link which is created at a pin and then dropped
        2) an existing link which is detached from a pin and then dropped
        Use the including_detached_links flag to control whether this function triggers when the user
        detaches a link and drops it.
        )"
    );
    m.def(
        "IsLinkCreated",
        [](IntRef startAttrID, IntRef endAttrID, BoolRef madeFromSnap)
        {
            bool* xxx = nullptr;
            if(madeFromSnap)
            {
                xxx = &(madeFromSnap->val);
            }
            return ImNodes::IsLinkCreated(&startAttrID->val, &endAttrID->val, xxx);
        },
        "started_at_attribute_id"_a,
        "ended_at_attribute_id"_a,
        "created_from_snap"_a = nullptr
    );

    m.def(
        "IsLinkCreated",
        [](IntRef startNodeID,
           IntRef startAttrID,
           IntRef endNodeID,
           IntRef endAttrID,
           BoolRef madeFromSnap)
        {
            bool* xxx = nullptr;
            if(madeFromSnap)
            {
                xxx = &(madeFromSnap->val);
            }
            return ImNodes::IsLinkCreated(
                &startNodeID->val,
                &startAttrID->val,
                &endNodeID->val,
                &endAttrID->val,
                xxx
            );
        },
        "started_at_node_id"_a,
        "started_at_attribute_id"_a,
        "ended_at_node_id"_a,
        "ended_at_attribute_id"_a,
        "created_from_snap"_a = nullptr
    );

    m.def(
        "IsLinkDestroyed",
        [](IntRef linkID)
        {
            return ImNodes::IsLinkDestroyed(&linkID->val);
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