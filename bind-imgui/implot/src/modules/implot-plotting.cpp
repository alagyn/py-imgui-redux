#include <implot/inc/implot-modules.h>
#include <pybind11/numpy.h>

template<typename T> using arr = py::array_t<T, py::array::c_style>;

void init_plotting(py::module& m)
{
    m.def(
        "PlotLine",
        [](const char* label_id,
           arr<double> values,
           double xscale,
           double xstart,
           ImPlotLineFlags flags,
           int offset)
        {
            ImPlot::PlotLine(
                label_id,
                values.data(),
                values.size(),
                xscale,
                xstart,
                flags,
                offset
            );
        },
        "label_id"_a,
        "values"_a,
        "xscale"_a = 1,
        "xstart"_a = 0,
        "flags"_a = 0,
        "offset"_a = 0
    );

    m.def(
        "PlotLine",
        [](const char* label_id, arr<double> xs, arr<double> ys, int flags, int offset
        )
        {
            if(xs.size() != ys.size())
            {
                throw py::value_error("len(x) != len(y)");
            }
            ImPlot::PlotLine(
                label_id,
                xs.data(),
                ys.data(),
                xs.size(),
                flags,
                offset
            );
        },
        "label_id"_a,
        "xs"_a,
        "ys"_a,
        "flags"_a = 0,
        "offset"_a = 0
    );

    m.def(
        "PlotScatter",
        [](const char* label_id,
           arr<double> values,
           double xscale,
           double xstart,
           int flags,
           int offset)
        {
            ImPlot::PlotScatter(
                label_id,
                values.data(),
                values.size(),
                xscale,
                xstart,
                flags,
                offset
            );
        },
        "label_id"_a,
        "values"_a,
        "xscale"_a = 1,
        "xstart"_a = 0,
        "flags"_a = 0,
        "offset"_a = 0
    );

    m.def(
        "PlotScatter",
        [](const char* label_id, arr<double> xs, arr<double> ys, int flags, int offset
        )
        {
            if(xs.size() != ys.size())
            {
                throw py::value_error("len(x) != len(y)");
            }
            ImPlot::PlotScatter(
                label_id,
                xs.data(),
                ys.data(),
                xs.size(),
                flags,
                offset
            );
        },
        "label_id"_a,
        "xs"_a,
        "ys"_a,
        "flags"_a = 0,
        "offset"_a = 0
    );

    m.def(
        "PlotStairs",
        [](const char* label_id,
           arr<double> values,
           double xscale,
           double xstart,
           int flags,
           int offset)
        {
            ImPlot::PlotStairs(
                label_id,
                values.data(),
                values.size(),
                xscale,
                xstart,
                flags,
                offset
            );
        },
        "label_id"_a,
        "values"_a,
        "xscale"_a = 1,
        "xstart"_a = 0,
        "flags"_a = 0,
        "offset"_a = 0
    );
    m.def(
        "PlotStairs",
        [](const char* label_id, arr<double> xs, arr<double> ys, int flags, int offset
        )
        {
            if(xs.size() != ys.size())
            {
                throw py::value_error("len(x) != len(y)");
            }
            ImPlot::PlotStairs(
                label_id,
                xs.data(),
                ys.data(),
                xs.size(),
                flags,
                offset
            );
        },
        "label_id"_a,
        "xs"_a,
        "ys"_a,
        "flags"_a = 0,
        "offset"_a = 0
    );

    m.def(
        "PlotShaded",
        [](const char* label_id,
           arr<double> values,
           double yref,
           double xscale,
           double xstart,
           int flags,
           int offset)
        {
            ImPlot::PlotShaded(
                label_id,
                values.data(),
                values.size(),
                yref,
                xscale,
                xstart,
                flags,
                offset
            );
        },
        "label_id"_a,
        "values"_a,
        "yref"_a = 0,
        "xscale"_a = 1,
        "xstart"_a = 0,
        "flags"_a = 0,
        "offset"_a = 0
    );

    m.def(
        "PlotShaded",
        [](const char* label_id,
           arr<double> xs,
           arr<double> ys,
           double yref,
           int flags,
           int offset)
        {
            if(xs.size() != ys.size())
            {
                throw py::value_error("len(x) != len(y)");
            }
            ImPlot::PlotShaded(
                label_id,
                xs.data(),
                ys.data(),
                xs.size(),
                yref,
                flags,
                offset
            );
        },
        "label_id"_a,
        "xs"_a,
        "ys"_a,
        "yref"_a = 0,
        "flags"_a = 0,
        "offset"_a = 0
    );

    m.def(
        "PlotShaded",
        [](const char* label_id,
           arr<double> xs,
           arr<double> ys1,
           arr<double> ys2,
           int flags,
           int offset)
        {
            if(xs.size() != ys1.size() || xs.size() != ys2.size())
            {
                throw py::value_error("len(x) != len(y1) != len(y2)");
            }
            ImPlot::PlotShaded(
                label_id,
                xs.data(),
                ys1.data(),
                ys2.data(),
                xs.size(),
                flags,
                offset
            );
        },
        "label_id"_a,
        "xs"_a,
        "ys1"_a,
        "ys2"_a,
        "flags"_a = 0,
        "offset"_a = 0
    );

    m.def(
        "PlotBars",
        [](const char* label_id,
           arr<double> values,
           double bar_size,
           double shift,
           int flags,
           int offset)
        {
            ImPlot::PlotBars(
                label_id,
                values.data(),
                values.size(),
                bar_size,
                shift,
                flags,
                offset
            );
        },
        "label_id"_a,
        "values"_a,
        "bar_size"_a = 0.67,
        "shift"_a = 0.0,
        "flags"_a = 0,
        "offset"_a = 0
    );

    m.def(
        "PlotBars",
        [](const char* label_id,
           arr<double> xs,
           arr<double> ys,
           double bar_size,
           int flags,
           int offset)
        {
            if(xs.size() != ys.size())
            {
                throw py::value_error("len(x) != len(y1)");
            }
            ImPlot::PlotBars(
                label_id,
                xs.data(),
                ys.data(),
                xs.size(),
                bar_size,
                flags,
                offset
            );
        },
        "label_id"_a,
        "xs"_a,
        "ys"_a,
        "bar_size"_a = 0.67,
        "flags"_a = 0,
        "offset"_a = 0
    );

    m.def(
        "PlotBarGroups",
        [](arr<const char*> labels,
           arr<double> values,
           int item_count,
           int group_count,
           double group_size,
           double shift,
           int flags)
        {
            if(labels.size() != item_count)
            {
                throw py::value_error("len(labels) != item_count");
            }
            if(values.size() != item_count * group_size)
            {
                throw py::value_error("len(values) != item_count * group_count");
            }

            ImPlot::PlotBarGroups(
                labels.data(),
                values.data(),
                item_count,
                group_count,
                group_size,
                shift,
                flags
            );
        },
        "labels"_a,
        "values"_a,
        "item_count"_a,
        "group_count"_a,
        "group_size"_a = 0.67,
        "shift"_a = 0.0,
        "flags"_a = 0
    );

    m.def(
        "PlotErrorBars",
        [](const char* label_id,
           arr<double> xs,
           arr<double> ys,
           arr<double> err,
           int flags,
           int offset)
        {
            if(xs.size() != ys.size() || xs.size() != err.size())
            {
                throw py::value_error("len(xs) != len(ys) != len(err)");
            }

            ImPlot::PlotErrorBars(
                label_id,
                xs.data(),
                ys.data(),
                err.data(),
                xs.size(),
                flags,
                offset
            );
        },
        "label_id"_a,
        "xs"_a,
        "ys"_a,
        "err"_a,
        "flags"_a = 0,
        "offset"_a = 0
    );

    m.def(
        "PlotErrorBars",
        [](const char* label_id,
           arr<double> xs,
           arr<double> ys,
           arr<double> neg,
           arr<double> pos,
           int flags,
           int offset)
        {
            if(xs.size() != ys.size() || xs.size() != neg.size()
               || xs.size() != pos.size())
            {
                throw py::value_error(
                    "len(xs) != len(ys) != len(neg) != len(pos)"
                );
            }

            ImPlot::PlotErrorBars(
                label_id,
                xs.data(),
                ys.data(),
                neg.data(),
                pos.data(),
                xs.size(),
                flags,
                offset
            );
        },
        "label_id"_a,
        "xs"_a,
        "ys"_a,
        "neg"_a,
        "pos"_a,
        "flags"_a = 0,
        "offset"_a = 0
    );

    m.def(
        "PlotStems",
        [](const char* label_id,
           arr<double> values,
           int ref,
           double scale,
           double start,
           int flags,
           int offset)
        {
            ImPlot::PlotStems(
                label_id,
                values.data(),
                values.size(),
                ref,
                scale,
                start,
                flags,
                offset
            );
        },
        "label_id"_a,
        "values"_a,
        "ref"_a = 0,
        "scale"_a = 1,
        "start"_a = 0,
        "flags"_a = 0,
        "offset"_a = 0
    );
    m.def(
        "PlotStems",
        [](const char* label_id,
           arr<double> xs,
           arr<double> ys,
           int ref,
           int flags,
           int offset)
        {
            if(xs.size() != ys.size())
            {
                throw py::value_error("len(x) != len(y1)");
            }
            ImPlot::PlotStems(
                label_id,
                xs.data(),
                ys.data(),
                xs.size(),
                ref,
                flags,
                offset
            );
        },
        "label_id"_a,
        "xs"_a,
        "ys"_a,
        "ref"_a = 0,
        "flags"_a = 0,
        "offset"_a = 0
    );

    m.def(
        "PlotInfLines",
        [](const char* label_id, arr<double> values, int flags, int offset)
        {
            ImPlot::PlotInfLines(
                label_id,
                values.data(),
                values.size(),
                flags,
                offset
            );
        },
        "label_id"_a,
        "values"_a,
        "flags"_a = 0,
        "offset"_a = 0
    );

    m.def(
        "PlotPieChart",
        [](arr<const char*> label_ids,
           arr<double> values,
           double x,
           double y,
           double radius,
           const char* label_fmt,
           double angle0,
           int flags)
        {
            if(label_ids.size() != values.size())
            {
                throw py::value_error("len(label_ids) != len(values)");
            }
            ImPlot::PlotPieChart(
                label_ids.data(),
                values.data(),
                label_ids.size(),
                x,
                y,
                radius,
                label_fmt,
                angle0,
                flags
            );
        },
        "label_ids"_a,
        "values"_a,
        "x"_a,
        "y"_a,
        "radius"_a,
        "label_fmt"_a = "%.1f",
        "angle0"_a = 90,
        "flags"_a = 0
    );

    m.def(
        "PlotHeatmap",
        [](const char* label_id,
           arr<double> values,
           int rows,
           int cols,
           double scale_min,
           double scale_max,
           const char* label_fmt,
           const ImPlotPoint& bounds_min,
           const ImPlotPoint& bounds_max,
           int flags)
        {
            if(values.size() < rows * cols)
            {
                throw py::value_error("len(values) > rows * cols");
            }

            ImPlot::PlotHeatmap(
                label_id,
                values.data(),
                rows,
                cols,
                scale_min,
                scale_max,
                label_fmt,
                bounds_min,
                bounds_max,
                flags
            );
        },
        "label_id"_a,
        "values"_a,
        "rows"_a,
        "cols"_a,
        "scale_min"_a = 0,
        "scale_max"_a = 0,
        "label_fmt"_a = "%.1f",
        "bounds_min"_a = ImPlotPoint(0, 0),
        "bounds_max"_a = ImPlotPoint(1, 1),
        "flags"_a = 0
    );

    m.def(
        "PlotHistogram",
        [](const char* label_id,
           arr<double> values,
           int bins,
           double bar_scale,
           ImPlotRange range,
           int flags)
        {
            ImPlot::PlotHistogram(
                label_id,
                values.data(),
                values.size(),
                bins,
                bar_scale,
                range,
                flags
            );
        },
        "label_id"_a,
        "values"_a,
        "bins"_a = ImPlotBin_Sturges,
        "bar_scale"_a = 1.0,
        "range"_a = ImPlotRange(),
        "flags"_a = 0
    );

    m.def(
        "PlotHistogram2D",
        [](const char* label_id,
           arr<double> xs,
           arr<double> ys,
           int x_bins,
           int y_bins,
           ImPlotRect range,
           int flags)
        {
            if(xs.size() != ys.size())
            {
                throw py::value_error("len(xs) != len(ys)");
            }
            ImPlot::PlotHistogram2D(
                label_id,
                xs.data(),
                ys.data(),
                xs.size(),
                x_bins,
                y_bins,
                range,
                flags
            );
        },
        "label_id"_a,
        "xs"_a,
        "ys"_a,
        "x_bins"_a = ImPlotBin_Sturges,
        "y_bins"_a = ImPlotBin_Sturges,
        "range"_a = ImPlotRect(),
        "flags"_a = 0
    );

    m.def(
        "PlotDigital",
        [](const char* label_id, arr<double> xs, arr<double> ys, int flags, int offset
        )
        {
            if(xs.size() != ys.size())
            {
                throw py::value_error("len(xs) != len(ys)");
            }

            ImPlot::PlotDigital(
                label_id,
                xs.data(),
                ys.data(),
                xs.size(),
                flags,
                offset
            );
        },
        "label_id"_a,
        "xs"_a,
        "ys"_a,
        "flags"_a = 0,
        "offset"_a = 0
    );

    // TODO PlotImage

    m.def(
        IMFUNC(PlotText),
        "text"_a,
        "x"_a,
        "y"_a,
        "pix_offset"_a = ImVec2(0, 0),
        "flags"_a = 0
    );

    m.def(IMFUNC(PlotDummy), "label_id"_a, "flags"_a = 0);
}