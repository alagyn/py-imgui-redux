"""
Example boilerplate for a setting up/shutting down the ImGui context and
GLFW window correctly, as well as a basic render loop
"""
from typing import Callable, Optional
import os

import imgui as im
from imgui import glfw, imnodes, implot

# Define a DrawFunc as a callable that takes no arguments and returns a bool
DrawFunc = Callable[[], bool]


def errorCallback(err: int, msg: str) -> None:
    print(f'GLFW Error Code: {err}, Msg: {msg}')


def cursorPosCallback(window, xpos, ypos):
    print("GLFW callback", xpos, ypos)


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
    or the draw() func returns true.
    init is called once, after imgui is initialized.
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
    glslVersion = "#version 130"

    # MacOS example settings:
    # glfw.WindowHint(glfw.CONTEXT_VERSION_MAJOR, 3)
    # glfw.WindowHint(glfw.CONTEXT_VERSION_MINOR, 2)
    # glfw.WindowHint(glfw.OPENGL_PROFILE, glfw.OPENGL_CORE_PROFILE)
    # glfw.WindowHint(glfw.OPENGL_FORWARD_COMPAT, 1)
    # glfw.WindowHint(glfw.COCOA_GRAPHICS_SWITCHING, 1)
    # glslVersion = "#version 150"

    window = glfw.CreateWindow(width, height, title)
    if window is None:
        print("Cannot create GLFW window")
        return

    # Example callback
    # glfw.SetCursorPosCallback(window, cursorPosCallback)

    glfw.MakeContextCurrent(window)
    # enable vsync
    glfw.SwapInterval(1)

    # Set window icon
    # Get a path to our image
    imageFile = os.path.join(
        os.path.split(__file__)[0], "..", "docs", "pyimgui-logo-512.png"
    )
    # Can also load image bytes via the methods in the image example openCV/PILLOW/etc.
    # Byte data must be RGBA
    icon = glfw.Image(imageFile)
    glfw.SetWindowIcon(window, [icon])

    # Create ImGui context
    im.CreateContext()
    # optionally create extension contexts
    implot.CreateContext()
    imnodes.CreateContext()

    # Initialize glfw backend
    im.InitContextForGLFW(window, glslVersion)

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
    imnodes.DestroyContext()
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

    window_mainloop("Demo", 1024, 768, showDemo)
