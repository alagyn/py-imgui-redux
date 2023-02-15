#include <binder/inc/def-utility.h>
#include <imnodes.h>
#include <imnodes/inc/imnodes-modules.h>

void init_imnodes_enums(py::module& m)
{
    py::enum_<ImNodesCol_>(m, "Col")
        .ENUM(ImNodesCol, NodeBackground)
        .ENUM(ImNodesCol, NodeBackgroundHovered)
        .ENUM(ImNodesCol, NodeBackgroundSelected)
        .ENUM(ImNodesCol, NodeOutline)
        .ENUM(ImNodesCol, TitleBar)
        .ENUM(ImNodesCol, TitleBarHovered)
        .ENUM(ImNodesCol, TitleBarSelected)
        .ENUM(ImNodesCol, Link)
        .ENUM(ImNodesCol, LinkHovered)
        .ENUM(ImNodesCol, LinkSelected)
        .ENUM(ImNodesCol, Pin)
        .ENUM(ImNodesCol, PinHovered)
        .ENUM(ImNodesCol, BoxSelector)
        .ENUM(ImNodesCol, BoxSelectorOutline)
        .ENUM(ImNodesCol, GridBackground)
        .ENUM(ImNodesCol, GridLine)
        .ENUM(ImNodesCol, GridLinePrimary)
        .ENUM(ImNodesCol, MiniMapBackground)
        .ENUM(ImNodesCol, MiniMapBackgroundHovered)
        .ENUM(ImNodesCol, MiniMapOutline)
        .ENUM(ImNodesCol, MiniMapOutlineHovered)
        .ENUM(ImNodesCol, MiniMapNodeBackground)
        .ENUM(ImNodesCol, MiniMapNodeBackgroundHovered)
        .ENUM(ImNodesCol, MiniMapNodeBackgroundSelected)
        .ENUM(ImNodesCol, MiniMapNodeOutline)
        .ENUM(ImNodesCol, MiniMapLink)
        .ENUM(ImNodesCol, MiniMapLinkSelected)
        .ENUM(ImNodesCol, MiniMapCanvas)
        .ENUM(ImNodesCol, MiniMapCanvasOutline);

    py::enum_<ImNodesStyleVar_>(m, "StyleVar")
        .ENUM(ImNodesStyleVar, GridSpacing)
        .ENUM(ImNodesStyleVar, NodeCornerRounding)
        .ENUM(ImNodesStyleVar, NodePadding)
        .ENUM(ImNodesStyleVar, NodeBorderThickness)
        .ENUM(ImNodesStyleVar, LinkThickness)
        .ENUM(ImNodesStyleVar, LinkLineSegmentsPerLength)
        .ENUM(ImNodesStyleVar, LinkHoverDistance)
        .ENUM(ImNodesStyleVar, PinCircleRadius)
        .ENUM(ImNodesStyleVar, PinQuadSideLength)
        .ENUM(ImNodesStyleVar, PinTriangleSideLength)
        .ENUM(ImNodesStyleVar, PinLineThickness)
        .ENUM(ImNodesStyleVar, PinHoverRadius)
        .ENUM(ImNodesStyleVar, PinOffset)
        .ENUM(ImNodesStyleVar, MiniMapPadding)
        .ENUM(ImNodesStyleVar, MiniMapOffset);

    py::enum_<ImNodesStyleFlags_>(m, "StyleFlags")
        .ENUM(ImNodesStyleFlags, None)
        .ENUM(ImNodesStyleFlags, NodeOutline)
        .ENUM(ImNodesStyleFlags, GridLines)
        .ENUM(ImNodesStyleFlags, GridLinesPrimary)
        .ENUM(ImNodesStyleFlags, GridSnapping);

    py::enum_<ImNodesPinShape_>(m, "PinShape")
        .ENUM(ImNodesPinShape, Circle)
        .ENUM(ImNodesPinShape, CircleFilled)
        .ENUM(ImNodesPinShape, Triangle)
        .ENUM(ImNodesPinShape, TriangleFilled)
        .ENUM(ImNodesPinShape, Quad)
        .ENUM(ImNodesPinShape, QuadFilled);

    py::enum_<ImNodesAttributeFlags_>(m, "AttributeFlags")
        .ENUM(ImNodesAttributeFlags, None)
        .ENUM(ImNodesAttributeFlags, EnableLinkDetachWithDragClick)
        .ENUM(ImNodesAttributeFlags, EnableLinkCreationOnSnap);

    py::enum_<ImNodesMiniMapLocation_>(m, "MinimapLocation")
        .ENUM(ImNodesMiniMapLocation, BottomLeft)
        .ENUM(ImNodesMiniMapLocation, BottomRight)
        .ENUM(ImNodesMiniMapLocation, TopLeft)
        .ENUM(ImNodesMiniMapLocation, TopRight);
}