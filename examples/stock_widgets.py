"""
Example uses of the basic widgets and the Ref data types.
Uses most of the widgets.
"""

import sys
import os
import time

# Add this file's dir to the path just in case we can't find the other files
sys.path.append(os.path.split(__file__)[0])

# Import the boilerplate loop from "window_boilerplate.py"
from window_boilerplate import window_mainloop

import imgui


# Data holder for our UI state
class State:

    def __init__(self) -> None:
        self.cb1 = imgui.BoolRef(False)
        self.radio = imgui.IntRef(-1)
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

        self.color = imgui.Vec4(0.5, 0.1, 0.1, 1.0)

    def showAll(self):
        if imgui.Begin("Widgets"):
            normWidgets(self)
            imgui.End()

        if imgui.Begin("Tables"):
            tables()
            imgui.End()

        return False


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

        if imgui.CheckBox("Checkbox", state.cb1):
            print("Checkbox")
        # TODO checkbox flags
        if imgui.Button("Reset Radio"):
            state.radio.val = -1
        if imgui.RadioButton("Radio0", state.radio.val == 0):
            state.radio.val = 0
        # shorthand for the above if statement
        imgui.RadioButton("Radio1", state.radio, 1)

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

        if imgui.BeginPopupModal("nc-modal"):
            imgui.Selectable("ASDFASDF")
            imgui.EndPopup()

        if imgui.BeginPopupModal("c-modal", imgui.BoolRef(True)):
            imgui.SetWindowFocus()
            imgui.Selectable("ASDFASDF")
            imgui.Dummy(imgui.Vec2(10, 20))
            imgui.Text("Hover to close")
            if imgui.IsItemHovered():
                imgui.CloseCurrentPopup()
            imgui.EndPopup()

        if imgui.Button("Non-Closable Modal"):
            imgui.SetWindowFocus()
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

        imgui.ColorEdit4("Color Edit", state.color)


def tables():
    COLS = 3
    ROWS = 10
    flags = (imgui.TableFlags.BordersInnerH | imgui.TableFlags.BordersOuterV
             | imgui.TableFlags.BordersOuterH)
    if imgui.BeginTable("tab-id", COLS, flags):
        for x in range(ROWS):
            imgui.TableNextRow()
            for c in range(COLS):
                imgui.TableNextColumn()
                col = imgui.Vec4(x / ROWS, c / COLS,
                                 1 - (x + c) / (ROWS + COLS), 1.0)
                imgui.TextColored(
                    col,
                    f"({int(col.x * 255)}, {int(col.y * 255)}, {int(col.z * 255)})"
                )

        imgui.EndTable()


def main():
    state = State()
    window_mainloop("Basic Widgets", 1024, 680, state.showAll)


if __name__ == '__main__':
    main()
