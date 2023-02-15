import sys
sys.path.append("../build/bind-imgui/Release")

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


def showAll(state: State):
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
    elif imgui.RadioButton("Radio1", state.radio == 1):
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

    imgui.Text("Hover Me")
    if imgui.IsItemHovered():
        imgui.BeginTooltip()
        imgui.Text("This is a tooltip")
        imgui.EndTooltip()


def main():
    print("Init GLFW")
    window = glfw.Init(window_width=500, window_height=500, title="Test")

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
        if imgui.Begin("Window", False)[0]:
            showAll(state)
            imgui.End()
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
