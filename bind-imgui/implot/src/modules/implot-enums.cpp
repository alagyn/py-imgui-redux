#include <binder/inc/enum-utility.h>
#include <implot/inc/implot-modules.h>

void init_implot_enums(py::module& m)
{
    ENUM(Im, Axis)
        .VALUE(Im, Axis, X1)
        .VALUE(Im, Axis, X2)
        .VALUE(Im, Axis, X3)
        .VALUE(Im, Axis, Y1)
        .VALUE(Im, Axis, Y2)
        .VALUE(Im, Axis, Y3);

    ENUM(Im, PlotFlags)
        .value("None_", 0)
        .VALUE(Im, PlotFlags, NoTitle)
        .VALUE(Im, PlotFlags, NoLegend)
        .VALUE(Im, PlotFlags, NoMouseText)
        .VALUE(Im, PlotFlags, NoInputs)
        .VALUE(Im, PlotFlags, NoMenus)
        .VALUE(Im, PlotFlags, NoBoxSelect)
        .VALUE(Im, PlotFlags, NoChild)
        .VALUE(Im, PlotFlags, NoFrame)
        .VALUE(Im, PlotFlags, Equal)
        .VALUE(Im, PlotFlags, Crosshairs)
        .VALUE(Im, PlotFlags, CanvasOnly);

    ENUM(ImPlot, AxisFlags)
        .value("None_", 0)
        .VALUE(ImPlot, AxisFlags, NoLabel)
        .VALUE(ImPlot, AxisFlags, NoGridLines)
        .VALUE(ImPlot, AxisFlags, NoTickMarks)
        .VALUE(ImPlot, AxisFlags, NoTickLabels)
        .VALUE(ImPlot, AxisFlags, NoInitialFit)
        .VALUE(ImPlot, AxisFlags, NoMenus)
        .VALUE(ImPlot, AxisFlags, NoSideSwitch)
        .VALUE(ImPlot, AxisFlags, NoHighlight)
        .VALUE(ImPlot, AxisFlags, Opposite)
        .VALUE(ImPlot, AxisFlags, Foreground)
        .VALUE(ImPlot, AxisFlags, Invert)
        .VALUE(ImPlot, AxisFlags, AutoFit)
        .VALUE(ImPlot, AxisFlags, RangeFit)
        .VALUE(ImPlot, AxisFlags, PanStretch)
        .VALUE(ImPlot, AxisFlags, LockMin)
        .VALUE(ImPlot, AxisFlags, LockMax)
        .VALUE(ImPlot, AxisFlags, Lock)
        .VALUE(ImPlot, AxisFlags, NoDecorations)
        .VALUE(ImPlot, AxisFlags, AuxDefault);

    ENUM(ImPlot, SubplotFlags)
        .value("None_", 0)
        .VALUE(ImPlot, SubplotFlags, NoTitle)
        .VALUE(ImPlot, SubplotFlags, NoLegend)
        .VALUE(ImPlot, SubplotFlags, NoMenus)
        .VALUE(ImPlot, SubplotFlags, NoResize)
        .VALUE(ImPlot, SubplotFlags, NoAlign)
        .VALUE(ImPlot, SubplotFlags, ShareItems)
        .VALUE(ImPlot, SubplotFlags, LinkRows)
        .VALUE(ImPlot, SubplotFlags, LinkCols)
        .VALUE(ImPlot, SubplotFlags, LinkAllX)
        .VALUE(ImPlot, SubplotFlags, LinkAllY)
        .VALUE(ImPlot, SubplotFlags, ColMajor);

    ENUM(ImPlot, LegendFlags)
        .value("None_", 0)
        .VALUE(ImPlot, LegendFlags, NoButtons)
        .VALUE(ImPlot, LegendFlags, NoHighlightItem)
        .VALUE(ImPlot, LegendFlags, NoHighlightAxis)
        .VALUE(ImPlot, LegendFlags, NoMenus)
        .VALUE(ImPlot, LegendFlags, Outside)
        .VALUE(ImPlot, LegendFlags, Horizontal)
        .VALUE(ImPlot, LegendFlags, Sort);

    ENUM(ImPlot, MouseTextFlags)
        .value("None_", 0)
        .VALUE(ImPlot, MouseTextFlags, NoAuxAxes)
        .VALUE(ImPlot, MouseTextFlags, NoFormat)
        .VALUE(ImPlot, MouseTextFlags, ShowAlways);

    ENUM(ImPlot, DragToolFlags)
        .value("None_", 0)
        .VALUE(ImPlot, DragToolFlags, NoCursors)
        .VALUE(ImPlot, DragToolFlags, NoFit)
        .VALUE(ImPlot, DragToolFlags, NoInputs)
        .VALUE(ImPlot, DragToolFlags, Delayed);

    ENUM(ImPlot, ItemFlags)
        .value("None_", 0)
        .VALUE(ImPlot, ItemFlags, NoLegend)
        .VALUE(ImPlot, ItemFlags, NoFit);

    ENUM(ImPlot, LineFlags)
        .value("None_", 0)
        .VALUE(ImPlot, LineFlags, Segments)
        .VALUE(ImPlot, LineFlags, Loop)
        .VALUE(ImPlot, LineFlags, SkipNaN)
        .VALUE(ImPlot, LineFlags, NoClip)
        .VALUE(ImPlot, LineFlags, Shaded);

    ENUM(ImPlot, ScatterFlags)
        .value("None_", 0)
        .VALUE(ImPlot, ScatterFlags, NoClip);

    ENUM(ImPlot, StairsFlags)
        .value("None_", 0)
        .VALUE(ImPlot, StairsFlags, PreStep)
        .VALUE(ImPlot, StairsFlags, Shaded);

    ENUM(ImPlot, ShadedFlags).value("None_", 0);

    ENUM(ImPlot, BarsFlags).value("None_", 0).VALUE(ImPlot, BarsFlags, Horizontal);

    ENUM(ImPlot, BarGroupsFlags)
        .value("None_", 0)
        .VALUE(ImPlot, BarGroupsFlags, Horizontal)
        .VALUE(ImPlot, BarGroupsFlags, Stacked);

    ENUM(ImPlot, ErrorBarsFlags)
        .value("None_", 0)
        .VALUE(ImPlot, ErrorBarsFlags, Horizontal);

    ENUM(ImPlot, StemsFlags)
        .value("None_", 0)
        .VALUE(ImPlot, StemsFlags, Horizontal);

    ENUM(ImPlot, InfLinesFlags)
        .value("None_", 0)
        .VALUE(ImPlot, InfLinesFlags, Horizontal);

    ENUM(ImPlot, PieChartFlags)
        .value("None_", 0)
        .VALUE(ImPlot, PieChartFlags, Normalize);

    ENUM(ImPlot, HeatmapFlags)
        .value("None_", 0)
        .VALUE(ImPlot, HeatmapFlags, ColMajor);

    ENUM(ImPlot, HistogramFlags)
        .value("None_", 0)
        .VALUE(ImPlot, HistogramFlags, Horizontal)
        .VALUE(ImPlot, HistogramFlags, Cumulative)
        .VALUE(ImPlot, HistogramFlags, Density)
        .VALUE(ImPlot, HistogramFlags, NoOutliers)
        .VALUE(ImPlot, HistogramFlags, ColMajor);

    ENUM(ImPlot, DigitalFlags).value("None_", 0);

    ENUM(ImPlot, ImageFlags).value("None_", 0);

    ENUM(ImPlot, TextFlags).value("None_", 0).VALUE(ImPlot, TextFlags, Vertical);

    ENUM(ImPlot, DummyFlags).value("None_", 0);

    ENUM(ImPlot, Cond)
        .value("None_", 0)
        .VALUE(ImPlot, Cond, Always)
        .VALUE(ImPlot, Cond, Once);

    ENUM(ImPlot, Col)
        .VALUE(ImPlot, Col, Line)
        .VALUE(ImPlot, Col, Fill)
        .VALUE(ImPlot, Col, MarkerOutline)
        .VALUE(ImPlot, Col, MarkerFill)
        .VALUE(ImPlot, Col, ErrorBar)
        .VALUE(ImPlot, Col, FrameBg)
        .VALUE(ImPlot, Col, PlotBg)
        .VALUE(ImPlot, Col, PlotBorder)
        .VALUE(ImPlot, Col, LegendBg)
        .VALUE(ImPlot, Col, LegendBorder)
        .VALUE(ImPlot, Col, LegendText)
        .VALUE(ImPlot, Col, TitleText)
        .VALUE(ImPlot, Col, InlayText)
        .VALUE(ImPlot, Col, AxisText)
        .VALUE(ImPlot, Col, AxisGrid)
        .VALUE(ImPlot, Col, AxisTick)
        .VALUE(ImPlot, Col, AxisBg)
        .VALUE(ImPlot, Col, AxisBgHovered)
        .VALUE(ImPlot, Col, AxisBgActive)
        .VALUE(ImPlot, Col, Selection)
        .VALUE(ImPlot, Col, Crosshairs);

    ENUM(ImPlot, StyleVar)
        .VALUE(ImPlot, StyleVar, LineWeight)
        .VALUE(ImPlot, StyleVar, Marker)
        .VALUE(ImPlot, StyleVar, MarkerSize)
        .VALUE(ImPlot, StyleVar, MarkerWeight)
        .VALUE(ImPlot, StyleVar, FillAlpha)
        .VALUE(ImPlot, StyleVar, ErrorBarSize)
        .VALUE(ImPlot, StyleVar, ErrorBarWeight)
        .VALUE(ImPlot, StyleVar, DigitalBitHeight)
        .VALUE(ImPlot, StyleVar, DigitalBitGap)
        .VALUE(ImPlot, StyleVar, PlotBorderSize)
        .VALUE(ImPlot, StyleVar, MinorAlpha)
        .VALUE(ImPlot, StyleVar, MajorTickLen)
        .VALUE(ImPlot, StyleVar, MinorTickLen)
        .VALUE(ImPlot, StyleVar, MajorTickSize)
        .VALUE(ImPlot, StyleVar, MinorTickSize)
        .VALUE(ImPlot, StyleVar, MajorGridSize)
        .VALUE(ImPlot, StyleVar, MinorGridSize)
        .VALUE(ImPlot, StyleVar, PlotPadding)
        .VALUE(ImPlot, StyleVar, LabelPadding)
        .VALUE(ImPlot, StyleVar, LegendPadding)
        .VALUE(ImPlot, StyleVar, LegendInnerPadding)
        .VALUE(ImPlot, StyleVar, LegendSpacing)
        .VALUE(ImPlot, StyleVar, MousePosPadding)
        .VALUE(ImPlot, StyleVar, AnnotationPadding)
        .VALUE(ImPlot, StyleVar, FitPadding)
        .VALUE(ImPlot, StyleVar, PlotDefaultSize)
        .VALUE(ImPlot, StyleVar, PlotMinSize);

    ENUM(ImPlot, Scale)
        .VALUE(ImPlot, Scale, Linear)
        .VALUE(ImPlot, Scale, Time)
        .VALUE(ImPlot, Scale, Log10)
        .VALUE(ImPlot, Scale, SymLog);

    ENUM(ImPlot, Marker)
        .value("None_", 0)
        .VALUE(ImPlot, Marker, Circle)
        .VALUE(ImPlot, Marker, Square)
        .VALUE(ImPlot, Marker, Diamond)
        .VALUE(ImPlot, Marker, Up)
        .VALUE(ImPlot, Marker, Down)
        .VALUE(ImPlot, Marker, Left)
        .VALUE(ImPlot, Marker, Right)
        .VALUE(ImPlot, Marker, Cross)
        .VALUE(ImPlot, Marker, Plus)
        .VALUE(ImPlot, Marker, Asterisk);

    RAW_ENUM(ImPlotColormap_, ColormapEnum)
        .VALUE(ImPlot, Colormap, Deep)
        .VALUE(ImPlot, Colormap, Dark)
        .VALUE(ImPlot, Colormap, Pastel)
        .VALUE(ImPlot, Colormap, Paired)
        .VALUE(ImPlot, Colormap, Viridis)
        .VALUE(ImPlot, Colormap, Plasma)
        .VALUE(ImPlot, Colormap, Hot)
        .VALUE(ImPlot, Colormap, Cool)
        .VALUE(ImPlot, Colormap, Pink)
        .VALUE(ImPlot, Colormap, Jet)
        .VALUE(ImPlot, Colormap, Twilight)
        .VALUE(ImPlot, Colormap, RdBu)
        .VALUE(ImPlot, Colormap, BrBG)
        .VALUE(ImPlot, Colormap, PiYG)
        .VALUE(ImPlot, Colormap, Spectral)
        .VALUE(ImPlot, Colormap, Greys);

    ENUM(ImPlot, Location)
        .VALUE(ImPlot, Location, Center)
        .VALUE(ImPlot, Location, North)
        .VALUE(ImPlot, Location, South)
        .VALUE(ImPlot, Location, West)
        .VALUE(ImPlot, Location, East)
        .VALUE(ImPlot, Location, NorthWest)
        .VALUE(ImPlot, Location, NorthEast)
        .VALUE(ImPlot, Location, SouthWest)
        .VALUE(ImPlot, Location, SouthEast);

    ENUM(ImPlot, Bin)
        .VALUE(ImPlot, Bin, Sqrt)
        .VALUE(ImPlot, Bin, Sturges)
        .VALUE(ImPlot, Bin, Rice)
        .VALUE(ImPlot, Bin, Scott);
}