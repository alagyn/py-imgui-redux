"""
Example boilerplate for a setting up/shutting down the ImGui context and
GLFW window correctly, as well as a basic render loop
"""
from typing import Callable, Optional

import glfw  # import this first so that the libs are loaded correctly

import imgui as im
import imgui.implot as implot

# Define a DrawFunc as a callable that takes no arguments and returns a bool
DrawFunc = Callable[[], bool]


def errorCallback(err: int, msg: str) -> None:
    print(f'GLFW Error Code: {err}, Msg: {msg}')


def window_mainloop(
    title: str,
    width: int,
    height: int,
    draw: DrawFunc,
    init: Optional[Callable[[], None]] = None,
    cleanup: Optional[Callable[[], None]] = None
):
    """
    Create a single window and enter render loop until either the window is closed
    or the draw() func returns true
    init is called once, after imgui is initialized
    cleanup func is called once before imgui contexts are destroyed
    """

    # set error callback func
    glfw.SetErrorCallback(errorCallback)
    if not glfw.Init():
        print("Cannot initialize GLFW")
        return

    # create our window
    glfw.WindowHint(glfw.CONTEXT_VERSION_MAJOR, 4)
    glfw.WindowHint(glfw.CONTEXT_VERSION_MINOR, 6)
    window = glfw.CreateWindow(width, height, title, None, None)
    if window is None:
        print("Cannot create GLFW window")
        return

    glfw.MakeContextCurrent(window)
    # enable vsync
    glfw.SwapInterval(1)

    # Create ImGui context
    im.CreateContext()
    # optionally create extension contexts
    implot.CreateContext()

    print(dir(window))

    # Initialize glfw backend
    im.InitContextForGLFW(window, "#version 130")

    # 4) Setup style
    im.StyleColorsDark()
    # Set background OpenGL "clear color"
    clear_color = im.Vec4(0.22, 0.22, 0.22, 1.0)

    # do any init tasks
    if init is not None:
        init()

    # 5) Main Loop
    while True:
        # pre-frame init
        glfw.PollEvents()
        im.NewFrame()

        # Do GUI processing
        shouldExit = draw()

        # Render the frame
        im.Render(window, clear_color)
        glfw.SwapBuffers(window)

        # if the draw func says we should exit, or the user clicked the close button
        if shouldExit or glfw.WindowShouldClose(window):
            break

    # do any cleanup tasks
    if cleanup is not None:
        cleanup()

    # Shutdown window
    # Do this first, else there will usually be a segfault
    glfw.DestroyWindow(window)
    im.Shutdown()

    # Destroy Contexts
    # in reverse order, destroy extensions first
    implot.DestroyContext()
    im.DestroyContext()

    # terminate glfw
    glfw.Terminate()

    # Done


if __name__ == '__main__':

    def showDemo():
        im.ShowDemoWindow()
        implot.ShowDemoWindow()
        return False

    window_mainloop("Demo", 860, 640, showDemo)
