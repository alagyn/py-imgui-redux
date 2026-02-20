#include <bind-imgui/callback-structs.h>
#include <bind-imgui/imgui-modules.h>
#include <binder/list-wrapper.h>
#include <binder/struct-utility.h>
#include <binder/wraps.h>
#include <imgui_internal.h>

#define RO_ARRAY(STRUCT, TYPE, VALUE, SIZE) \
    def_property_readonly( \
        #VALUE, \
        [](STRUCT* self) \
        { \
            return ConstListWrapper<TYPE>(self->VALUE, SIZE); \
        } \
    )

#define RW_ARRAY(STRUCT, TYPE, VALUE, SIZE) \
    def_property_readonly( \
        #VALUE, \
        [](STRUCT* self) \
        { \
            return ListWrapper<TYPE>(self->VALUE, SIZE); \
        } \
    )

void init_imgui_structs(py::module& m)
{
    initConstListWrapper<ImVec2>(m, "ConstListWrapperImVec2");
    initConstListWrapper<ImGuiTableColumnSortSpecs>(m, "ConstListWrapperTCSS");
    initListWrapper<ImVec4>(m, "ListWrapperVec4");

    // Vectors
    py::class_<ImVec2>(m, "Vec2")
        .RW(ImVec2, x)
        .RW(ImVec2, y)
        .def(py::init<>())
        .def(py::init<float, float>(), "x"_a, "y"_a)
        .def(
            "__str__",
            [](ImVec2* self)
            {
                std::stringstream ss;
                ss << "im.Vec2(" << self->x << ", " << self->y << ")";
                return ss.str();
            }
        );

    py::class_<ImVec4>(m, "Vec4")
        .RW(ImVec4, x)
        .RW(ImVec4, y)
        .RW(ImVec4, z)
        .RW(ImVec4, w)
        .def(py::init<>())
        .def(py::init<float, float, float, float>(), "x"_a, "y"_a, "z"_a, "w"_a)
        .def(
            "__str__",
            [](ImVec4* self)
            {
                std::stringstream ss;
                ss << "im.Vec4(" << self->x << ", " << self->y << ", "
                   << self->z << ", " << self->w << ")";
                return ss.str();
            }
        );

    // Style
    py::class_<ImGuiStyle>(m, "Style")
        .RW(ImGuiStyle, FontSizeBase)
        .RW(ImGuiStyle, FontScaleMain)
        .RW(ImGuiStyle, FontScaleDpi)
        .RW(ImGuiStyle, Alpha)
        .RW(ImGuiStyle, DisabledAlpha)
        .RW(ImGuiStyle, WindowPadding)
        .RW(ImGuiStyle, WindowRounding)
        .RW(ImGuiStyle, WindowBorderSize)
        .RW(ImGuiStyle, WindowBorderHoverPadding)
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
        .RW(ImGuiStyle, ScrollbarPadding)
        .RW(ImGuiStyle, GrabMinSize)
        .RW(ImGuiStyle, GrabRounding)
        .RW(ImGuiStyle, LogSliderDeadzone)
        .RW(ImGuiStyle, ImageRounding)
        .RW(ImGuiStyle, ImageBorderSize)
        .RW(ImGuiStyle, TabRounding)
        .RW(ImGuiStyle, TabBorderSize)
        .RW(ImGuiStyle, TabMinWidthBase)
        .RW(ImGuiStyle, TabMinWidthShrink)
        .RW(ImGuiStyle, TabCloseButtonMinWidthSelected)
        .RW(ImGuiStyle, TabCloseButtonMinWidthUnselected)
        .RW(ImGuiStyle, TabBarBorderSize)
        .RW(ImGuiStyle, TabBarOverlineSize)
        .RW(ImGuiStyle, TableAngledHeadersAngle)
        .RW(ImGuiStyle, TableAngledHeadersTextAlign)
        .RW(ImGuiStyle, TreeLinesFlags)
        .RW(ImGuiStyle, TreeLinesSize)
        .RW(ImGuiStyle, TreeLinesRounding)
        .RW(ImGuiStyle, DragDropTargetRounding)
        .RW(ImGuiStyle, DragDropTargetBorderSize)
        .RW(ImGuiStyle, DragDropTargetPadding)
        .RW(ImGuiStyle, ColorMarkerSize)
        .RW(ImGuiStyle, ColorButtonPosition)
        .RW(ImGuiStyle, ButtonTextAlign)
        .RW(ImGuiStyle, SelectableTextAlign)
        .RW(ImGuiStyle, SeparatorTextBorderSize)
        .RW(ImGuiStyle, SeparatorTextAlign)
        .RW(ImGuiStyle, SeparatorTextPadding)
        .RW(ImGuiStyle, DisplayWindowPadding)
        .RW(ImGuiStyle, DisplaySafeAreaPadding)
        .RW(ImGuiStyle, MouseCursorScale)
        .RW(ImGuiStyle, AntiAliasedLines)
        .RW(ImGuiStyle, AntiAliasedLinesUseTex)
        .RW(ImGuiStyle, AntiAliasedFill)
        .RW(ImGuiStyle, CurveTessellationTol)
        .RW(ImGuiStyle, CircleTessellationMaxError)
        .RW_ARRAY(ImGuiStyle, ImVec4, Colors, ImGuiCol_COUNT)
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
        .RW(ImGuiIO, FontAllowUserScaling)
        .RW(ImGuiIO, FontDefault)
        .RW(ImGuiIO, DisplayFramebufferScale)
        // Keyboard/Gamepad navigation options
        .RW(ImGuiIO, ConfigNavSwapGamepadButtons)
        .RW(ImGuiIO, ConfigNavMoveSetMousePos)
        .RW(ImGuiIO, ConfigNavCaptureKeyboard)
        .RW(ImGuiIO, ConfigNavEscapeClearFocusItem)
        .RW(ImGuiIO, ConfigNavEscapeClearFocusWindow)
        .RW(ImGuiIO, ConfigNavCursorVisibleAuto)
        .RW(ImGuiIO, ConfigNavCursorVisibleAlways)
        // Misc
        .RW(ImGuiIO, MouseDrawCursor)
        .RW(ImGuiIO, ConfigMacOSXBehaviors)
        .RW(ImGuiIO, ConfigInputTrickleEventQueue)
        .RW(ImGuiIO, ConfigInputTextCursorBlink)
        .RW(ImGuiIO, ConfigInputTextEnterKeepActive)
        .RW(ImGuiIO, ConfigDragClickToInputText)
        .RW(ImGuiIO, ConfigWindowsResizeFromEdges)
        .RW(ImGuiIO, ConfigWindowsMoveFromTitleBarOnly)
        .RW(ImGuiIO, ConfigWindowsCopyContentsWithCtrlC)
        .RW(ImGuiIO, ConfigScrollbarScrollByPage)
        .RW(ImGuiIO, ConfigMemoryCompactTimer)
        // Input
        .RW(ImGuiIO, MouseDoubleClickTime)
        .RW(ImGuiIO, MouseDoubleClickMaxDist)
        .RW(ImGuiIO, MouseDragThreshold)
        .RW(ImGuiIO, KeyRepeatDelay)
        .RW(ImGuiIO, KeyRepeatRate)
        // Debug options
        .RW(ImGuiIO, ConfigErrorRecovery)
        .RW(ImGuiIO, ConfigErrorRecoveryEnableAssert)
        .RW(ImGuiIO, ConfigErrorRecoveryEnableDebugLog)
        .RW(ImGuiIO, ConfigErrorRecoveryEnableTooltip)
        .RW(ImGuiIO, ConfigDebugIsDebuggerPresent)
        .RW(ImGuiIO, ConfigDebugHighlightIdConflicts)
        .RW(ImGuiIO, ConfigDebugHighlightIdConflictsShowItemPicker)
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
        // TODO Ignoring Clipboard stuff/Moved to PlatformIO?
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
        .def(DEF(ImGuiIO, ClearInputMouse))
        // output UI state
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
        .RW(ImGuiIO, MouseCtrlLeftAsRightClick)
        .RO_ARRAY(ImGuiIO, float, MouseDownDuration, 5)
        .RO_ARRAY(ImGuiIO, float, MouseDownDurationPrev, 5)
        .RO_ARRAY(ImGuiIO, float, MouseDragMaxDistanceSqr, 5)
        .RW(ImGuiIO, PenPressure)
        .RW(ImGuiIO, AppFocusLost)
        .RW(ImGuiIO, AppAcceptingEvents)
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
        .def(DEF(ImGuiListClipper, SeekCursorForItem), "item_index"_a)
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

    py::class_<ImFontBaked>(m, "ImFontBaked")
        // Should we expose these internals?
        // .RO(ImFontBaked, IndexAdvanceX)
        // .RO(ImFontBaked, FallbackAdvanceX)
        // .RO(ImFontBaked, Size)
        // .RO(ImFontBaked, RasterizerDensity)
        // .RO(ImFontBaked, IndexLookup)
        // .RO(ImFontBaked, Glyphs)
        // .RO(ImFontBaked, FallbackGlyphIndex)
        // .RO(ImFontBaked, Ascent)
        // .RO(ImFontBaked, Descent)
        .def(DEF(ImFontBaked, FindGlyph), "c"_a, py::return_value_policy::reference)
        .def(
            DEF(ImFontBaked, FindGlyphNoFallback),
            "c"_a,
            py::return_value_policy::reference
        )
        .def(DEF(ImFontBaked, GetCharAdvance), "c"_a)
        .def(DEF(ImFontBaked, IsGlyphLoaded));

    py::class_<ImFont>(m, "ImFont")
        // .RO(ImFont, ContainerAtlas)
        // .RO(ImFont, Flags)
        // .RO(ImFont, CurrentRasterizerDensity)
        // .RO(ImFont, FontId)
        .RO(ImFont, LegacySize)
        // TODO Sources?
        .RO(ImFont, EllipsisChar)
        .RO(ImFont, FallbackChar)
        // TODO Used8kPagesMap?
        // TODO RemapPairs?
        .def(DEF(ImFont, IsGlyphInFont), "c"_a)
        .def(DEF(ImFont, IsLoaded))
        .def(DEF(ImFont, GetDebugName))
        .def(DEF(ImFont, GetFontBaked), "font_size"_a, "density"_a = -1.0f)
        .def(
            "CalcTextSizeA",
            [](ImFont* self,
               float size,
               const char* text,
               float max_width,
               float wrap_width)
            {
                return self->CalcTextSizeA(size, max_width, wrap_width, text);
            },
            "size"_a,
            "text"_a,
            "max_width"_a,
            "wrap_width"_a
        )
        .def(
            "CalcWordWrapPosition",
            [](ImFont* self, float size, const char* text, float wrap_width)
            {
                return self->CalcWordWrapPosition(size, text, nullptr, wrap_width);
            },
            "size"_a,
            "text"_a,
            "wrap_width"_a
        )
        // TODO Render funcs?
        // TODO other internal stuff?
        ;

    py::class_<ImFontConfig>(m, "ImFontConfig")
        .RW(ImFontConfig, FontDataSize)
        .RW(ImFontConfig, FontDataOwnedByAtlas)
        .RW(ImFontConfig, MergeMode)
        .RW(ImFontConfig, PixelSnapH)
        .RW(ImFontConfig, OversampleH)
        .RW(ImFontConfig, OversampleV)
        .RW(ImFontConfig, EllipsisChar)
        .RW(ImFontConfig, SizePixels)
        .RW(ImFontConfig, GlyphOffset)
        .RW(ImFontConfig, GlyphMinAdvanceX)
        .RW(ImFontConfig, GlyphMaxAdvanceX)
        .RW(ImFontConfig, GlyphExtraAdvanceX)
        .RW(ImFontConfig, FontNo)
        .RW(ImFontConfig, FontLoaderFlags)
        .RW(ImFontConfig, RasterizerMultiply)
        .RW(ImFontConfig, RasterizerDensity)
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

    py::class_<ImFontAtlasRect>(m, "ImFontAtlasRect")
        .RO(ImFontAtlasRect, x)
        .RO(ImFontAtlasRect, y)
        .RO(ImFontAtlasRect, w)
        .RO(ImFontAtlasRect, h)
        .RO(ImFontAtlasRect, uv0)
        .RO(ImFontAtlasRect, uv1)
        .def(py::init<>());

    py::class_<ImFontAtlas>(m, "ImFontAtlas")
        .RW(ImFontAtlas, Flags)
        .RW(ImFontAtlas, TexDesiredFormat)
        .RW(ImFontAtlas, TexGlyphPadding)
        .RW(ImFontAtlas, TexMinWidth)
        .RW(ImFontAtlas, TexMinHeight)
        .RW(ImFontAtlas, TexMaxWidth)
        .RW(ImFontAtlas, TexMaxHeight)
        .RO(ImFontAtlas, TexRef)
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
        .def(
            DEF(ImFontAtlas, AddFontDefaultVector),
            "font_cfg"_a = nullptr,
            py::return_value_policy::reference
        )
        .def(
            DEF(ImFontAtlas, AddFontDefaultBitmap),
            "font_cfg"_a = nullptr,
            py::return_value_policy::reference
        )
        .def(
            "AddFontFromFileTTF",
            [](ImFontAtlas* self,
               const char* filename,
               float size_pixels,
               ImFontConfig* font_cfg,
               WCharListPtr glyph_ranges)
            {
                if(glyph_ranges)
                {
                    return self->AddFontFromFileTTF(
                        filename,
                        size_pixels,
                        font_cfg,
                        glyph_ranges->vals.data()
                    );
                }
                return self->AddFontFromFileTTF(filename, size_pixels, font_cfg);
            },
            "filename"_a,
            "size_pixels"_a,
            "font_cfg"_a = nullptr,
            "glyph_ranges"_a = nullptr,
            py::return_value_policy::reference
        )
        // TODO AddFontFromMemory...?
        .def(DEF(ImFontAtlas, RemoveFont), "font"_a)
        .def(DEF(ImFontAtlas, Clear))
        .def(DEF(ImFontAtlas, CompactCache))
        // .def(DEF(ImFontAtlas, SetFontLoader), "font_loader"_a)
        .def(DEF(ImFontAtlas, ClearInputData))
        .def(DEF(ImFontAtlas, ClearFonts))
        .def(DEF(ImFontAtlas, ClearTexData))
        .def(DEF(ImFontAtlas, GetGlyphRangesDefault))
        .def(
            DEF(ImFontAtlas, AddCustomRect),
            "width"_a,
            "height"_a,
            "out_r"_a = nullptr
        )
        .def(DEF(ImFontAtlas, RemoveCustomRect), "id"_a)
        .def(DEF(ImFontAtlas, GetCustomRect), "id"_a, "out_r"_a);

    py::class_<ImGuiViewport>(m, "Viewport")
        .RW(ImGuiViewport, Flags)
        .RW(ImGuiViewport, Pos)
        .RW(ImGuiViewport, Size)
        .RW(ImGuiViewport, WorkPos)
        .RW(ImGuiViewport, WorkSize)
        .def(DEF(ImGuiViewport, GetCenter))
        .def(DEF(ImGuiViewport, GetWorkCenter));

    py::class_<ImGuiMultiSelectIO>(m, "MultiSelectIO")
        // TODO Requests
        .RO(ImGuiMultiSelectIO, Requests)
        .RO(ImGuiMultiSelectIO, RangeSrcItem)
        .RO(ImGuiMultiSelectIO, NavIdItem)
        .RO(ImGuiMultiSelectIO, NavIdSelected)
        .RW(ImGuiMultiSelectIO, RangeSrcReset)
        .RO(ImGuiMultiSelectIO, ItemsCount);

    py::class_<ImGuiSelectionRequest>(m, "SelectionRequest")
        .RO(ImGuiSelectionRequest, Type)
        .RO(ImGuiSelectionRequest, Selected)
        .RO(ImGuiSelectionRequest, RangeDirection)
        .RO(ImGuiSelectionRequest, RangeFirstItem)
        .RO(ImGuiSelectionRequest, RangeLastItem);

    py::class_<ImDrawData>(m, "DrawData")
        .RO(ImDrawData, Valid)
        .RO(ImDrawData, CmdListsCount)
        .RO(ImDrawData, TotalIdxCount)
        .RO(ImDrawData, TotalVtxCount)
        // TODO CmdLists
        .RW(ImDrawData, DisplayPos)
        .RW(ImDrawData, DisplaySize)
        .RW(ImDrawData, FramebufferScale)
        // TODO Funcs
        ;

    py::class_<ImGuiInputTextCallbackData>(m, "InputTextCallbackData")
        .RO(ImGuiInputTextCallbackData, Ctx)
        .RO(ImGuiInputTextCallbackData, EventFlag)
        .RO(ImGuiInputTextCallbackData, Flags)
        .def_property_readonly(
            "UserData",
            [](ImGuiInputTextCallbackData* self)
            {
                auto data = static_cast<InputTextCallbackData*>(self->UserData);
                return data->userData;
            }
        )
        .RO(ImGuiInputTextCallbackData, ID)
        .RO(ImGuiInputTextCallbackData, EventKey)
        .RW(ImGuiInputTextCallbackData, EventChar)
        .RO(ImGuiInputTextCallbackData, EventActivated)
        .RW(ImGuiInputTextCallbackData, BufDirty)
        .RW(ImGuiInputTextCallbackData, Buf)
        .RW(ImGuiInputTextCallbackData, BufTextLen)
        .RO(ImGuiInputTextCallbackData, BufSize)
        .RW(ImGuiInputTextCallbackData, CursorPos)
        .RW(ImGuiInputTextCallbackData, SelectionStart)
        .RW(ImGuiInputTextCallbackData, SelectionEnd)
        .def(DEF(ImGuiInputTextCallbackData, DeleteChars), "pos"_a, "bytes_count"_a)
        .def(
            "InsertChars",
            [](ImGuiInputTextCallbackData* self, int pos, const char* text)
            {
                self->InsertChars(pos, text);
            },
            "pos"_a,
            "text"_a
        )
        .def(DEF(ImGuiInputTextCallbackData, SelectAll))
        .def(DEF(ImGuiInputTextCallbackData, SetSelection), "s"_a, "e"_a)
        .def(DEF(ImGuiInputTextCallbackData, ClearSelection))
        .def(DEF(ImGuiInputTextCallbackData, HasSelection));

    py::class_<ImGuiSizeCallbackData>(m, "SizeCallbackData")
        .def_property_readonly(
            "UserData",
            [](ImGuiSizeCallbackData* self)
            {
                auto data = static_cast<SizeCallbackData*>(self->UserData);
                return data->userData;
            }
        )
        .RO(ImGuiSizeCallbackData, Pos)
        .RO(ImGuiSizeCallbackData, CurrentSize)
        .RW(ImGuiSizeCallbackData, DesiredSize);
}