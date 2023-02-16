#include <binder/inc/def-utility.h>
#include <implot/inc/implot-modules.h>

void init_implot_enums(py::module& m)
{
    py::enum_<ImAxis_>(m, "Axis")
        .ENUM(ImAxis, X1)
        .ENUM(ImAxis, X2)
        .ENUM(ImAxis, X3)
        .ENUM(ImAxis, Y1)
        .ENUM(ImAxis, Y2)
        .ENUM(ImAxis, Y3);

    py::enum_<ImPlotFlags_>(m, "PlotFlags")
        .ENUM(ImPlotFlags, None)
        .ENUM(ImPlotFlags, NoTitle)
        .ENUM(ImPlotFlags, NoLegend)
        .ENUM(ImPlotFlags, NoMouseText)
        .ENUM(ImPlotFlags, NoInputs)
        .ENUM(ImPlotFlags, NoMenus)
        .ENUM(ImPlotFlags, NoBoxSelect)
        .ENUM(ImPlotFlags, NoChild)
        .ENUM(ImPlotFlags, NoFrame)
        .ENUM(ImPlotFlags, Equal)
        .ENUM(ImPlotFlags, Crosshairs)
        .ENUM(ImPlotFlags, CanvasOnly);

    py::enum_<ImPlotAxisFlags_>(m, "AxisFlags")
        .ENUM(ImPlotAxisFlags, None)
        .ENUM(ImPlotAxisFlags, NoLabel)
        .ENUM(ImPlotAxisFlags, NoGridLines)
        .ENUM(ImPlotAxisFlags, NoTickMarks)
        .ENUM(ImPlotAxisFlags, NoTickLabels)
        .ENUM(ImPlotAxisFlags, NoInitialFit)
        .ENUM(ImPlotAxisFlags, NoMenus)
        .ENUM(ImPlotAxisFlags, NoSideSwitch)
        .ENUM(ImPlotAxisFlags, NoHighlight)
        .ENUM(ImPlotAxisFlags, Opposite)
        .ENUM(ImPlotAxisFlags, Foreground)
        .ENUM(ImPlotAxisFlags, Invert)
        .ENUM(ImPlotAxisFlags, AutoFit)
        .ENUM(ImPlotAxisFlags, RangeFit)
        .ENUM(ImPlotAxisFlags, PanStretch)
        .ENUM(ImPlotAxisFlags, LockMin)
        .ENUM(ImPlotAxisFlags, LockMax)
        .ENUM(ImPlotAxisFlags, Lock)
        .ENUM(ImPlotAxisFlags, NoDecorations)
        .ENUM(ImPlotAxisFlags, AuxDefault);

    py::enum_<ImPlotSubplotFlags_>(m, "SubplotFlags")
        .ENUM(ImPlotSubplotFlags, None)
        .ENUM(ImPlotSubplotFlags, NoTitle)
        .ENUM(ImPlotSubplotFlags, NoLegend)
        .ENUM(ImPlotSubplotFlags, NoMenus)
        .ENUM(ImPlotSubplotFlags, NoResize)
        .ENUM(ImPlotSubplotFlags, NoAlign)
        .ENUM(ImPlotSubplotFlags, ShareItems)
        .ENUM(ImPlotSubplotFlags, LinkRows)
        .ENUM(ImPlotSubplotFlags, LinkCols)
        .ENUM(ImPlotSubplotFlags, LinkAllX)
        .ENUM(ImPlotSubplotFlags, LinkAllY)
        .ENUM(ImPlotSubplotFlags, ColMajor);

    py::enum_<ImPlotLegendFlags_>(m, "LegendFlags")
        .ENUM(ImPlotLegendFlags, None)
        .ENUM(ImPlotLegendFlags, NoButtons)
        .ENUM(ImPlotLegendFlags, NoHighlightItem)
        .ENUM(ImPlotLegendFlags, NoHighlightAxis)
        .ENUM(ImPlotLegendFlags, NoMenus)
        .ENUM(ImPlotLegendFlags, Outside)
        .ENUM(ImPlotLegendFlags, Horizontal)
        .ENUM(ImPlotLegendFlags, Sort);

    py::enum_<ImPlotMouseTextFlags_>(m, "MouseTextFlags")
        .ENUM(ImPlotMouseTextFlags, None)
        .ENUM(ImPlotMouseTextFlags, NoAuxAxes)
        .ENUM(ImPlotMouseTextFlags, NoFormat)
        .ENUM(ImPlotMouseTextFlags, ShowAlways);

    py::enum_<ImPlotDragToolFlags_>(m, "DragToolFlags")
        .ENUM(ImPlotDragToolFlags, None)
        .ENUM(ImPlotDragToolFlags, NoCursors)
        .ENUM(ImPlotDragToolFlags, NoFit)
        .ENUM(ImPlotDragToolFlags, NoInputs)
        .ENUM(ImPlotDragToolFlags, Delayed);

    py::enum_<ImPlotItemFlags_>(m, "ItemFlags")
        .ENUM(ImPlotItemFlags, None)
        .ENUM(ImPlotItemFlags, NoLegend)
        .ENUM(ImPlotItemFlags, NoFit);

    py::enum_<ImPlotLineFlags_>(m, "LineFlags")
        .ENUM(ImPlotLineFlags, None)
        .ENUM(ImPlotLineFlags, Segments)
        .ENUM(ImPlotLineFlags, Loop)
        .ENUM(ImPlotLineFlags, SkipNaN)
        .ENUM(ImPlotLineFlags, NoClip)
        .ENUM(ImPlotLineFlags, Shaded);

    py::enum_<ImPlotScatterFlags_>(m, "ScatterFlags")
        .ENUM(ImPlotScatterFlags, None)
        .ENUM(ImPlotScatterFlags, NoClip);

    py::enum_<ImPlotStairsFlags_>(m, "StairsFlags")
        .ENUM(ImPlotStairsFlags, None)
        .ENUM(ImPlotStairsFlags, PreStep)
        .ENUM(ImPlotStairsFlags, Shaded);

    py::enum_<ImPlotShadedFlags_>(m, "ShadedFlags").ENUM(ImPlotShadedFlags, None);

    py::enum_<ImPlotBarsFlags_>(m, "BarsFlags")
        .ENUM(ImPlotBarsFlags, None)
        .ENUM(ImPlotBarsFlags, Horizontal);

    py::enum_<ImPlotBarGroupsFlags_>(m, "BarGroupsFlags")
        .ENUM(ImPlotBarGroupsFlags, None)
        .ENUM(ImPlotBarGroupsFlags, Horizontal)
        .ENUM(ImPlotBarGroupsFlags, Stacked);

    py::enum_<ImPlotErrorBarsFlags_>(m, "ErrorBarsFlags")
        .ENUM(ImPlotErrorBarsFlags, None)
        .ENUM(ImPlotErrorBarsFlags, Horizontal);

    py::enum_<ImPlotStemsFlags_>(m, "StemsFlags")
        .ENUM(ImPlotStemsFlags, None)
        .ENUM(ImPlotStemsFlags, Horizontal);

    py::enum_<ImPlotInfLinesFlags_>(m, "InfLineFlags")
        .ENUM(ImPlotInfLinesFlags, None)
        .ENUM(ImPlotInfLinesFlags, Horizontal);

    py::enum_<ImPlotPieChartFlags_>(m, "PieCharFlags")
        .ENUM(ImPlotPieChartFlags, None)
        .ENUM(ImPlotPieChartFlags, Normalize);

    py::enum_<ImPlotHeatmapFlags_>(m, "HeatmapFlags")
        .ENUM(ImPlotHeatmapFlags, None)
        .ENUM(ImPlotHeatmapFlags, ColMajor);

    py::enum_<ImPlotHistogramFlags_>(m, "HistogramFlags")
        .ENUM(ImPlotHistogramFlags, None)
        .ENUM(ImPlotHistogramFlags, Horizontal)
        .ENUM(ImPlotHistogramFlags, Cumulative)
        .ENUM(ImPlotHistogramFlags, Density)
        .ENUM(ImPlotHistogramFlags, NoOutliers)
        .ENUM(ImPlotHistogramFlags, ColMajor);

    py::enum_<ImPlotDigitalFlags_>(m, "DigitalFlags")
        .ENUM(ImPlotDigitalFlags, None);

    py::enum_<ImPlotImageFlags_>(m, "ImageFlags").ENUM(ImPlotImageFlags, None);

    py::enum_<ImPlotTextFlags_>(m, "TextFlags")
        .ENUM(ImPlotTextFlags, None)
        .ENUM(ImPlotTextFlags, Vertical);

    py::enum_<ImPlotDummyFlags_>(m, "DummyFlags").ENUM(ImPlotDummyFlags, None);

    py::enum_<ImPlotCond_>(m, "Cond")
        .ENUM(ImPlotCond, None)
        .ENUM(ImPlotCond, Always)
        .ENUM(ImPlotCond, Once);

    py::enum_<ImPlotCol_>(m, "Col")
        .ENUM(ImPlotCol, Line)
        .ENUM(ImPlotCol, Fill)
        .ENUM(ImPlotCol, MarkerOutline)
        .ENUM(ImPlotCol, MarkerFill)
        .ENUM(ImPlotCol, ErrorBar)
        .ENUM(ImPlotCol, FrameBg)
        .ENUM(ImPlotCol, PlotBg)
        .ENUM(ImPlotCol, PlotBorder)
        .ENUM(ImPlotCol, LegendBg)
        .ENUM(ImPlotCol, LegendBorder)
        .ENUM(ImPlotCol, LegendText)
        .ENUM(ImPlotCol, TitleText)
        .ENUM(ImPlotCol, InlayText)
        .ENUM(ImPlotCol, AxisText)
        .ENUM(ImPlotCol, AxisGrid)
        .ENUM(ImPlotCol, AxisTick)
        .ENUM(ImPlotCol, AxisBg)
        .ENUM(ImPlotCol, AxisBgHovered)
        .ENUM(ImPlotCol, AxisBgActive)
        .ENUM(ImPlotCol, Selection)
        .ENUM(ImPlotCol, Crosshairs);

    py::enum_<ImPlotStyleVar_>(m, "StyleVar")
        .ENUM(ImPlotStyleVar, LineWeight)
        .ENUM(ImPlotStyleVar, Marker)
        .ENUM(ImPlotStyleVar, MarkerSize)
        .ENUM(ImPlotStyleVar, MarkerWeight)
        .ENUM(ImPlotStyleVar, FillAlpha)
        .ENUM(ImPlotStyleVar, ErrorBarSize)
        .ENUM(ImPlotStyleVar, ErrorBarWeight)
        .ENUM(ImPlotStyleVar, DigitalBitHeight)
        .ENUM(ImPlotStyleVar, DigitalBitGap)
        .ENUM(ImPlotStyleVar, PlotBorderSize)
        .ENUM(ImPlotStyleVar, MinorAlpha)
        .ENUM(ImPlotStyleVar, MajorTickLen)
        .ENUM(ImPlotStyleVar, MinorTickLen)
        .ENUM(ImPlotStyleVar, MajorTickSize)
        .ENUM(ImPlotStyleVar, MinorTickSize)
        .ENUM(ImPlotStyleVar, MajorGridSize)
        .ENUM(ImPlotStyleVar, MinorGridSize)
        .ENUM(ImPlotStyleVar, PlotPadding)
        .ENUM(ImPlotStyleVar, LabelPadding)
        .ENUM(ImPlotStyleVar, LegendPadding)
        .ENUM(ImPlotStyleVar, LegendInnerPadding)
        .ENUM(ImPlotStyleVar, LegendSpacing)
        .ENUM(ImPlotStyleVar, MousePosPadding)
        .ENUM(ImPlotStyleVar, AnnotationPadding)
        .ENUM(ImPlotStyleVar, FitPadding)
        .ENUM(ImPlotStyleVar, PlotDefaultSize)
        .ENUM(ImPlotStyleVar, PlotMinSize);

    py::enum_<ImPlotScale_>(m, "Scale")
        .ENUM(ImPlotScale, Linear)
        .ENUM(ImPlotScale, Time)
        .ENUM(ImPlotScale, Log10)
        .ENUM(ImPlotScale, SymLog);

    py::enum_<ImPlotMarker_>(m, "Marker")
        .ENUM(ImPlotMarker, None)
        .ENUM(ImPlotMarker, Circle)
        .ENUM(ImPlotMarker, Square)
        .ENUM(ImPlotMarker, Diamond)
        .ENUM(ImPlotMarker, Up)
        .ENUM(ImPlotMarker, Down)
        .ENUM(ImPlotMarker, Left)
        .ENUM(ImPlotMarker, Right)
        .ENUM(ImPlotMarker, Cross)
        .ENUM(ImPlotMarker, Plus)
        .ENUM(ImPlotMarker, Asterisk);

    py::enum_<ImPlotColormap_>(m, "ColorMap")
        .ENUM(ImPlotColormap, Deep)
        .ENUM(ImPlotColormap, Dark)
        .ENUM(ImPlotColormap, Pastel)
        .ENUM(ImPlotColormap, Paired)
        .ENUM(ImPlotColormap, Viridis)
        .ENUM(ImPlotColormap, Plasma)
        .ENUM(ImPlotColormap, Hot)
        .ENUM(ImPlotColormap, Cool)
        .ENUM(ImPlotColormap, Pink)
        .ENUM(ImPlotColormap, Jet)
        .ENUM(ImPlotColormap, Twilight)
        .ENUM(ImPlotColormap, RdBu)
        .ENUM(ImPlotColormap, BrBG)
        .ENUM(ImPlotColormap, PiYG)
        .ENUM(ImPlotColormap, Spectral)
        .ENUM(ImPlotColormap, Greys);

    py::enum_<ImPlotLocation_>(m, "Location")
        .ENUM(ImPlotLocation, Center)
        .ENUM(ImPlotLocation, North)
        .ENUM(ImPlotLocation, South)
        .ENUM(ImPlotLocation, West)
        .ENUM(ImPlotLocation, East)
        .ENUM(ImPlotLocation, NorthWest)
        .ENUM(ImPlotLocation, NorthEast)
        .ENUM(ImPlotLocation, SouthWest)
        .ENUM(ImPlotLocation, SouthEast);

    py::enum_<ImPlotBin_>(m, "Bin")
        .ENUM(ImPlotBin, Sqrt)
        .ENUM(ImPlotBin, Sturges)
        .ENUM(ImPlotBin, Rice)
        .ENUM(ImPlotBin, Scott);
}