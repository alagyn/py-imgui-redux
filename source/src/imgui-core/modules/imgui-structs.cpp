#include <bind-imgui/imgui-modules.h>
#include <binder/list-wrapper.h>
#include <binder/struct-utility.h>

#define RO_ARRAY(STRUCT, TYPE, VALUE, SIZE) \
    def_property_readonly( \
        #VALUE, \
        [](STRUCT* self) \
        { \
            return ListWrapper<TYPE>(self->VALUE, SIZE); \
        } \
    )

void init_imgui_structs(py::module& m)
{
    initListWrapper<bool>(m, "ListWrapperBool");
    initListWrapper<ImVec2>(m, "ListWrapperImVec2");
    initListWrapper<double>(m, "ListWrapperDouble");
    initListWrapper<ImGuiTableColumnSortSpecs>(m, "ListWrapperTCSS");

    // Vectors
    py::class_<ImVec2>(m, "Vec2")
        .RW(ImVec2, x)
        .RW(ImVec2, y)
        .def(py::init<>())
        .def(py::init<float, float>(), "x"_a, "y"_a);

    py::class_<ImVec4>(m, "Vec4")
        .RW(ImVec4, x)
        .RW(ImVec4, y)
        .RW(ImVec4, z)
        .RW(ImVec4, w)
        .def(py::init<>())
        .def(py::init<float, float, float, float>(), "x"_a, "y"_a, "z"_a, "w"_a);

    // Style
    py::class_<ImGuiStyle>(m, "Style")
        .RW(ImGuiStyle, Alpha)
        .RW(ImGuiStyle, DisabledAlpha)
        .RW(ImGuiStyle, WindowPadding)
        .RW(ImGuiStyle, WindowRounding)
        .RW(ImGuiStyle, WindowBorderSize)
        .RW(ImGuiStyle, WindowMinSize)
        .RW(ImGuiStyle, WindowTitleAlign)
        .RW(ImGuiStyle, WindowMenuButtonPosition)
        .RW(ImGuiStyle, ChildRounding)
        .RW(ImGuiStyle, ChildBorderSize)
        .RW(ImGuiStyle, PopupRounding)
        .RW(ImGuiStyle, PopupBorderSize)
        .RW(ImGuiStyle, FramePadding)
        .RW(ImGuiStyle, FrameRounding)
        .RW(ImGuiStyle, FrameBorderSize)
        .RW(ImGuiStyle, ItemSpacing)
        .RW(ImGuiStyle, ItemInnerSpacing)
        .RW(ImGuiStyle, CellPadding)
        .RW(ImGuiStyle, TouchExtraPadding)
        .RW(ImGuiStyle, IndentSpacing)
        .RW(ImGuiStyle, ColumnsMinSpacing)
        .RW(ImGuiStyle, ScrollbarSize)
        .RW(ImGuiStyle, ScrollbarRounding)
        .RW(ImGuiStyle, GrabMinSize)
        .RW(ImGuiStyle, GrabRounding)
        .RW(ImGuiStyle, LogSliderDeadzone)
        .RW(ImGuiStyle, TabRounding)
        .RW(ImGuiStyle, TabBorderSize)
        .RW(ImGuiStyle, TabMinWidthForCloseButton)
        .RW(ImGuiStyle, ColorButtonPosition)
        .RW(ImGuiStyle, ButtonTextAlign)
        .RW(ImGuiStyle, SelectableTextAlign)
        .RW(ImGuiStyle, DisplayWindowPadding)
        .RW(ImGuiStyle, DisplaySafeAreaPadding)
        .RW(ImGuiStyle, MouseCursorScale)
        .RW(ImGuiStyle, AntiAliasedLines)
        .RW(ImGuiStyle, AntiAliasedLinesUseTex)
        .RW(ImGuiStyle, AntiAliasedFill)
        .RW(ImGuiStyle, CurveTessellationTol)
        .RW(ImGuiStyle, CircleTessellationMaxError)
        .RO_ARRAY(ImGuiStyle, ImVec4, Colors, ImGuiCol_COUNT)
        .RW(ImGuiStyle, HoverStationaryDelay)
        .RW(ImGuiStyle, HoverDelayShort)
        .RW(ImGuiStyle, HoverDelayNormal)
        .RW(ImGuiStyle, HoverFlagsForTooltipMouse)
        .RW(ImGuiStyle, HoverFlagsForTooltipNav)

        .def(py::init<>())
        .def(DEF(ImGuiStyle, ScaleAllSizes), "scale_factor"_a);

    py::class_<ImGuiKeyData>(m, "KeyData")
        .RO(ImGuiKeyData, Down)
        .RO(ImGuiKeyData, DownDuration)
        .RO(ImGuiKeyData, DownDurationPrev)
        .RO(ImGuiKeyData, AnalogValue);

    py::class_<ImGuiIO>(m, "IO")
        .RW(ImGuiIO, ConfigFlags)
        .RW(ImGuiIO, BackendFlags)
        .RW(ImGuiIO, DisplaySize)
        .RW(ImGuiIO, DeltaTime)
        .RW(ImGuiIO, IniSavingRate)
        .RW(ImGuiIO, IniFilename)
        .RW(ImGuiIO, LogFilename)
        // Fonts
        .RW(ImGuiIO, Fonts)
        .RW(ImGuiIO, FontGlobalScale)
        .RW(ImGuiIO, FontAllowUserScaling)
        .RW(ImGuiIO, FontDefault)
        .RW(ImGuiIO, DisplayFramebufferScale)
        // Misc
        .RW(ImGuiIO, MouseDrawCursor)
        .RW(ImGuiIO, ConfigMacOSXBehaviors)
        .RW(ImGuiIO, ConfigInputTrickleEventQueue)
        .RW(ImGuiIO, ConfigInputTextCursorBlink)
        .RW(ImGuiIO, ConfigInputTextEnterKeepActive)
        .RW(ImGuiIO, ConfigDragClickToInputText)
        .RW(ImGuiIO, ConfigWindowsResizeFromEdges)
        .RW(ImGuiIO, ConfigWindowsMoveFromTitleBarOnly)
        .RW(ImGuiIO, ConfigMemoryCompactTimer)
        // Input
        .RW(ImGuiIO, MouseDoubleClickTime)
        .RW(ImGuiIO, MouseDoubleClickMaxDist)
        .RW(ImGuiIO, MouseDragThreshold)
        .RW(ImGuiIO, KeyRepeatDelay)
        .RW(ImGuiIO, KeyRepeatRate)
        .RW(ImGuiIO, ConfigDebugIsDebuggerPresent)
        .RW(ImGuiIO, ConfigDebugBeginReturnValueOnce)
        .RW(ImGuiIO, ConfigDebugBeginReturnValueLoop)
        .RW(ImGuiIO, ConfigDebugIgnoreFocusLoss)
        .RW(ImGuiIO, ConfigDebugIniSettings)
        // Optional names
        .RW(ImGuiIO, BackendPlatformName)
        .RW(ImGuiIO, BackendRendererName)
        .RW(ImGuiIO, BackendPlatformUserData)
        .RW(ImGuiIO, BackendRendererUserData)
        .RW(ImGuiIO, BackendLanguageUserData)
        // TODO Ignoring Clipboard stuff
        .def(DEF(ImGuiIO, AddKeyEvent), "key"_a, "down"_a)
        .def(DEF(ImGuiIO, AddKeyAnalogEvent), "key"_a, "down"_a, "v"_a)
        .def(DEF(ImGuiIO, AddMousePosEvent), "x"_a, "y"_a)
        .def(DEF(ImGuiIO, AddMouseButtonEvent), "button"_a, "down"_a)
        .def(DEF(ImGuiIO, AddMouseWheelEvent), "wh_x"_a, "wh_y"_a)
        .def(DEF(ImGuiIO, AddMouseSourceEvent), "source"_a)
        .def(DEF(ImGuiIO, AddFocusEvent), "focused"_a)
        .def(DEF(ImGuiIO, AddInputCharacter), "c"_a)
        .def(DEF(ImGuiIO, AddInputCharacterUTF16), "c"_a)
        .def(DEF(ImGuiIO, AddInputCharactersUTF8), "str"_a)
        .def(
            DEF(ImGuiIO, SetKeyEventNativeData),
            "key"_a,
            "native_keycode"_a,
            "native_scancode"_a,
            "native_legacy_index"_a = -1
        )
        .def(DEF(ImGuiIO, SetAppAcceptingEvents), "accepting_events"_a)
        .def(DEF(ImGuiIO, ClearEventsQueue))
        .def(DEF(ImGuiIO, ClearInputKeys))
        .RW(ImGuiIO, WantCaptureMouse)
        .RW(ImGuiIO, WantCaptureKeyboard)
        .RW(ImGuiIO, WantTextInput)
        .RW(ImGuiIO, WantSetMousePos)
        .RW(ImGuiIO, WantSaveIniSettings)
        .RO(ImGuiIO, NavActive)
        .RO(ImGuiIO, NavVisible)
        .RO(ImGuiIO, Framerate)
        .RO(ImGuiIO, MetricsRenderVertices)
        .RO(ImGuiIO, MetricsRenderIndices)
        .RO(ImGuiIO, MetricsRenderWindows)
        .RO(ImGuiIO, MetricsActiveWindows)
        .RO(ImGuiIO, MouseDelta)
        // Main  Input State
        .RW(ImGuiIO, MousePos)
        .RO_ARRAY(ImGuiIO, bool, MouseDown, 5)
        //.RW(ImGuiIO, MouseDown)
        .RW(ImGuiIO, MouseWheel)
        .RW(ImGuiIO, MouseWheelH)
        .RW(ImGuiIO, KeyCtrl)
        .RW(ImGuiIO, KeyShift)
        .RW(ImGuiIO, KeyAlt)
        .RW(ImGuiIO, KeySuper)
        // Other state
        .RW(ImGuiIO, KeyMods)
        // Ignoring KeysData, use IsKeyXXX
        .RW(ImGuiIO, WantCaptureMouseUnlessPopupClose)
        .RW(ImGuiIO, MousePosPrev)
        .RO_ARRAY(ImGuiIO, ImVec2, MouseClickedPos, 5)
        .RO_ARRAY(ImGuiIO, double, MouseClickedTime, 5)
        .RO_ARRAY(ImGuiIO, bool, MouseClicked, 5)
        .RO_ARRAY(ImGuiIO, bool, MouseDoubleClicked, 5)
        .RO_ARRAY(ImGuiIO, ImU16, MouseClickedCount, 5)
        .RO_ARRAY(ImGuiIO, ImU16, MouseClickedLastCount, 5)
        .RO_ARRAY(ImGuiIO, bool, MouseReleased, 5)
        .RO_ARRAY(ImGuiIO, bool, MouseDownOwned, 5)
        .RO_ARRAY(ImGuiIO, bool, MouseDownOwnedUnlessPopupClose, 5)
        .RW(ImGuiIO, MouseWheelRequestAxisSwap)
        .RO_ARRAY(ImGuiIO, float, MouseDownDuration, 5)
        .RO_ARRAY(ImGuiIO, float, MouseDownDurationPrev, 5)
        .RO_ARRAY(ImGuiIO, float, MouseDragMaxDistanceSqr, 5)
        .RW(ImGuiIO, PenPressure)
        .RW(ImGuiIO, AppFocusLost)
        .RW(ImGuiIO, AppAcceptingEvents)
        .RW(ImGuiIO, BackendUsingLegacyKeyArrays)
        .RW(ImGuiIO, BackendUsingLegacyNavInputArray)
        .RW(ImGuiIO, InputQueueSurrogate)
        .def(py::init<>());

    py::class_<ImGuiListClipper>(m, "ListClipper")
        .def(py::init<>())
        .def(
            DEF(ImGuiListClipper, Begin),
            "items_count"_a,
            "items_height"_a = -1.0f
        )
        .def(DEF(ImGuiListClipper, End))
        .def(DEF(ImGuiListClipper, Step))
        .def(DEF(ImGuiListClipper, IncludeItemByIndex), "item_index"_a)
        .def(
            DEF(ImGuiListClipper, IncludeItemsByIndex),
            "item_begin"_a,
            "item_end"_a
        )
        .RO(ImGuiListClipper, DisplayStart)
        .RO(ImGuiListClipper, DisplayEnd);

    py::class_<ImGuiTableSortSpecs>(m, "TableSortSpecs")
        .def(py::init<>())
        .RO_ARRAY(
            ImGuiTableSortSpecs,
            ImGuiTableColumnSortSpecs,
            Specs,
            self->SpecsCount
        )
        .RW(ImGuiTableSortSpecs, SpecsDirty);

    py::class_<ImGuiTableColumnSortSpecs>(m, "TableColumnSortSpecs")
        .RW(ImGuiTableColumnSortSpecs, ColumnUserID)
        .RW(ImGuiTableColumnSortSpecs, ColumnIndex)
        .RW(ImGuiTableColumnSortSpecs, SortOrder)
        .def_property(
            "SortDirection",
            [](ImGuiTableColumnSortSpecs* self)
            {
                return self->SortDirection;
            },
            [](ImGuiTableColumnSortSpecs* self, ImGuiSortDirection val)
            {
                self->SortDirection = val;
            }
        )
        .def(py::init<>());

    py::class_<ImColor>(m, "Color")
        .RW(ImColor, Value)
        .def(py::init<>())
        .def(
            py::init<float, float, float, float>(),
            "r"_a,
            "g"_a,
            "b"_a,
            "a"_a = 1.0f
        )
        .def(py::init<int, int, int, int>(), "r"_a, "g"_a, "b"_a, "a"_a = 255)
        .def(DEF(ImColor, SetHSV), "h"_a, "s"_a, "v"_a, "a"_a = 1.0f)
        .def_static(DEF(ImColor, HSV), "h"_a, "s"_a, "v"_a, "a"_a = 1.0f);

    py::class_<ImFont>(m, "ImFont")
        .RW(ImFont, IndexAdvanceX)
        .RW(ImFont, FallbackAdvanceX)
        .RW(ImFont, FontSize)
        .RW(ImFont, IndexLookup)
        .RW(ImFont, Glyphs)
        .RW(ImFont, FallbackGlyph)
        .RW(ImFont, ContainerAtlas)
        .RW(ImFont, ConfigData)
        .RW(ImFont, ConfigDataCount)
        .RW(ImFont, FallbackChar)
        .RW(ImFont, EllipsisChar)
        .RW(ImFont, EllipsisCharCount)
        .RW(ImFont, EllipsisWidth)
        .RW(ImFont, EllipsisCharStep)
        .RW(ImFont, DirtyLookupTables)
        .RW(ImFont, Scale)
        .RW(ImFont, Ascent)
        .RW(ImFont, Descent)
        .RW(ImFont, MetricsTotalSurface)
        // TODO Used4kPagesMap?
        .def(DEF(ImFont, FindGlyph), "c"_a, py::return_value_policy::reference)
        .def(
            DEF(ImFont, FindGlyphNoFallback),
            "c"_a,
            py::return_value_policy::reference
        )
        .def(DEF(ImFont, GetCharAdvance), "c"_a)
        .def(DEF(ImFont, IsLoaded))
        .def(DEF(ImFont, GetDebugName), py::return_value_policy::reference)
        .def(
            "CalcTextSizeA",
            [](ImFont* self, const char* text, float max_width, float wrap_width)
            {
                return self
                    ->CalcTextSizeA(self->FontSize, max_width, wrap_width, text);
            },
            "text"_a,
            "max_width"_a = FLT_MAX,
            "wrap_width"_a = -1.0
        )
        // TODO CalcWordWrapPositionA
        .def(DEF(ImFont, RenderChar), "draw_list"_a, "size"_a, "pos"_a, "col"_a, "c"_a)
        // TODO RenderText
        ;

    py::class_<ImFontConfig>(m, "ImFontConfig")
        .RW(ImFontConfig, FontDataSize)
        .RW(ImFontConfig, FontDataOwnedByAtlas)
        .RW(ImFontConfig, FontNo)
        .RW(ImFontConfig, SizePixels)
        .RW(ImFontConfig, OversampleH)
        .RW(ImFontConfig, OversampleV)
        .RW(ImFontConfig, PixelSnapH)
        .RW(ImFontConfig, GlyphExtraSpacing)
        .RW(ImFontConfig, GlyphOffset)
        .RW(ImFontConfig, GlyphMinAdvanceX)
        .RW(ImFontConfig, GlyphMaxAdvanceX)
        .RW(ImFontConfig, MergeMode)
        .RW(ImFontConfig, FontBuilderFlags)
        .RW(ImFontConfig, RasterizerMultiply)
        .RW(ImFontConfig, RasterizerDensity)
        .RW(ImFontConfig, EllipsisChar)
        .def(py::init<>());

    py::class_<ImFontGlyph>(m, "ImFontGlyph")
        .def_property(
            "Colored",
            [](ImFontGlyph* self)
            {
                return self->Colored;
            },
            [](ImFontGlyph* self, unsigned int val)
            {
                self->Colored = val;
            }
        )
        .def_property(
            "Visible",
            [](ImFontGlyph* self)
            {
                return self->Visible;
            },
            [](ImFontGlyph* self, unsigned int val)
            {
                self->Visible = val;
            }
        )
        .def_property(
            "Codepoint",
            [](ImFontGlyph* self)
            {
                return self->Codepoint;
            },
            [](ImFontGlyph* self, unsigned int val)
            {
                self->Codepoint = val;
            }
        )
        .RW(ImFontGlyph, AdvanceX)
        .RW(ImFontGlyph, X0)
        .RW(ImFontGlyph, X1)
        .RW(ImFontGlyph, Y0)
        .RW(ImFontGlyph, Y1)
        .RW(ImFontGlyph, U0)
        .RW(ImFontGlyph, U1)
        .RW(ImFontGlyph, V0)
        .RW(ImFontGlyph, V1);

    py::class_<ImFontAtlas>(m, "ImFontAtlas")
        .def(
            DEF(ImFontAtlas, AddFont),
            "font_cfg"_a,
            py::return_value_policy::reference
        )
        .def(
            DEF(ImFontAtlas, AddFontDefault),
            "font_cfg"_a = nullptr,
            py::return_value_policy::reference
        )
        /*
        .def(
            DEF(ImFontAtlas, AddFontFromFileTTF),
            "filename"_a,
            "size_pixels"_a,
            "font_cfg"_a = nullptr,
            "glyph_ranges"_a = nullptr
        )
        */
        .def(
            "AddFontFromFileTTF",
            [](ImFontAtlas* self,
               const char* filename,
               float size_pixels,
               ImFontConfig* font_cfg = nullptr)
            {
                return self->AddFontFromFileTTF(filename, size_pixels, font_cfg);
            },
            "filename"_a,
            "size_pixels"_a,
            "font_cfg"_a = nullptr,
            py::return_value_policy::reference
        )
        // TODO AddFontFromMemory...?
        .def(DEF(ImFontAtlas, ClearInputData))
        .def(DEF(ImFontAtlas, ClearTexData))
        .def(DEF(ImFontAtlas, ClearFonts))
        .def(DEF(ImFontAtlas, Clear))
        .def(DEF(ImFontAtlas, Build))
        // TODO GetTexData...?
        .def(DEF(ImFontAtlas, IsBuilt))
        .def(DEF(ImFontAtlas, SetTexID), "id"_a)
        // TODO GetGlyphRanges...?
        .def(DEF(ImFontAtlas, AddCustomRectRegular), "width"_a, "height"_a)
        .def(
            DEF(ImFontAtlas, AddCustomRectFontGlyph),
            "font"_a,
            "id"_a,
            "width"_a,
            "height"_a,
            "advance_x"_a,
            py::arg_v("offset", ImVec2(0, 0), "Vec2(0, 0)")
        )
        // TODO GetCustomRectByIndex?
        ;

    py::class_<ImGuiViewport>(m, "Viewport")
        .RO(ImGuiViewport, Flags)
        .RO(ImGuiViewport, Pos)
        .RO(ImGuiViewport, Size)
        .RO(ImGuiViewport, WorkPos)
        .RO(ImGuiViewport, WorkSize);
}