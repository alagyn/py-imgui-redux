import sys
# sys.path.append("../build/bind-imgui/Release")

import time

import imgui  # type: ignore
import imgui.glfw as glfw  # type: ignore


class State:
    def __init__(self) -> None:
        self.cb1 = False
        self.radio = -1
        self.progress = 0.0
        self.progressTime = time.perf_counter()
        self.comboVal = "Select Me"
        self.listboxVal = [False, False]

        self.fltVal1 = 0.0
        self.fltVal2 = 0.0
        self.fltVal3 = 0.0
        self.fltVal4 = 0.0

        self.intVal1 = 0
        self.intVal2 = 0
        self.intVal3 = 0
        self.intVal4 = 0


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
        _, state.intVal1 = imgui.DragInt("int 1", state.intVal1)

        x = (state.intVal1, state.intVal2)
        edit, x = imgui.DragInt2("int 2", x)
        if edit:
            state.intVal1 = x[0]
            state.intVal2 = x[1]

        x = (state.intVal1, state.intVal2, state.intVal3)
        edit, x = imgui.DragInt3("int 3", x)
        if edit:
            state.intVal1 = x[0]
            state.intVal2 = x[1]
            state.intVal3 = x[2]

        x = (state.intVal1, state.intVal2, state.intVal3, state.intVal4)
        edit, x = imgui.DragInt4("int 4", x)
        if edit:
            state.intVal1 = x[0]
            state.intVal2 = x[1]
            state.intVal3 = x[2]
            state.intVal4 = x[3]

        _, state.intVal1, state.intVal2 = imgui.DragIntRange2(
            "int range 2",
            state.intVal1, state.intVal2
        )

        imgui.Dummy(imgui.Vec2(10, 30))

        # float drags
        _, state.fltVal1 = imgui.DragFloat("flt 1", state.fltVal1)

        edit, x = imgui.DragFloat2("flt 2", (state.fltVal1, state.fltVal2))
        if edit:
            state.fltVal1 = x[0]
            state.fltVal2 = x[1]

        edit, x = imgui.DragFloat3(
            "flt 3", (state.fltVal1, state.fltVal2, state.fltVal3))
        if edit:
            state.fltVal1 = x[0]
            state.fltVal2 = x[1]
            state.fltVal3 = x[2]

        edit, x = imgui.DragFloat4(
            "flt 4", (state.fltVal1, state.fltVal2, state.fltVal3, state.fltVal4))
        if edit:
            state.fltVal1 = x[0]
            state.fltVal2 = x[1]
            state.fltVal3 = x[2]
            state.fltVal4 = x[3]

        _, state.fltVal1, state.fltVal2 = imgui.DragFloatRange2(
            "flt range 2", state.fltVal1, state.fltVal2
        )

        imgui.EndTable()


def tables():
    COLS = 3
    ROWS = 10
    flags = (
        imgui.TableFlags.BordersInnerH |
        imgui.TableFlags.BordersOuterV |
        imgui.TableFlags.BordersOuterH
    )
    if imgui.BeginTable("tab-id", COLS, flags):
        for x in range(ROWS):
            imgui.TableNextRow()
            for c in range(COLS):
                imgui.TableNextColumn()
                col = imgui.Vec4(x / ROWS, c / COLS, 1 - (x + c) / (ROWS + COLS), 1.0)
                imgui.TextColored(
                    col, f"({int(col.x * 255)}, {int(col.y * 255)}, {int(col.z * 255)})")

        imgui.EndTable()


def showAll(state: State):
    if imgui.Begin("Widgets", False)[0]:
        normWidgets(state)
        imgui.End()

    if imgui.Begin("Tables", False)[0]:
        tables()
        imgui.End()


def main():
    print("Init GLFW")
    window = glfw.Init(window_width=800, window_height=600, title="Test")

    if window is None:
        print("Error during GLFW init")
        exit(1)

    print("Create ImGUI Context")
    imgui.CreateContext()
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

    print("Shutting down")
    glfw.Shutdown(window)


if __name__ == '__main__':
    main()
