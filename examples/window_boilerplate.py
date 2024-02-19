"""
Example boilerplate for a setting up/shutting down the ImGui context and
GLFW window correctly, as well as a basic render loop
"""
from typing import Callable

import imgui as im
import imgui.glfw as glfw
import imgui.implot as implot

# Define a DrawFunc as a callable that takes no arguments and returns a bool
DrawFunc = Callable[[], bool]


def window_mainloop(title: str, width: int, height: int, draw: DrawFunc):
    """
    Create a single window and enter render loop until either the window is closed
    or the draw() func returns true
    """

    # 1) create our window
    window = glfw.Init(title, width, height)
    if window is None:
        # GLFW should have hopefully logged an error as well
        raise RuntimeError("Could not create GLFW Window")

    # 2) Create context
    im.CreateContext()
    # optionally create extension contexts
    implot.CreateContext()

    # 3) Initialize glfw backend
    glfw.InitContextForGLFW(window)

    # 4) Setup style
    im.StyleColorsDark()
    # Set background OpenGL "clear color"
    clear_color = im.Vec4(0.22, 0.22, 0.22, 1.0)

    # 5) Main Loop
    while True:
        # pre-frame init
        glfw.NewFrame()
        im.NewFrame()

        # Do GUI processing
        shouldExit = draw()

        # Render the frame
        im.Render()
        glfw.Render(window, clear_color)

        # if the draw func says we should exit, or the user clicked the close button
        if shouldExit or glfw.ShouldClose(window):
            break

    # 6) Shutdown window
    # Do this first, else there will usually be a segfault
    glfw.Shutdown(window)

    # 7) Destroy Contexts
    # in reverse order, destroy extensions first
    implot.DestroyContext()
    im.DestroyContext()

    # Done


if __name__ == '__main__':

    def showDemo():
        im.ShowDemoWindow()
        return False

    window_mainloop("Demo", 860, 640, showDemo)
