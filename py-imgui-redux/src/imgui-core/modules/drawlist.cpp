#include <bind-imgui/imgui-modules.h>
#include <bind-imgui/texture.h>
#include <binder/struct-utility.h>

#include <binder/wraps.h>

void init_drawlist(py::module& m)
{
    py::class_<ImDrawList>(m, "ImDrawList")
        // TODO buffers
        .RW(ImDrawList, Flags)
        // Ignoring internals
        // Ignoring Constr
        .def(
            DEF(ImDrawList, PushClipRect),
            "clip_rect_min"_a,
            "clip_rect_max"_a,
            "intersect_with_current_clip_rect"_a = false
        )
        .def(DEF(ImDrawList, PushClipRectFullScreen))
        .def(DEF(ImDrawList, PopClipRect))
        .def(DEF(ImDrawList, PushTextureID))
        .def(DEF(ImDrawList, PopTextureID))
        // Primitives
        .def(DEF(ImDrawList, AddLine), "p1"_a, "p2"_a, "col"_a, "thickness"_a = 1.0f)
        .def(
            DEF(ImDrawList, AddRect),
            "p_min"_a,
            "p_max"_a,
            "col"_a,
            "rounding"_a = 0.0f,
            "flags"_a = 0,
            "thickness"_a = 1.0f
        )
        .def(
            DEF(ImDrawList, AddRectFilled),
            "p_min"_a,
            "p_max"_a,
            "col"_a,
            "rounding"_a,
            "flags"_a = 0
        )
        .def(
            DEF(ImDrawList, AddRectFilledMultiColor),
            "p_min"_a,
            "p_max"_a,
            "col_upr_left"_a,
            "col_upr_right"_a,
            "col_bot_right"_a,
            "col_bot_left"_a
        )
        .def(
            DEF(ImDrawList, AddQuad),
            "p1"_a,
            "p2"_a,
            "p3"_a,
            "p4"_a,
            "col"_a,
            "thickness"_a = 1.0f
        )
        .def(DEF(ImDrawList, AddQuadFilled), "p1"_a, "p2"_a, "p3"_a, "p4"_a, "col"_a)
        .def(
            DEF(ImDrawList, AddTriangle),
            "p1"_a,
            "p2"_a,
            "p3"_a,
            "col"_a,
            "thickness"_a = 1.0f
        )
        .def(DEF(ImDrawList, AddTriangleFilled), "p1"_a, "p2"_a, "p3"_a, "col"_a)
        .def(
            DEF(ImDrawList, AddCircle),
            "center"_a,
            "radius"_a,
            "col"_a,
            "num_segments"_a = 0,
            "thickness"_a = 1.0f
        )
        .def(
            DEF(ImDrawList, AddCircleFilled),
            "center"_a,
            "radius"_a,
            "col"_a,
            "num_segments"_a = 0
        )
        .def(
            DEF(ImDrawList, AddNgon),
            "center"_a,
            "radius"_a,
            "col"_a,
            "num_segments"_a,
            "thickness"_a = 1.0f
        )
        .def(
            DEF(ImDrawList, AddNgonFilled),
            "center"_a,
            "radius"_a,
            "col"_a,
            "num_segments"_a
        )
        .def(
            DEF(ImDrawList, AddEllipse),
            "center"_a,
            "radius"_a,
            "col"_a,
            "rot"_a = 0.0f,
            "num_segments"_a = 0,
            "thickness"_a = 1.0f
        )
        .def(
            DEF(ImDrawList, AddEllipseFilled),
            "center"_a,
            "radius"_a,
            "col"_a,
            "rot"_a = 0.0f,
            "num_segments"_a = 0
        )
        // Combining AddText()
        .def(
            "AddText",
            [](ImDrawList* self,
               const ImVec2& pos,
               ImU32 col,
               const char* text,
               ImFont* font,
               float font_size,
               float wrap_width,
               const ImVec4* cpu_fine_clip_rect)
            {
                if(font == nullptr)
                {
                    self->AddText(pos, col, text);
                }
                else
                {
                    self->AddText(
                        font,
                        font_size,
                        pos,
                        col,
                        text,
                        nullptr, // this is null since the str will be zero terminated
                        wrap_width,
                        cpu_fine_clip_rect
                    );
                }
            },
            "pos"_a,
            "col"_a,
            "text"_a,
            "font"_a = nullptr,
            "font_size"_a = 1.0f,
            "wrap_width"_a = 0.0f,
            "cpu_fine_clip_rect"_a = nullptr
        )
        .def(
            "AddPolyline",
            [](ImDrawList* self,
               Vec2ListPtr points,
               ImU32 col,
               ImDrawFlags flags,
               float thickness)
            {
                self->AddPolyline(
                    points->data(),
                    points->size(),
                    col,
                    flags,
                    thickness
                );
            },
            "points"_a,
            "col"_a,
            "flags"_a,
            "thickness"_a
        )
        .def(
            "AddConvexPolyFilled",
            [](ImDrawList* self, Vec2ListPtr points, ImU32 col)
            {
                self->AddConvexPolyFilled(points->data(), points->size(), col);
            },
            "points"_a,
            "col"_a
        )
        .def(
            "AddConcavePolyFilled",
            [](ImDrawList* self, Vec2ListPtr points, ImU32 col)
            {
                self->AddConcavePolyFilled(points->data(), points->size(), col);
            }
        )
        .def(
            DEF(ImDrawList, AddBezierCubic),
            "p1"_a,
            "p2"_a,
            "p3"_a,
            "p4"_a,
            "col"_a,
            "thickness"_a,
            "num_segments"_a = 0
        )
        .def(
            DEF(ImDrawList, AddBezierQuadratic),
            "p1"_a,
            "p2"_a,
            "p3"_a,
            "col"_a,
            "thickness"_a,
            "num_segments"_a = 0
        )
        // Image Primitives
        .def(
            "AddImage",
            [](ImDrawList* self,
               Texture tex,
               ImVec2 p_min,
               ImVec2 p_max,
               ImVec2 uv_min,
               ImVec2 uv_max,
               ImU32 col)
            {
                self->AddImage(tex.texID, p_min, p_max, uv_min, uv_max, col);
            },
            "user_texture_id"_a,
            "p_min"_a,
            "p_max"_a,
            py::arg_v("uv_min", ImVec2(0, 0), "Vec2(0, 0)"),
            py::arg_v("uv_max", ImVec2(1, 1), "Vec2(1, 1)"),
            "col"_a = IM_COL32_WHITE
        )
        .def(
            "AddImageQuad",
            [](ImDrawList* self,
               Texture tex,
               ImVec2 p1,
               ImVec2 p2,
               ImVec2 p3,
               ImVec2 p4,
               ImVec2 uv1,
               ImVec2 uv2,
               ImVec2 uv3,
               ImVec2 uv4,
               ImU32 col)
            {
                self->AddImageQuad(tex.texID, p1, p2, p3, p4, uv1, uv2, uv3, uv4, col);
            },
            "user_texture_id"_a,
            "p1"_a,
            "p2"_a,
            "p3"_a,
            "p4"_a,
            py::arg_v("uv1", ImVec2(0, 0), "Vec2(0, 0)"),
            py::arg_v("uv2", ImVec2(1, 0), "Vec2(1, 0)"),
            py::arg_v("uv3", ImVec2(1, 1), "Vec2(0, 1)"),
            py::arg_v("uv4", ImVec2(0, 1), "Vec2(1, 1)"),
            "col"_a = IM_COL32_WHITE
        )
        .def(
            "AddImageRounded",
            [](ImDrawList* self,
               Texture tex,
               ImVec2 p_min,
               ImVec2 p_max,
               ImVec2 uv_min,
               ImVec2 uv_max,
               ImU32 col,
               float rounding,
               ImDrawFlags flags)
            {
                self->AddImageRounded(
                    tex.texID,
                    p_min,
                    p_max,
                    uv_min,
                    uv_max,
                    col,
                    rounding,
                    flags
                );
            },
            "user_texture_id"_a,
            "p_min"_a,
            "p_max"_a,
            "uv_min"_a,
            "uv_max"_a,
            "col"_a,
            "rounding"_a,
            "flags"_a = 0
        )
        .def(DEF(ImDrawList, PathClear))
        .def(DEF(ImDrawList, PathLineTo), "pos"_a)
        .def(DEF(ImDrawList, PathLineToMergeDuplicate), "pos"_a)
        .def(DEF(ImDrawList, PathFillConvex), "col"_a)
        .def(DEF(ImDrawList, PathFillConcave), "col"_a)
        .def(
            DEF(ImDrawList, PathStroke),
            "col"_a,
            "flags"_a = 0,
            "thickness"_a = 1.0f
        )
        .def(
            DEF(ImDrawList, PathArcTo),
            "center"_a,
            "radius"_a,
            "a_min"_a,
            "a_max"_a,
            "num_segments"_a = 0
        )
        .def(
            DEF(ImDrawList, PathArcToFast),
            "center"_a,
            "radius"_a,
            "a_min_of_12"_a,
            "a_max_of_12"_a
        )
        .def(
            DEF(ImDrawList, PathEllipticalArcTo),
            "center"_a,
            "radius"_a,
            "rot"_a,
            "a_min"_a,
            "a_max"_a,
            "num_segments"_a = 0
        )
        .def(
            DEF(ImDrawList, PathBezierCubicCurveTo),
            "p2"_a,
            "p3"_a,
            "p4"_a,
            "num_segments"_a = 0
        )
        .def(
            DEF(ImDrawList, PathBezierQuadraticCurveTo),
            "p2"_a,
            "p3"_a,
            "num_segments"_a = 0
        )
        .def(
            DEF(ImDrawList, PathRect),
            "rect_min"_a,
            "rect_max"_a,
            "rounding"_a = 0.0f,
            "flags"_a = 0
        )
        // TODO callbacks?
        // Channels
        .def(DEF(ImDrawList, ChannelsSplit), "count"_a)
        .def(DEF(ImDrawList, ChannelsMerge))
        .def(DEF(ImDrawList, ChannelsSetCurrent), "n"_a);
    // TODO primitive allocations?
}