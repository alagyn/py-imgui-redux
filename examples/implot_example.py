"""
Basic example of implot usage.
See the ImPlot docs for more info.
"""

import time
import random

import numpy as np

# Import a basic main loop for a simple UI
# This is included with the library for you to use as well
from imgui_utils.boilerplate import window_mainloop

import imgui.implot as implot
import imgui
import math


def formatterCallback(val: float, buf: imgui.EditableStrWrapper, userData):
    label = f'{userData} {val}'
    buf.set(label)
    return 0


def dataGetter(idx: int, data) -> implot.Point:
    val = idx + 0.1 / math.pi
    return implot.Point(val, math.sin(val + data))


class State:

    def __init__(self) -> None:
        self.plotMode = 0

        self.plotSize = 100
        self.plotMin = 0
        self.plotMax = 10
        self.plotX = np.arange(self.plotSize, dtype=np.float64)
        self.plotY = np.array(
            np.random.rand(self.plotSize) * self.plotMax, dtype=np.float64
        )
        self.plotIdx = 0

        self.lastUpate = 0
        self.updatePeriod = 0.5
        self.t = 0

    def render(self, dt: float):
        self.lastUpate += dt
        if imgui.Begin("Plot"):
            if imgui.RadioButton("Scatter", self.plotMode == 0):
                self.plotMode = 0
                implot.SetNextAxesToFit()
            if imgui.RadioButton("Heatmap", self.plotMode == 1):
                self.plotMode = 1
                implot.SetNextAxesToFit()
            if imgui.RadioButton("Custom Getter", self.plotMode == 2):
                self.plotMode = 2
                implot.SetNextAxesToFit()

            if implot.BeginPlot("data", imgui.Vec2(500, 500)):
                if self.plotMode == 0:
                    # The return value from this has to exist until the PlotXXX function
                    # is called
                    formatterData = implot.SetupAxisFormat(
                        implot.Axis.X1, formatterCallback, "data"
                    )
                    if self.lastUpate > self.updatePeriod:
                        self.plotY[
                            self.plotIdx
                        ] = random.triangular(self.plotMin, self.plotMax)
                        self.plotIdx = (self.plotIdx + 1) % self.plotSize
                        self.lastUpate = 0

                    implot.PlotScatter("DATA", self.plotX, self.plotY)
                elif self.plotMode == 1:
                    size = 10
                    if self.lastUpate > self.updatePeriod:
                        self.plotY[self.plotIdx] += random.triangular(-1, 1)
                        self.plotIdx = (self.plotIdx + 1) % (size * size)
                        self.lastUpate = 0
                    implot.PlotHeatmap(
                        "DATA",
                        self.plotY,
                        size,
                        size,
                        self.plotMin,
                        self.plotMax
                    )
                elif self.plotMode == 2:
                    size = 200
                    self.t += dt * 0.1
                    implot.PlotScatterG("DATA", dataGetter, self.t, size)
                implot.EndPlot()
        imgui.End()

        return False


if __name__ == '__main__':
    state = State()
    window_mainloop("Plotting", state.render, 1024, 640, init_implot=True)
