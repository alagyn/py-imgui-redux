import sys
sys.path.append("../build/bind-imgui/Release")

import imgui  # type: ignore
import imgui.glfw as glfw  # type: ignore
import imgui.implot as implot  # type: ignore

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
print("Create ImPlot Context")
implot.CreateContext()

print("Making Clear Color")
clearColor = imgui.Vec4(0.45, 0.55, 0.6, 1.0)

print("Starting Loop")
while True:
    # print("GLFW NewFrame")
    glfw.NewFrame()
    # print("ImGUI NewFrame")
    imgui.NewFrame()
    # print("ShowDemo")
    implot.ShowDemoWindow()
    # print("ImGUI Render")
    imgui.Render()
    # print("GLFW Render")
    glfw.Render(window, clearColor)

    # print("Check Close")
    if glfw.ShouldClose(window):
        break

print("Shutting down")
glfw.Shutdown(window)
