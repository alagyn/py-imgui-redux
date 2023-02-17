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
        .VALUE(Im, PlotFlags, None)
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
        .VALUE(ImPlot, AxisFlags, None)
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
        .VALUE(ImPlot, SubplotFlags, None)
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
        .VALUE(ImPlot, LegendFlags, None)
        .VALUE(ImPlot, LegendFlags, NoButtons)
        .VALUE(ImPlot, LegendFlags, NoHighlightItem)
        .VALUE(ImPlot, LegendFlags, NoHighlightAxis)
        .VALUE(ImPlot, LegendFlags, NoMenus)
        .VALUE(ImPlot, LegendFlags, Outside)
        .VALUE(ImPlot, LegendFlags, Horizontal)
        .VALUE(ImPlot, LegendFlags, Sort);

    ENUM(ImPlot, MouseTextFlags)
        .VALUE(ImPlot, MouseTextFlags, None)
        .VALUE(ImPlot, MouseTextFlags, NoAuxAxes)
        .VALUE(ImPlot, MouseTextFlags, NoFormat)
        .VALUE(ImPlot, MouseTextFlags, ShowAlways);

    ENUM(ImPlot, DragToolFlags)
        .VALUE(ImPlot, DragToolFlags, None)
        .VALUE(ImPlot, DragToolFlags, NoCursors)
        .VALUE(ImPlot, DragToolFlags, NoFit)
        .VALUE(ImPlot, DragToolFlags, NoInputs)
        .VALUE(ImPlot, DragToolFlags, Delayed);

    ENUM(ImPlot, ItemFlags)
        .VALUE(ImPlot, ItemFlags, None)
        .VALUE(ImPlot, ItemFlags, NoLegend)
        .VALUE(ImPlot, ItemFlags, NoFit);

    ENUM(ImPlot, LineFlags)
        .VALUE(ImPlot, LineFlags, None)
        .VALUE(ImPlot, LineFlags, Segments)
        .VALUE(ImPlot, LineFlags, Loop)
        .VALUE(ImPlot, LineFlags, SkipNaN)
        .VALUE(ImPlot, LineFlags, NoClip)
        .VALUE(ImPlot, LineFlags, Shaded);

    ENUM(ImPlot, ScatterFlags)
        .VALUE(ImPlot, ScatterFlags, None)
        .VALUE(ImPlot, ScatterFlags, NoClip);

    ENUM(ImPlot, StairsFlags)
        .VALUE(ImPlot, StairsFlags, None)
        .VALUE(ImPlot, StairsFlags, PreStep)
        .VALUE(ImPlot, StairsFlags, Shaded);

    ENUM(ImPlot, ShadedFlags).VALUE(ImPlot, ShadedFlags, None);

    ENUM(ImPlot, BarsFlags)
        .VALUE(ImPlot, BarsFlags, None)
        .VALUE(ImPlot, BarsFlags, Horizontal);

    ENUM(ImPlot, BarGroupsFlags)
        .VALUE(ImPlot, BarGroupsFlags, None)
        .VALUE(ImPlot, BarGroupsFlags, Horizontal)
        .VALUE(ImPlot, BarGroupsFlags, Stacked);

    ENUM(ImPlot, ErrorBarsFlags)
        .VALUE(ImPlot, ErrorBarsFlags, None)
        .VALUE(ImPlot, ErrorBarsFlags, Horizontal);

    ENUM(ImPlot, StemsFlags)
        .VALUE(ImPlot, StemsFlags, None)
        .VALUE(ImPlot, StemsFlags, Horizontal);

    ENUM(ImPlot, InfLinesFlags)
        .VALUE(ImPlot, InfLinesFlags, None)
        .VALUE(ImPlot, InfLinesFlags, Horizontal);

    ENUM(ImPlot, PieChartFlags)
        .VALUE(ImPlot, PieChartFlags, None)
        .VALUE(ImPlot, PieChartFlags, Normalize);

    ENUM(ImPlot, HeatmapFlags)
        .VALUE(ImPlot, HeatmapFlags, None)
        .VALUE(ImPlot, HeatmapFlags, ColMajor);

    ENUM(ImPlot, HistogramFlags)
        .VALUE(ImPlot, HistogramFlags, None)
        .VALUE(ImPlot, HistogramFlags, Horizontal)
        .VALUE(ImPlot, HistogramFlags, Cumulative)
        .VALUE(ImPlot, HistogramFlags, Density)
        .VALUE(ImPlot, HistogramFlags, NoOutliers)
        .VALUE(ImPlot, HistogramFlags, ColMajor);

    ENUM(ImPlot, DigitalFlags).VALUE(ImPlot, DigitalFlags, None);

    ENUM(ImPlot, ImageFlags).VALUE(ImPlot, ImageFlags, None);

    ENUM(ImPlot, TextFlags)
        .VALUE(ImPlot, TextFlags, None)
        .VALUE(ImPlot, TextFlags, Vertical);

    ENUM(ImPlot, DummyFlags).VALUE(ImPlot, DummyFlags, None);

    ENUM(ImPlot, Cond)
        .VALUE(ImPlot, Cond, None)
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
        .VALUE(ImPlot, Marker, None)
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