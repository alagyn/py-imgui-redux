import sys

sys.path.append("../build/bind-imgui/Release")
sys.path.append("../build/bind-imgui")
import time
import numpy as np
import random

import imgui  # type: ignore
import imgui.glfw as glfw  # type: ignore
import imgui.implot as implot  # type: ignore


class State:

    def __init__(self) -> None:
        self.cb1 = False
        self.radio = -1
        self.progress = 0.0
        self.progressTime = time.perf_counter()
        self.comboVal = "Select Me"
        self.listboxVal = [False, False]

        self.fltVal1 = imgui.FloatRef(0.0)
        self.fltVal2 = imgui.FloatRef(0.0)
        self.fltVal3 = imgui.FloatRef(0.0)
        self.fltList = imgui.FloatList([0.0, 0.0, 0.0, 0.0])

        self.intVal1 = imgui.IntRef(0)
        self.intVal2 = imgui.IntRef(0)
        self.intVal3 = imgui.IntRef(0)
        self.intList = imgui.IntList([0, 0, 0, 0])

        self.plotMode = 0

        self.plotSize = 1000
        self.plotMin = 0
        self.plotMax = 10
        self.plotX = np.arange(self.plotSize, dtype=np.float64)
        self.plotY = np.array(
            np.random.rand(self.plotSize) * self.plotMax, dtype=np.float64
        )
        self.plotIdx = 0

        self.lastUpate = time.perf_counter()
        self.updatePeriod = 0.5


def normWidgets(state: State):
    if imgui.BeginTable("tab1", 3):
        imgui.TableNextRow()
        imgui.TableNextColumn()
        if imgui.Button("B1"):
            print("B1")
        imgui.Text("This is ")
        imgui.SameLine()
        if imgui.SmallButton("a small button"):
            print("Small button")
        imgui.Text("Invisible btn ->")
        imgui.SameLine()
        if imgui.InvisibleButton("invis_btn", imgui.Vec2(50, 20)):
            print("Invis Btn")
        if imgui.ArrowButton("arrw_btn", 0):
            print("Arrow Btn")

        pressed, state.cb1 = imgui.CheckBox("Checkbox", state.cb1)
        if pressed:
            print("Checkbox")
        # TODO checkbox flags
        if imgui.Button("Reset Radio"):
            state.radio = -1
        if imgui.RadioButton("Radio0", state.radio == 0):
            state.radio = 0
        if imgui.RadioButton("Radio1", state.radio == 1):
            state.radio = 1

        imgui.ProgressBar(state.progress, imgui.Vec2(100, 20))
        if time.perf_counter() - state.progressTime > 0.5:
            state.progress += 0.1
            if state.progress > 1:
                state.progress = 0
            state.progressTime = time.perf_counter()

        if imgui.BeginCombo("Combo", state.comboVal):
            if imgui.Selectable("Select1"):
                state.comboVal = "Select1"
            elif imgui.Selectable("Select2"):
                state.comboVal = "Select2"
            imgui.EndCombo()

        if imgui.BeginListBox("Listbox"):
            for idx, val in enumerate(state.listboxVal):
                if imgui.Selectable(f"Listbox{idx}", selected=val):
                    state.listboxVal[idx] = not val
            imgui.EndListBox()

        if imgui.BeginMainMenuBar():
            if imgui.MenuItem("Item1"):
                print("Menu1")
            elif imgui.MenuItem("Item2"):
                print("Menu2")
            elif imgui.BeginMenu("Menu1"):
                if imgui.MenuItem("SubMenu1"):
                    print("SubMenu1")
                elif imgui.MenuItem("SubMenu2"):
                    print("SubMenu2")
                imgui.EndMenu()
            imgui.EndMainMenuBar()

        if imgui.BeginMenu("Window Menu"):
            if imgui.MenuItem("WindowMenu1"):
                print("WindowItem1")
            if imgui.MenuItem("WindowMenu2"):
                print("WindowItem2")
            imgui.EndMenu()

        imgui.Text("Tooltip")
        if imgui.IsItemHovered():
            imgui.BeginTooltip()
            imgui.Text("This is a tooltip")
            imgui.EndTooltip()

        if imgui.BeginPopup("popup"):
            if imgui.Selectable("Beep"):
                print("Sheep")
            imgui.EndPopup()

        if imgui.Button("Popup"):
            imgui.OpenPopup("popup")

        visible, op = imgui.BeginPopupModal("nc-modal")
        if visible:
            imgui.Selectable("ASDFASDF")
            imgui.EndPopup()

        visible, op = imgui.BeginPopupModal("c-modal", True)
        if visible:
            imgui.Selectable("ASDFASDF")
            imgui.Dummy(imgui.Vec2(10, 20))
            imgui.Text("Hover to close")
            if imgui.IsItemHovered():
                imgui.CloseCurrentPopup()
            imgui.EndPopup()

        if imgui.Button("Non-Closable Modal"):
            imgui.OpenPopup("nc-modal")

        if imgui.Button("Closable Modal"):
            imgui.OpenPopup("c-modal")

        imgui.Text("right click me")
        if imgui.BeginPopupContextItem("ctx-item"):
            imgui.Selectable("asdf")
            imgui.Selectable("potato")
            imgui.Selectable("whatever")
            imgui.EndPopup()

        if imgui.IsPopupOpen("ctx-item"):
            print("Open")

        imgui.TableNextColumn()

        # int drags
        imgui.DragInt("int 1", state.intVal1)
        imgui.DragInt2("int 2", state.intList)
        imgui.DragInt3("int 3", state.intList)
        imgui.DragInt4("int 4", state.intList)
        imgui.DragIntRange2("int range 2", state.intVal2, state.intVal3)

        imgui.Dummy(imgui.Vec2(10, 30))

        # float drags
        imgui.DragFloat("flt 1", state.fltVal1)
        imgui.DragFloat2("flt 2", state.fltList)
        imgui.DragFloat3("flt 3", state.fltList)
        imgui.DragFloat4("flt 4", state.fltList)
        imgui.DragFloatRange2("flt range 2", state.fltVal2, state.fltVal3)

        imgui.EndTable()


def tables():
    COLS = 3
    ROWS = 10
    flags = (
        imgui.TableFlags.BordersInnerH | imgui.TableFlags.BordersOuterV
        | imgui.TableFlags.BordersOuterH
    )
    if imgui.BeginTable("tab-id", COLS, flags):
        for x in range(ROWS):
            imgui.TableNextRow()
            for c in range(COLS):
                imgui.TableNextColumn()
                col = imgui.Vec4(
                    x / ROWS, c / COLS, 1 - (x + c) / (ROWS + COLS), 1.0
                )
                imgui.TextColored(
                    col,
                    f"({int(col.x * 255)}, {int(col.y * 255)}, {int(col.z * 255)})"
                )

        imgui.EndTable()


def plot(state: State):
    if imgui.RadioButton("Scatter", state.plotMode == 0):
        state.plotMode = 0
        implot.SetNextAxesToFit()
    if imgui.RadioButton("Heatmap", state.plotMode == 1):
        state.plotMode = 1
        implot.SetNextAxesToFit()

    implot.BeginPlot("data", imgui.Vec2(500, 500))
    if state.plotMode == 0:
        if time.perf_counter() - state.lastUpate > state.updatePeriod:
            state.plotY[state.plotIdx
                        ] = random.triangular(state.plotMin, state.plotMax)
            state.plotIdx = (state.plotIdx + 1) % state.plotSize
            state.lastUpate = time.perf_counter()
        implot.PlotScatter("DATA", state.plotX, state.plotY)
    elif state.plotMode == 1:
        size = 10
        if time.perf_counter() - state.lastUpate > state.updatePeriod:
            state.plotY[state.plotIdx] += random.triangular(-1, 1)
            state.plotIdx = (state.plotIdx + 1) % (size * size)
            state.lastUpate = time.perf_counter()
        implot.PlotHeatmap(
            "DATA", state.plotY, size, size, state.plotMin, state.plotMax
        )
    implot.EndPlot()


def showAll(state: State):
    if imgui.Begin("Widgets"):
        normWidgets(state)
        imgui.End()

    if imgui.Begin("Tables"):
        tables()
        imgui.End()

    if imgui.Begin("Plot"):
        plot(state)
        imgui.End()


def main():
    print("Init GLFW")
    window = glfw.Init(window_width=800, window_height=600, title="Test")

    if window is None:
        print("Error during GLFW init")
        exit(1)

    print("Create ImGUI Context")
    imgui.CreateContext()
    print("Create ImPlot Context")
    implot.CreateContext()
    print("Init Context for GLFW")
    glfw.InitContextForGLFW(window)
    print("Set Style Colors")
    imgui.StyleColorsDark()

    print("Making Clear Color")
    clearColor = imgui.Vec4(0.45, 0.55, 0.6, 1.0)

    state = State()

    print("Starting Loop")
    while True:
        # print("GLFW NewFrame")
        glfw.NewFrame()
        # print("ImGUI NewFrame")
        imgui.NewFrame()
        # print("ShowDemo")
        showAll(state)
        # print("ImGUI Render")
        imgui.Render()
        # print("GLFW Render")
        glfw.Render(window, clearColor)

        # print("Check Close")
        if glfw.ShouldClose(window):
            break

    print("Destroying ImPlot Context")
    implot.DestroyContext()
    print("Destroying ImGui Context")
    imgui.DestroyContext()

    print("Shutting down")
    glfw.Shutdown(window)


if __name__ == '__main__':
    main()
