import sys
import os

# Add this file's dir to the path just in case we can't find the other files
sys.path.append(os.path.split(__file__)[0])

# Import the boilerplate loop from "window_boilerplate.py"
from window_boilerplate import window_mainloop

import imgui as im

EXAMPLE_DIR = os.path.dirname(__file__)


class State:

    def __init__(self) -> None:
        self.font = None

    def setup(self):
        io = im.GetIO()

        self.font = io.Fonts.AddFontFromFileTTF(
            os.path.join(EXAMPLE_DIR, "fonts/RussoOne/RussoOne-Regular.ttf"),
            18.0
        )

        fontConfig = im.ImFontConfig()
        # Merge the icon font with the primary text font
        fontConfig.MergeMode = True
        # Load as many glyphs as possible
        glyphRanges = im.WCharList([0x1, 0xFFFF, 0])
        self.icons = io.Fonts.AddFontFromFileTTF(
            os.path.join(
                EXAMPLE_DIR,
                "fonts/NerdFontMonoSymbols/SymbolsNerdFontMono-Regular.ttf"
            ),
            18.0,
            fontConfig,
            glyphRanges
        )

        # Make sure to build the font atlas
        io.Fonts.Build()

    def render(self):
        if im.Begin("Window"):
            im.Text("Wooooow")
            im.Text("Look at that font")
            im.Text("This is an icon \ue61e and here is another \ueb1d")
        im.End()

        return False


if __name__ == '__main__':
    state = State()
    window_mainloop(
        "Images",
        1024,
        768,
        state.render,
        init=state.setup,
    )
