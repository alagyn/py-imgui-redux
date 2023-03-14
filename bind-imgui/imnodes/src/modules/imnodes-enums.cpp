#include <binder/inc/enum-utility.h>
#include <imnodes.h>
#include <imnodes/inc/imnodes-modules.h>

void init_imnodes_enums(py::module& m)
{
    ENUM(ImNodes, Col)
        .VALUE(ImNodes, Col, NodeBackground)
        .VALUE(ImNodes, Col, NodeBackgroundHovered)
        .VALUE(ImNodes, Col, NodeBackgroundSelected)
        .VALUE(ImNodes, Col, NodeOutline)
        .VALUE(ImNodes, Col, TitleBar)
        .VALUE(ImNodes, Col, TitleBarHovered)
        .VALUE(ImNodes, Col, TitleBarSelected)
        .VALUE(ImNodes, Col, Link)
        .VALUE(ImNodes, Col, LinkHovered)
        .VALUE(ImNodes, Col, LinkSelected)
        .VALUE(ImNodes, Col, Pin)
        .VALUE(ImNodes, Col, PinHovered)
        .VALUE(ImNodes, Col, BoxSelector)
        .VALUE(ImNodes, Col, BoxSelectorOutline)
        .VALUE(ImNodes, Col, GridBackground)
        .VALUE(ImNodes, Col, GridLine)
        .VALUE(ImNodes, Col, GridLinePrimary)
        .VALUE(ImNodes, Col, MiniMapBackground)
        .VALUE(ImNodes, Col, MiniMapBackgroundHovered)
        .VALUE(ImNodes, Col, MiniMapOutline)
        .VALUE(ImNodes, Col, MiniMapOutlineHovered)
        .VALUE(ImNodes, Col, MiniMapNodeBackground)
        .VALUE(ImNodes, Col, MiniMapNodeBackgroundHovered)
        .VALUE(ImNodes, Col, MiniMapNodeBackgroundSelected)
        .VALUE(ImNodes, Col, MiniMapNodeOutline)
        .VALUE(ImNodes, Col, MiniMapLink)
        .VALUE(ImNodes, Col, MiniMapLinkSelected)
        .VALUE(ImNodes, Col, MiniMapCanvas)
        .VALUE(ImNodes, Col, MiniMapCanvasOutline);

    ENUM(ImNodes, StyleVar)
        .VALUE(ImNodes, StyleVar, GridSpacing)
        .VALUE(ImNodes, StyleVar, NodeCornerRounding)
        .VALUE(ImNodes, StyleVar, NodePadding)
        .VALUE(ImNodes, StyleVar, NodeBorderThickness)
        .VALUE(ImNodes, StyleVar, LinkThickness)
        .VALUE(ImNodes, StyleVar, LinkLineSegmentsPerLength)
        .VALUE(ImNodes, StyleVar, LinkHoverDistance)
        .VALUE(ImNodes, StyleVar, PinCircleRadius)
        .VALUE(ImNodes, StyleVar, PinQuadSideLength)
        .VALUE(ImNodes, StyleVar, PinTriangleSideLength)
        .VALUE(ImNodes, StyleVar, PinLineThickness)
        .VALUE(ImNodes, StyleVar, PinHoverRadius)
        .VALUE(ImNodes, StyleVar, PinOffset)
        .VALUE(ImNodes, StyleVar, MiniMapPadding)
        .VALUE(ImNodes, StyleVar, MiniMapOffset);

    ENUM(ImNodes, StyleFlags)
        .RAW_VALUE(None_, ImNodesStyleFlags_None)
        .VALUE(ImNodes, StyleFlags, NodeOutline)
        .VALUE(ImNodes, StyleFlags, GridLines)
        .VALUE(ImNodes, StyleFlags, GridLinesPrimary)
        .VALUE(ImNodes, StyleFlags, GridSnapping);

    ENUM(ImNodes, PinShape)
        .VALUE(ImNodes, PinShape, Circle)
        .VALUE(ImNodes, PinShape, CircleFilled)
        .VALUE(ImNodes, PinShape, Triangle)
        .VALUE(ImNodes, PinShape, TriangleFilled)
        .VALUE(ImNodes, PinShape, Quad)
        .VALUE(ImNodes, PinShape, QuadFilled);

    ENUM(ImNodes, AttributeFlags)
        .RAW_VALUE(None_, ImNodesAttributeFlags_None)
        .VALUE(ImNodes, AttributeFlags, EnableLinkDetachWithDragClick)
        .VALUE(ImNodes, AttributeFlags, EnableLinkCreationOnSnap);

    ENUM(ImNodes, MiniMapLocation)
        .VALUE(ImNodes, MiniMapLocation, BottomLeft)
        .VALUE(ImNodes, MiniMapLocation, BottomRight)
        .VALUE(ImNodes, MiniMapLocation, TopLeft)
        .VALUE(ImNodes, MiniMapLocation, TopRight);
}