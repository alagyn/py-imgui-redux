"""
Example of how to load and use images and textures
in a couple different methods
"""

import sys
import os
import numpy as np

# Add this file's dir to the path just in case we can't find the other files
sys.path.append(os.path.split(__file__)[0])

# Import the boilerplate loop from "window_boilerplate.py"
from window_boilerplate import window_mainloop

import imgui as im

# These are optional methods to laod images
# useful if you want to do some image manipulation
import cv2  # type: ignore
from PIL import Image  # type: ignore


# METHOD 1
# Load via built-in image file parsing
# see the README for more info
def loadSTB(filename: str) -> im.Texture:
    return im.LoadTextureFile(filename)


SIZE = 255


# METHOD 2
# Load via OpenCV
def loadOpenCV(filename: str) -> im.Texture:
    image = cv2.imread(filename, cv2.IMREAD_UNCHANGED)
    # Might need to convert the colors here
    image = cv2.cvtColor(image, cv2.COLOR_BGRA2RGBA)
    # Pass the data to imgui
    return im.LoadTexture(
        image.tobytes(), image.shape[1], image.shape[0], image.shape[2]
    )


# METHOD 3
# Load via PILLOW
def loadPILLOW(filename) -> im.Texture:
    print("Load PILLOW")
    image2 = Image.open(filename)
    # Pass the data to imgui
    return im.LoadTexture(
        image2.tobytes(),
        image2.size[0],
        image2.size[1],
        len(image2.getbands())
    )


class State:

    def __init__(self) -> None:
        self.textures = []
        # rendered image size
        self.imSize = im.Vec2(200, 200)

    def setup(self):
        # Get a path to our image
        imageFile = os.path.join(
            os.path.split(__file__)[0], "..", "docs", "pyimgui-logo-512.png"
        )

        # textures can only be loaded AFTER imgui and glfw has been intialized

        print("Load stb")
        tex1 = loadSTB(imageFile)
        print("Load OpenCV")
        tex2 = loadOpenCV(imageFile)
        print("Load PILLOW")
        tex3 = loadPILLOW(imageFile)
        # we no longer need the image data once loaded in a texture
        self.textures = [("built-in", tex1), ("openCV", tex2), ("PIL", tex3)]

    def render(self):
        im.SetNextWindowSize(im.Vec2(700, 300))
        if im.Begin("Window"):
            if im.BeginTable("_im", len(self.textures)):
                for label, _ in self.textures:
                    im.TableNextColumn()
                    im.Text(label)

                im.TableNextRow()
                for _, texture in self.textures:
                    im.TableNextColumn()
                    # create image object
                    im.Image(texture, self.imSize)

                im.EndTable()
        im.End()

        return False

    def cleanup(self):
        for _, tex in self.textures:
            # unload all our textures to be nice :)
            im.UnloadTexture(tex)


if __name__ == '__main__':
    state = State()
    window_mainloop(
        "Images",
        1024,
        768,
        state.render,
        init=state.setup,
        cleanup=state.cleanup
    )
