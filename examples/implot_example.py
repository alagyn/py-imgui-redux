"""
Basic example of implot usage.
See the ImPlot docs for more info.
"""

import sys
import os
import time
import random

import numpy as np

import imgui.implot as implot
import imgui

# Add this file's dir to the path just in case we can't find the other files
sys.path.append(os.path.split(__file__)[0])
# Import the boilerplate loop from "window_boilerplate.py"
from window_boilerplate import window_mainloop


class State:

    def __init__(self) -> None:
        self.plotMode = 0

        self.plotSize = 1000
        self.plotMin = 0
        self.plotMax = 10
        self.plotX = np.arange(self.plotSize, dtype=np.float64)
        self.plotY = np.array(
            np.random.rand(self.plotSize) * self.plotMax, dtype=np.float64
        )
        self.plotIdx = 0

        self.lastUpate = time.perf_counter()
        self.updatePeriod = 0.5

    def render(self):
        if imgui.Begin("Plot"):
            if imgui.RadioButton("Scatter", self.plotMode == 0):
                self.plotMode = 0
                implot.SetNextAxesToFit()
            if imgui.RadioButton("Heatmap", self.plotMode == 1):
                self.plotMode = 1
                implot.SetNextAxesToFit()

            if implot.BeginPlot("data", imgui.Vec2(500, 500)):
                if self.plotMode == 0:
                    if time.perf_counter(
                    ) - self.lastUpate > self.updatePeriod:
                        self.plotY[self.plotIdx] = random.triangular(
                            self.plotMin, self.plotMax
                        )
                        self.plotIdx = (self.plotIdx + 1) % self.plotSize
                        self.lastUpate = time.perf_counter()
                    implot.PlotScatter("DATA", self.plotX, self.plotY)
                elif self.plotMode == 1:
                    size = 10
                    if time.perf_counter(
                    ) - self.lastUpate > self.updatePeriod:
                        self.plotY[self.plotIdx] += random.triangular(-1, 1)
                        self.plotIdx = (self.plotIdx + 1) % (size * size)
                        self.lastUpate = time.perf_counter()
                    implot.PlotHeatmap(
                        "DATA",
                        self.plotY,
                        size,
                        size,
                        self.plotMin,
                        self.plotMax
                    )
                implot.EndPlot()
        imgui.End()


if __name__ == '__main__':
    state = State()
    window_mainloop("Plotting", 1024, 640, state.render)
