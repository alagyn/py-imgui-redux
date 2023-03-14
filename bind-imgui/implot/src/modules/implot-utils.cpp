#include <implot/inc/implot-modules.h>

#define STR(x) #x
#define AUTO_COL_STR STR(IMPLOT_AUTO_COL)

void init_utils(py::module& m)
{
    m.def(IMFUNC(SetAxis), "axis"_a);
    m.def(IMFUNC(SetAxes), "x_axis"_a, "y_axis"_a);

    m.def(
        "PixelsToPlot",
        py::overload_cast<const ImVec2&, ImAxis, ImAxis>(ImPlot::PixelsToPlot),
        "pix"_a,
        "x_axis"_a = IMPLOT_AUTO,
        "y_axis"_a = IMPLOT_AUTO
    );
    m.def(
        "PixelsToPlot",
        py::overload_cast<float, float, ImAxis, ImAxis>(ImPlot::PixelsToPlot),
        "x"_a,
        "y"_a,
        "x_axis"_a = IMPLOT_AUTO,
        "y_axis"_a = IMPLOT_AUTO
    );

    m.def(
        "PlotToPixels",
        py::overload_cast<const ImPlotPoint&, ImAxis, ImAxis>(ImPlot::PlotToPixels
        ),
        "plt"_a,
        "x_axis"_a = IMPLOT_AUTO,
        "y_axis"_a = IMPLOT_AUTO
    );

    m.def(
        "PlotToPixels",
        py::overload_cast<double, double, ImAxis, ImAxis>(ImPlot::PlotToPixels),
        "x"_a,
        "y"_a,
        "x_axis"_a = IMPLOT_AUTO,
        "y_axis"_a = IMPLOT_AUTO
    );

    QUICK(GetPlotPos);
    QUICK(GetPlotSize);

    m.def(
        IMFUNC(GetPlotMousePos),
        "x_axis"_a = IMPLOT_AUTO,
        "y_axis"_a = IMPLOT_AUTO
    );

    m.def(
        IMFUNC(GetPlotLimits),
        "x_axis"_a = IMPLOT_AUTO,
        "y_axis"_a = IMPLOT_AUTO
    );

    QUICK(IsPlotHovered);
    m.def(IMFUNC(IsAxisHovered), "axis"_a);
    QUICK(IsSubplotsHovered);
    QUICK(IsPlotSelected);
    m.def(
        IMFUNC(GetPlotSelection),
        "x_axis"_a = IMPLOT_AUTO,
        "y_axis"_a = IMPLOT_AUTO
    );
    QUICK(CancelPlotSelection);

    m.def(
        IMFUNC(HideNextItem),
        "hidden"_a = true,
        "cond"_a = (int)ImPlotCond_Once
    );
    m.def(IMFUNC(BeginAlignedPlots), "group_id"_a, "vertical"_a = true);

    // Legend utils
    m.def(
        IMFUNC(BeginLegendPopup),
        "label_id"_a,
        "mouse_button"_a = (int)ImGuiMouseButton_Right
    );
    QUICK(EndLegendPopup);
    m.def(IMFUNC(IsLegendEntryHovered), "label_id"_a);

    // Drag and drop
    QUICK(BeginDragDropTargetPlot);
    m.def(IMFUNC(BeginDragDropTargetAxis), "axis"_a);
    QUICK(BeginDragDropTargetLegend);
    QUICK(EndDragDropTarget);

    m.def(IMFUNC(BeginDragDropSourcePlot), "flags"_a = 0);
    m.def(IMFUNC(BeginDragDropSourceAxis), "axis"_a, "flags"_a = 0);
    m.def(IMFUNC(BeginDragDropSourceItem), "label_id"_a, "flags"_a = 0);
    QUICK(EndDragDropSource);

    // Styling
    QUICK(GetStyle);
    m.def(IMFUNC(StyleColorsAuto), "dst"_a = nullptr);
    m.def(IMFUNC(StyleColorsClassic), "dst"_a = nullptr);
    m.def(IMFUNC(StyleColorsDark), "dst"_a = nullptr);
    m.def(IMFUNC(StyleColorsLight), "dst"_a = nullptr);

    m.def(
        "PushStyleColor",
        py::overload_cast<ImPlotStyleVar, ImU32>(ImPlot::PushStyleColor),
        "idx"_a,
        "col"_a
    );
    m.def(
        "PushStyleColor",
        py::overload_cast<ImPlotStyleVar, const ImVec4&>(ImPlot::PushStyleColor),
        "idx"_a,
        "col"_a
    );
    m.def(IMFUNC(PopStyleColor), "count"_a = 1);

    m.def(
        "PushStyleVar",
        py::overload_cast<ImPlotStyleVar, int>(ImPlot::PushStyleVar),
        "idx"_a,
        "val"_a.noconvert()
    );
    m.def(
        "PushStyleVar",
        py::overload_cast<ImPlotStyleVar, float>(ImPlot::PushStyleVar),
        "idx"_a,
        "val"_a.noconvert()
    );
    m.def(
        "PushStyleVar",
        py::overload_cast<ImPlotStyleVar, const ImVec2&>(ImPlot::PushStyleVar),
        "idx"_a,
        "val"_a.noconvert()
    );
    m.def(IMFUNC(PopStyleVar), "count"_a = 1);

    m.def(
        IMFUNC(SetNextLineStyle),
        py::arg_v("col", IMPLOT_AUTO_COL, AUTO_COL_STR),
        "weight"_a = IMPLOT_AUTO
    );

    m.def(
        IMFUNC(SetNextFillStyle),
        py::arg_v("col", IMPLOT_AUTO_COL, AUTO_COL_STR),
        "alpha_mod"_a = IMPLOT_AUTO
    );

    m.def(
        IMFUNC(SetNextMarkerStyle),
        "marker"_a = IMPLOT_AUTO,
        "size"_a = IMPLOT_AUTO,
        py::arg_v("fill", IMPLOT_AUTO_COL, AUTO_COL_STR),
        "weight"_a = IMPLOT_AUTO,
        py::arg_v("outline", IMPLOT_AUTO_COL, AUTO_COL_STR)
    );

    m.def(
        IMFUNC(SetNextErrorBarStyle),
        py::arg_v("col", IMPLOT_AUTO_COL, AUTO_COL_STR),
        "size"_a = IMPLOT_AUTO,
        "weight"_a = IMPLOT_AUTO
    );

    QUICK(GetLastItemColor);
    m.def(IMFUNC(GetStyleColorName), "idx"_a);
    m.def(IMFUNC(GetMarkerName), "idx"_a);
}