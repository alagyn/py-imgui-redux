#include <binder/inc/struct-utility.h>
#include <imnodes/inc/imnodes-modules.h>

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
}