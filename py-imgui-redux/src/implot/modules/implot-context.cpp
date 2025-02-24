#ifndef IMGUI_DEFINE_MATH_OPERATORS
    #define IMGUI_DEFINE_MATH_OPERATORS
#endif

#include <bind-imgui/implot-modules.h>
#include <binder/wraps.h>

// Import internal so that we get the context class def
#include <implot_internal.h>

void init_implot_context(py::module& m)
{
    // Def opaque class
    py::class_<ImPlotContext>(m, "Context");

    m.def(IMFUNC(CreateContext), py::return_value_policy::reference);
    m.def(IMFUNC(DestroyContext), "ctx"_a = nullptr);
    m.def(IMFUNC(GetCurrentContext), py::return_value_policy::reference);
    m.def(IMFUNC(SetCurrentContext), "ctx"_a);
    //m.def(IMFUNC(SetImGuiContext), "ctx"_a);

    m.def(
        "BeginPlot",
        py::overload_cast<const char*, const ImVec2&, ImPlotFlags>(
            ImPlot::BeginPlot
        ),
        "title_id"_a,
        py::arg_v("size", ImVec2(-1, 0), "Vec2(-1, 0)"),
        "flags"_a = 0
    );
    QUICK(EndPlot);

    m.def(
        "BeginSubplots",
        [](const char* title_id,
           int rows,
           int cols,
           const ImVec2& size,
           ImPlotSubplotFlags flags,
           FloatListPtr row_ratios,
           FloatListPtr col_ratios)
        {
            if(row_ratios && row_ratios->size() < rows)
            {
                throw py::value_error(
                    "Invalid row ratios, len(row_rations) < rows"
                );
            }
            if(col_ratios && col_ratios->size() < cols)
            {
                throw py::value_error(
                    "Invalid cols ratios, len(cols_rations) < cols"
                );
            }

            return ImPlot::BeginSubplots(
                title_id,
                rows,
                cols,
                size,
                flags,
                row_ratios ? row_ratios->data() : nullptr,
                col_ratios ? col_ratios->data() : nullptr
            );
        },
        "title_id"_a,
        "rows"_a,
        "cols"_a,
        "size"_a,
        "flags"_a = 0,
        "row_ratios"_a = nullptr,
        "col_ratios"_a = nullptr
    );

    QUICK(EndSubplots);
}