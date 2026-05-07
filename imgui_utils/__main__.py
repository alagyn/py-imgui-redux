import imgui
from imgui import implot
from imgui_utils import boilerplate

if __name__ == '__main__':

    def showDemo(dt: float):
        imgui.ShowDemoWindow()
        implot.ShowDemoWindow()
        return False

    boilerplate.window_mainloop("Demo", showDemo, 1024, 768, init_implot=True)
