#include <binder/inc/struct-utility.h>
#include <imgui-core/inc/imgui-modules.h>

void init_imgui_structs(py::module& m)
{
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
        .RO(ImGuiStyle, Colors)
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
        .RW(ImGuiIO, MouseDoubleClickTime)
        .RW(ImGuiIO, MouseDoubleClickMaxDist)
        .RW(ImGuiIO, MouseDragThreshold)
        .RW(ImGuiIO, KeyRepeatDelay)
        .RW(ImGuiIO, KeyRepeatRate)
        .RW(ImGuiIO, HoverDelayNormal)
        .RW(ImGuiIO, HoverDelayShort)
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
        .def(DEF(ImGuiIO, AddFocusEvent), "focused"_a)
        .def(DEF(ImGuiIO, AddInputCharacter), "c"_a)
        .def(DEF(ImGuiIO, AddInputCharactersUTF8), "str"_a)
        .def(
            DEF(ImGuiIO, SetKeyEventNativeData),
            "key"_a,
            "native_keycode"_a,
            "native_scancode"_a,
            "native_legacy_index"_a = -1
        )
        .def(DEF(ImGuiIO, SetAppAcceptingEvents), "accepting_events"_a)
        .def(DEF(ImGuiIO, ClearInputCharacters))
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
        .RO(ImGuiIO, MetricsActiveAllocations)
        .RO(ImGuiIO, MouseDelta)
        // Main  Input State
        // TODO?
        /*
        .RW(ImGuiIO, MousePos)
        .RW(ImGuiIO, MouseDown)
        .RW(ImGuiIO, MouseWheel)
        .RW(ImGuiIO, MouseWheelH)
        .RW(ImGuiIO, KeyCtrl)
        .RW(ImGuiIO, KeyShift)
        .RW(ImGuiIO, KeyAlt)
        .RW(ImGuiIO, KeySuper)
        */
        .def(py::init<>());

    py::class_<ImGuiTableColumnSortSpecs>(m, "TableColumnSortSpecs")
        .RW(ImGuiTableColumnSortSpecs, ColumnUserID)
        .RW(ImGuiTableColumnSortSpecs, ColumnIndex)
        .RW(ImGuiTableColumnSortSpecs, SortOrder)
        // TODO SortDirection
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
}