#include <bind-imgui/implot-modules.h>

#include <bind-imgui/implot-formatter-callback.h>
#include <bind-imgui/implot-spec.h>
#include <bind-imgui/texture.h>
#include <binder/numpy.h>
#include <binder/wraps.h>

#include <pybind11/functional.h>

using GetterCallback = std::function<ImPlotPoint(int, py::object)>;

#define PLOT_FUNC_CALL(func, ...) \
    if(py::isinstance<py::tuple>(spec)) \
    { \
        func(__VA_ARGS__, makeSpec(spec)); \
    } \
    else \
    { \
        func(__VA_ARGS__, spec.cast<const ImPlotSpec&>()); \
    }

struct GetterCallbackData
{
    GetterCallback callback;
    py::object userdata;
};

ImPlotPoint getterCallbackFunc(int index, void* userdata)
{
    auto* data = static_cast<GetterCallbackData*>(userdata);
    return data->callback(index, data->userdata);
}

template<typename T> void initWrapperPlotting(py::module& m)
{
    m.def(
        "PlotLine",
        [](const char* label_id,
           T values,
           double xscale,
           double xstart,
           py::typing::Union<const ImPlotSpec&, py::tuple> spec)
        {
            PLOT_FUNC_CALL(
                ImPlot::PlotLine,
                label_id,
                values->data(),
                values->size(),
                xscale,
                xstart
            );
        },
        "label_id"_a,
        "values"_a,
        "xscale"_a = 1,
        "xstart"_a = 0,
        py::arg_v("spec", ImPlotSpec(), "PlotSpec()")
    );

    m.def(
        "PlotLine",
        [](const char* label_id,
           T xs,
           T ys,
           py::typing::Union<const ImPlotSpec&, py::tuple> spec)
        {
            if(xs->size() != ys->size())
            {
                throw py::value_error("len(x) != len(y)");
            }

            PLOT_FUNC_CALL(
                ImPlot::PlotLine,
                label_id,
                xs->data(),
                ys->data(),
                xs->size()
            );
        },
        "label_id"_a,
        "xs"_a,
        "ys"_a,
        py::arg_v("spec", ImPlotSpec(), "PlotSpec()")
    );

    m.def(
        "PlotLineG",
        [](const char* label_id,
           GetterCallback getter,
           py::object data,
           int count,
           py::typing::Union<const ImPlotSpec&, py::tuple> spec)
        {
            GetterCallbackData userdata{getter, data};

            PLOT_FUNC_CALL(
                ImPlot::PlotLineG,
                label_id,
                getterCallbackFunc,
                &userdata,
                count
            );
        },
        "label_id"_a,
        "getter"_a.none(false),
        "data"_a,
        "count"_a,
        py::arg_v("spec", ImPlotSpec(), "PlotSpec()")
    );

    m.def(
        "PlotScatter",
        [](const char* label_id,
           T values,
           double xscale,
           double xstart,
           py::typing::Union<const ImPlotSpec&, py::tuple> spec)
        {
            PLOT_FUNC_CALL(
                ImPlot::PlotScatter,
                label_id,
                values->data(),
                values->size(),
                xscale,
                xstart
            );
        },
        "label_id"_a,
        "values"_a,
        "xscale"_a = 1,
        "xstart"_a = 0,
        py::arg_v("spec", ImPlotSpec(), "PlotSpec()")
    );

    m.def(
        "PlotScatter",
        [](const char* label_id,
           T xs,
           T ys,
           py::typing::Union<const ImPlotSpec&, py::tuple> spec)
        {
            if(xs->size() != ys->size())
            {
                throw py::value_error("len(x) != len(y)");
            }

            PLOT_FUNC_CALL(
                ImPlot::PlotScatter,
                label_id,
                xs->data(),
                ys->data(),
                xs->size()
            )
        },
        "label_id"_a,
        "xs"_a,
        "ys"_a,
        py::arg_v("spec", ImPlotSpec(), "PlotSpec()")
    );

    m.def(
        "PlotScatterG",
        [](const char* label_id,
           GetterCallback getter,
           py::object data,
           int count,
           py::typing::Union<const ImPlotSpec&, py::tuple> spec)
        {
            GetterCallbackData userdata{getter, data};

            PLOT_FUNC_CALL(
                ImPlot::PlotScatterG,
                label_id,
                getterCallbackFunc,
                &userdata,
                count
            );
        },
        "label_id"_a,
        "getter"_a.none(false),
        "data"_a,
        "count"_a,
        py::arg_v("spec", ImPlotSpec(), "PlotSpec()")
    );

    m.def(
        "PlotBubbles",
        [](const char* label_id,
           T values,
           T sizes,
           double xscale,
           double xstart,
           py::typing::Union<const ImPlotSpec&, py::tuple> spec)
        {
            if(values->size() != sizes->size())
            {
                throw py::value_error("len(values) != len(sizes)");
            }

            PLOT_FUNC_CALL(
                ImPlot::PlotBubbles,
                label_id,
                values->data(),
                sizes->data(),
                values->size(),
                xscale,
                xstart
            );
        },
        "label_id"_a,
        "values"_a,
        "szs"_a,
        "xscale"_a = 1,
        "xstart"_a = 0,
        py::arg_v("spec", ImPlotSpec(), "PlotSpec()")
    );

    m.def(
        "PlotBubbles",
        [](const char* label_id,
           T xs,
           T ys,
           T sizes,
           py::typing::Union<const ImPlotSpec&, py::tuple> spec)
        {
            if(xs->size() != ys->size())
            {
                throw py::value_error("len(x) != len(y)");
            }

            PLOT_FUNC_CALL(
                ImPlot::PlotBubbles,
                label_id,
                xs->data(),
                ys->data(),
                sizes->data(),
                xs->size()
            );
        },
        "label_id"_a,
        "xs"_a,
        "ys"_a,
        "szs"_a,
        py::arg_v("spec", ImPlotSpec(), "PlotSpec()")
    );

    m.def(
        "PlotPolygon",
        [](const char* label_id,
           T xs,
           T ys,
           py::typing::Union<const ImPlotSpec&, py::tuple> spec)
        {
            if(xs->size() != ys->size())
            {
                throw py::value_error("len(x) != len(y)");
            }

            PLOT_FUNC_CALL(
                ImPlot::PlotPolygon,
                label_id,
                xs->data(),
                ys->data(),
                xs->size()
            );
        },
        "label_id"_a,
        "xs"_a,
        "ys"_a,
        py::arg_v("spec", ImPlotSpec(), "PlotSpec()")
    );

    m.def(
        "PlotStairs",
        [](const char* label_id,
           T values,
           double xscale,
           double xstart,
           py::typing::Union<const ImPlotSpec&, py::tuple> spec)
        {
            PLOT_FUNC_CALL(
                ImPlot::PlotStairs,
                label_id,
                values->data(),
                values->size(),
                xscale,
                xstart
            );
        },
        "label_id"_a,
        "values"_a,
        "xscale"_a = 1,
        "xstart"_a = 0,
        py::arg_v("spec", ImPlotSpec(), "PlotSpec()")
    );

    m.def(
        "PlotStairs",
        [](const char* label_id,
           T xs,
           T ys,
           py::typing::Union<const ImPlotSpec&, py::tuple> spec)
        {
            if(xs->size() != ys->size())
            {
                throw py::value_error("len(x) != len(y)");
            }

            PLOT_FUNC_CALL(
                ImPlot::PlotStairs,
                label_id,
                xs->data(),
                ys->data(),
                xs->size()
            );
        },
        "label_id"_a,
        "xs"_a,
        "ys"_a,
        py::arg_v("spec", ImPlotSpec(), "PlotSpec()")
    );

    m.def(
        "PlotStairsG",
        [](const char* label_id,
           GetterCallback getter,
           py::object data,
           int count,
           py::typing::Union<const ImPlotSpec&, py::tuple> spec)
        {
            GetterCallbackData userdata{getter, data};

            PLOT_FUNC_CALL(
                ImPlot::PlotStairsG,
                label_id,
                getterCallbackFunc,
                &userdata,
                count
            );
        },
        "label_id"_a,
        "getter"_a.none(false),
        "data"_a,
        "count"_a,
        py::arg_v("spec", ImPlotSpec(), "PlotSpec()")
    );

    m.def(
        "PlotShaded",
        [](const char* label_id,
           T values,
           double yref,
           double xscale,
           double xstart,
           py::typing::Union<const ImPlotSpec&, py::tuple> spec)
        {
            PLOT_FUNC_CALL(
                ImPlot::PlotShaded,
                label_id,
                values->data(),
                values->size(),
                yref,
                xscale,
                xstart
            );
        },
        "label_id"_a,
        "values"_a,
        "yref"_a = 0,
        "xscale"_a = 1,
        "xstart"_a = 0,
        py::arg_v("spec", ImPlotSpec(), "PlotSpec()")
    );

    m.def(
        "PlotShaded",
        [](const char* label_id,
           T xs,
           T ys,
           double yref,
           py::typing::Union<const ImPlotSpec&, py::tuple> spec)
        {
            if(xs->size() != ys->size())
            {
                throw py::value_error("len(x) != len(y)");
            }

            PLOT_FUNC_CALL(
                ImPlot::PlotShaded,
                label_id,
                xs->data(),
                ys->data(),
                xs->size(),
                yref
            );
        },
        "label_id"_a,
        "xs"_a,
        "ys"_a,
        "yref"_a = 0,
        py::arg_v("spec", ImPlotSpec(), "PlotSpec()")
    );

    m.def(
        "PlotShaded",
        [](const char* label_id,
           T xs,
           T ys1,
           T ys2,
           py::typing::Union<const ImPlotSpec&, py::tuple> spec)
        {
            if(xs->size() != ys1->size() || xs->size() != ys2->size())
            {
                throw py::value_error("len(x) != len(y1) != len(y2)");
            }

            PLOT_FUNC_CALL(
                ImPlot::PlotShaded,
                label_id,
                xs->data(),
                ys1->data(),
                ys2->data(),
                xs->size()
            );
        },
        "label_id"_a,
        "xs"_a,
        "ys1"_a,
        "ys2"_a,
        py::arg_v("spec", ImPlotSpec(), "PlotSpec()")
    );

    m.def(
        "PlotShadedG",
        [](const char* label_id,
           GetterCallback getter1,
           py::object data1,
           GetterCallback getter2,
           py::object data2,
           int count,
           py::typing::Union<const ImPlotSpec&, py::tuple> spec)
        {
            GetterCallbackData cbdata1{getter1, data1};
            GetterCallbackData cbdata2{getter2, data2};

            PLOT_FUNC_CALL(
                ImPlot::PlotShadedG,
                label_id,
                getterCallbackFunc,
                &cbdata1,
                getterCallbackFunc,
                &cbdata2,
                count
            );
        },
        "label_id"_a,
        "getter1"_a.none(false),
        "data1"_a,
        "getter2"_a.none(false),
        "data2"_a,
        "count"_a,
        py::arg_v("spec", ImPlotSpec(), "PlotSpec()")
    );

    m.def(
        "PlotBars",
        [](const char* label_id,
           T values,
           double bar_size,
           double shift,
           py::typing::Union<const ImPlotSpec&, py::tuple> spec)
        {
            PLOT_FUNC_CALL(
                ImPlot::PlotBars,
                label_id,
                values->data(),
                values->size(),
                bar_size,
                shift
            );
        },
        "label_id"_a,
        "values"_a,
        "bar_size"_a = 0.67,
        "shift"_a = 0.0,
        py::arg_v("spec", ImPlotSpec(), "PlotSpec()")
    );

    m.def(
        "PlotBars",
        [](const char* label_id,
           T xs,
           T ys,
           double bar_size,
           py::typing::Union<const ImPlotSpec&, py::tuple> spec)
        {
            if(xs->size() != ys->size())
            {
                throw py::value_error("len(x) != len(y1)");
            }
            PLOT_FUNC_CALL(
                ImPlot::PlotBars,
                label_id,
                xs->data(),
                ys->data(),
                xs->size(),
                bar_size
            );
        },
        "label_id"_a,
        "xs"_a,
        "ys"_a,
        "bar_size"_a = 0.67,
        py::arg_v("spec", ImPlotSpec(), "PlotSpec()")
    );

    m.def(
        "PlotBarsG",
        [](const char* label_id,
           GetterCallback getter,
           py::object data,
           int count,
           double bar_size,
           py::typing::Union<const ImPlotSpec&, py::tuple> spec)
        {
            GetterCallbackData userdata{getter, data};
            PLOT_FUNC_CALL(
                ImPlot::PlotBarsG,
                label_id,
                getterCallbackFunc,
                &userdata,
                count,
                bar_size
            );
        },
        "label_id"_a,
        "getter"_a.none(false),
        "data"_a,
        "count"_a,
        "bar_size"_a,
        py::arg_v("spec", ImPlotSpec(), "PlotSpec()")
    );

    m.def(
        "PlotBarGroups",
        [](StrListPtr labels,
           T values,
           int item_count,
           int group_count,
           double group_size,
           double shift,
           py::typing::Union<const ImPlotSpec&, py::tuple> spec)
        {
            if(labels->size() != item_count)
            {
                throw py::value_error("len(labels) != item_count");
            }
            if(values->size() != item_count * group_size)
            {
                throw py::value_error("len(values) != item_count * group_count");
            }

            PLOT_FUNC_CALL(
                ImPlot::PlotBarGroups,
                labels->data(),
                values->data(),
                item_count,
                group_count,
                group_size,
                shift
            );
        },
        "labels"_a,
        "values"_a,
        "item_count"_a,
        "group_count"_a,
        "group_size"_a = 0.67,
        "shift"_a = 0.0,
        py::arg_v("spec", ImPlotSpec(), "PlotSpec()")
    );

    m.def(
        "PlotErrorBars",
        [](const char* label_id,
           T xs,
           T ys,
           T err,
           py::typing::Union<const ImPlotSpec&, py::tuple> spec)
        {
            if(xs->size() != ys->size() || xs->size() != err->size())
            {
                throw py::value_error("len(xs) != len(ys) != len(err)");
            }
            PLOT_FUNC_CALL(
                ImPlot::PlotErrorBars,
                label_id,
                xs->data(),
                ys->data(),
                err->data(),
                xs->size()
            );
        },
        "label_id"_a,
        "xs"_a,
        "ys"_a,
        "err"_a,
        py::arg_v("spec", ImPlotSpec(), "PlotSpec()")
    );

    m.def(
        "PlotErrorBars",
        [](const char* label_id,
           T xs,
           T ys,
           T neg,
           T pos,
           py::typing::Union<const ImPlotSpec&, py::tuple> spec)
        {
            if(xs->size() != ys->size() || xs->size() != neg->size()
               || xs->size() != pos->size())
            {
                throw py::value_error(
                    "len(xs) != len(ys) != len(neg) != len(pos)"
                );
            }

            PLOT_FUNC_CALL(
                ImPlot::PlotErrorBars,
                label_id,
                xs->data(),
                ys->data(),
                neg->data(),
                pos->data(),
                xs->size()
            );
        },
        "label_id"_a,
        "xs"_a,
        "ys"_a,
        "neg"_a,
        "pos"_a,
        py::arg_v("spec", ImPlotSpec(), "PlotSpec()")
    );

    m.def(
        "PlotStems",
        [](const char* label_id,
           T values,
           int ref,
           double scale,
           double start,
           py::typing::Union<const ImPlotSpec&, py::tuple> spec)
        {
            PLOT_FUNC_CALL(
                ImPlot::PlotStems,
                label_id,
                values->data(),
                values->size(),
                ref,
                scale,
                start
            );
        },
        "label_id"_a,
        "values"_a,
        "ref"_a = 0,
        "scale"_a = 1,
        "start"_a = 0,
        py::arg_v("spec", ImPlotSpec(), "PlotSpec()")
    );

    m.def(
        "PlotStems",
        [](const char* label_id,
           T xs,
           T ys,
           int ref,
           py::typing::Union<const ImPlotSpec&, py::tuple> spec)
        {
            if(xs->size() != ys->size())
            {
                throw py::value_error("len(x) != len(y1)");
            }
            PLOT_FUNC_CALL(
                ImPlot::PlotStems,
                label_id,
                xs->data(),
                ys->data(),
                xs->size(),
                ref
            );
        },
        "label_id"_a,
        "xs"_a,
        "ys"_a,
        "ref"_a = 0,
        py::arg_v("spec", ImPlotSpec(), "PlotSpec()")
    );

    m.def(
        "PlotInfLines",
        [](const char* label_id,
           T values,
           py::typing::Union<const ImPlotSpec&, py::tuple> spec)
        {
            PLOT_FUNC_CALL(
                ImPlot::PlotInfLines,
                label_id,
                values->data(),
                values->size()
            );
        },
        "label_id"_a,
        "values"_a,
        py::arg_v("spec", ImPlotSpec(), "PlotSpec()")
    );

    m.def(
        "PlotPieChart",
        [](StrListPtr label_ids,
           T values,
           double x,
           double y,
           double radius,
           FormatterCallback fmt,
           py::object fmt_data,
           double angle0,
           py::typing::Union<const ImPlotSpec&, py::tuple> spec)
        {
            if(label_ids->size() != values->size())
            {
                throw py::value_error("len(label_ids) != len(values)");
            }
            FormatterCallbackData data(fmt, fmt_data);
            PLOT_FUNC_CALL(
                ImPlot::PlotPieChart,
                label_ids->data(),
                values->data(),
                label_ids->size(),
                x,
                y,
                radius,
                plotFormatterCallback,
                &data,
                angle0
            );
        },
        "label_ids"_a,
        "values"_a,
        "x"_a,
        "y"_a,
        "radius"_a,
        "fmt"_a.none(false),
        "fmt_data"_a = py::none(),
        "angle0"_a = 90,
        py::arg_v("spec", ImPlotSpec(), "PlotSpec()")
    );

    m.def(
        "PlotPieChart",
        [](StrListPtr label_ids,
           T values,
           double x,
           double y,
           double radius,
           const char* label_fmt,
           double angle0,
           py::typing::Union<const ImPlotSpec&, py::tuple> spec)
        {
            if(label_ids->size() != values->size())
            {
                throw py::value_error("len(label_ids) != len(values)");
            }
            PLOT_FUNC_CALL(
                ImPlot::PlotPieChart,
                label_ids->data(),
                values->data(),
                label_ids->size(),
                x,
                y,
                radius,
                label_fmt,
                angle0
            );
        },
        "label_ids"_a,
        "values"_a,
        "x"_a,
        "y"_a,
        "radius"_a,
        "label_fmt"_a = "%.1f",
        "angle0"_a = 90,
        py::arg_v("spec", ImPlotSpec(), "PlotSpec()")
    );

    m.def(
        "PlotHeatmap",
        [](const char* label_id,
           T values,
           int rows,
           int cols,
           double scale_min,
           double scale_max,
           const char* label_fmt,
           const ImPlotPoint& bounds_min,
           const ImPlotPoint& bounds_max,
           py::typing::Union<const ImPlotSpec&, py::tuple> spec)
        {
            if(values->size() < rows * cols)
            {
                throw py::value_error("len(values) > rows * cols");
            }
            PLOT_FUNC_CALL(
                ImPlot::PlotHeatmap,
                label_id,
                values->data(),
                rows,
                cols,
                scale_min,
                scale_max,
                label_fmt,
                bounds_min,
                bounds_max
            );
        },
        "label_id"_a,
        "values"_a,
        "rows"_a,
        "cols"_a,
        "scale_min"_a = 0,
        "scale_max"_a = 0,
        "label_fmt"_a = "%.1f",
        py::arg_v("bounds_min", ImPlotPoint(0, 0), "Point(0, 0)"),
        py::arg_v("bounds_max", ImPlotPoint(1, 1), "Point(1, 1)"),
        py::arg_v("spec", ImPlotSpec(), "PlotSpec()")
    );

    m.def(
        "PlotHistogram",
        [](const char* label_id,
           T values,
           int bins,
           double bar_scale,
           ImPlotRange range,
           py::typing::Union<const ImPlotSpec&, py::tuple> spec)
        {
            PLOT_FUNC_CALL(
                ImPlot::PlotHistogram,
                label_id,
                values->data(),
                values->size(),
                bins,
                bar_scale,
                range
            );
        },
        "label_id"_a,
        "values"_a,
        "bins"_a = (int)ImPlotBin_Sturges,
        "bar_scale"_a = 1.0,
        py::arg_v("range", ImPlotRange(), "Range(0, 0)"),
        py::arg_v("spec", ImPlotSpec(), "PlotSpec()")
    );

    m.def(
        "PlotHistogram2D",
        [](const char* label_id,
           T xs,
           T ys,
           int x_bins,
           int y_bins,
           ImPlotRect range,
           py::typing::Union<const ImPlotSpec&, py::tuple> spec)
        {
            if(xs->size() != ys->size())
            {
                throw py::value_error("len(xs) != len(ys)");
            }

            PLOT_FUNC_CALL(
                ImPlot::PlotHistogram2D,
                label_id,
                xs->data(),
                ys->data(),
                xs->size(),
                x_bins,
                y_bins,
                range
            );
        },
        "label_id"_a,
        "xs"_a,
        "ys"_a,
        "x_bins"_a = (int)ImPlotBin_Sturges,
        "y_bins"_a = (int)ImPlotBin_Sturges,
        py::arg_v("range", ImPlotRect(), "Rect(0, 0)"),
        py::arg_v("spec", ImPlotSpec(), "PlotSpec()")
    );

    m.def(
        "PlotDigital",
        [](const char* label_id,
           T xs,
           T ys,
           py::typing::Union<const ImPlotSpec&, py::tuple> spec)
        {
            if(xs->size() != ys->size())
            {
                throw py::value_error("len(xs) != len(ys)");
            }
            PLOT_FUNC_CALL(
                ImPlot::PlotDigital,
                label_id,
                xs->data(),
                ys->data(),
                xs->size()
            );
        },
        "label_id"_a,
        "xs"_a,
        "ys"_a,
        py::arg_v("spec", ImPlotSpec(), "PlotSpec()")
    );

    m.def(
        "PlotDigitalG",
        [](const char* label_id,
           GetterCallback getter,
           py::object data,
           int count,
           py::typing::Union<const ImPlotSpec&, py::tuple> spec)
        {
            GetterCallbackData userdata{getter, data};
            PLOT_FUNC_CALL(
                ImPlot::PlotDigitalG,
                label_id,
                getterCallbackFunc,
                &userdata,
                count
            );
        },
        "label_id"_a,
        "getter"_a.none(false),
        "data"_a,
        "count"_a,
        py::arg_v("spec", ImPlotSpec(), "PlotSpec()")
    );
}

void init_plotting(py::module& m)
{
    initWrapperPlotting<DoubleListPtr>(m);
    initWrapperPlotting<IntListPtr>(m);
    initWrapperPlotting<arr<double>*>(m);

    m.def(
        "PlotImage",
        [](const char* label_id,
           Texture tex,
           const ImPlotPoint& bounds_min,
           const ImPlotPoint& bounds_max,
           const ImVec2& uv0,
           const ImVec2& uv1,
           const ImVec4& tint_col,
           py::typing::Union<const ImPlotSpec&, py::tuple> spec)
        {
            PLOT_FUNC_CALL(
                ImPlot::PlotImage,
                label_id,
                ImTextureRef(tex.texID),
                bounds_min,
                bounds_max,
                uv0,
                uv1,
                tint_col
            );
        },
        "label_id"_a,
        "texture"_a,
        "bounds_min"_a,
        "bounds_max"_a,
        py::arg_v("uv0", ImVec2(0, 0), "Vec2(0, 0)"),
        py::arg_v("uv1", ImVec2(0, 0), "Vec2(0, 0)"),
        py::arg_v("tint_col", ImVec4(1, 1, 1, 1), "Vec4(1, 1, 1, 1)"),
        py::arg_v("spec", ImPlotSpec(), "PlotSpec()")
    );

    m.def(
        "PlotText",
        [](const char* text,
           double x,
           double y,
           const ImVec2& pix_offset,
           py::typing::Union<const ImPlotSpec&, py::tuple> spec)
        {
            PLOT_FUNC_CALL(ImPlot::PlotText, text, x, y, pix_offset);
        },
        "text"_a,
        "x"_a,
        "y"_a,
        py::arg_v("pix_offset", ImVec2(0, 0), "Vec2(0, 0)"),
        py::arg_v("spec", ImPlotSpec(), "PlotSpec()")
    );

    m.def(
        "PlotDummy",
        [](const char* label_id,
           py::typing::Union<const ImPlotSpec&, py::tuple> spec)
        {
            PLOT_FUNC_CALL(ImPlot::PlotDummy, label_id);
        },
        "label_id"_a,
        py::arg_v("spec", ImPlotSpec(), "PlotSpec()")
    );
}