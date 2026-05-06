"""
A basic boilerplate function so you can get up and running fast
"""

from typing import Callable, Optional
import platform

import imgui as im
from imgui import glfw, imnodes, implot

# Define a DrawFunc as a callable that takes a single argument (delta_t) and returns a bool
DrawFunc = Callable[[float], bool]
# Define an InitFunc as a callable that takes no arguments and returns None
InitFunc = Callable[[], None]
# Define a CleanupFunc as a callable that takes no arguments and returns None
CleanupFunc = Callable[[], None]


def errorCallback(err: int, msg: str) -> None:
    print(f'GLFW Error Code: {err}, Msg: {msg}')


def window_mainloop(
    title: str,
    draw: DrawFunc,
    width: int = -1,
    height: int = -1,
    init: Optional[InitFunc] = None,
    cleanup: Optional[CleanupFunc] = None,
    init_imnodes: bool = False,
    init_implot: bool = False,
    opengl_ver_major=4,
    opengl_ver_minor=6,
    glsl_version="#version 130",
    clear_color=im.Vec4(0.22, 0.22, 0.22, 1.0),
    window_icon: Optional[str] = None
):
    """
    Create a single window and enter render loop until either the window is closed
    or the draw() func returns true.
    init is called once, after imgui is initialized.
    cleanup func is called once before imgui contexts are destroyed

    :param title: The window title
    :param draw: The main rendering function, window will exit when this returns true
    :param width: The starting window width, set to -1 to fill the screen
    :param height: The starting window height, set to -1 to fill the screen
    :param init: An initialization function, called once after imgui has been started
    :param cleanup: A cleanup function, called once before imgui shutsdown comepletely
    :param init_imnodes: Enable imnodes context
    :param init_implot: Enable implot context
    :param opengl_ver_major: The openGL major version
    :param opengl_ver_minor: The openGL minor version
    :param glsl_version: The GLSL version
    :param clear_color: The default background clear color
    :param window_icon: The path to an image to use as the window icon
    """

    # set error callback func
    glfw.SetErrorCallback(errorCallback)
    if not glfw.Init():
        print("Cannot initialize GLFW")
        return

    # create our window
    glfw.WindowHint(glfw.CONTEXT_VERSION_MAJOR, opengl_ver_major)
    glfw.WindowHint(glfw.CONTEXT_VERSION_MINOR, opengl_ver_minor)

    # MacOS settings:
    if platform.system() == "Darwin":
        glfw.WindowHint(glfw.OPENGL_PROFILE, glfw.OPENGL_CORE_PROFILE)
        glfw.WindowHint(glfw.OPENGL_FORWARD_COMPAT, 1)
        glfw.WindowHint(glfw.COCOA_GRAPHICS_SWITCHING, 1)

    if width <= 0 or height <= 0:
        width = 1024
        height = 768
        glfw.WindowHint(glfw.MAXIMIZED, 1)

    window = glfw.CreateWindow(width, height, title)
    if window is None:
        print("Cannot create GLFW window")
        return

    glfw.MakeContextCurrent(window)
    # enable vsync
    glfw.SwapInterval(1)

    # Set window icon
    if window_icon is not None:
        # Byte data must be RGBA
        icon = glfw.Image(window_icon)
        glfw.SetWindowIcon(window, [icon])

    # Create ImGui context
    im.CreateContext()
    # optionally create extension contexts
    if init_implot:
        implot.CreateContext()
    if init_imnodes:
        imnodes.CreateContext()

    # Initialize glfw backend
    im.InitContextForGLFW(window, glsl_version)

    # 4) Setup style
    im.StyleColorsDark()

    # do any init tasks
    if init is not None:
        init()

    prevTime = glfw.GetTime()

    # 5) Main Loop
    while True:
        # pre-frame init
        glfw.PollEvents()
        im.NewFrame()

        newTime = glfw.GetTime()
        # Do GUI processing
        shouldExit = draw(newTime - prevTime)
        prevTime = newTime

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
    if init_imnodes:
        imnodes.DestroyContext()
    if init_implot:
        implot.DestroyContext()

    im.DestroyContext()

    # terminate glfw
    glfw.Terminate()

    # Done
