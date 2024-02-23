"""
Example of how to load and use images and textures
in a couple different methods
"""

import sys
import os

# Add this file's dir to the path just in case we can't find the other files
sys.path.append(os.path.split(__file__)[0])

# Import the boilerplate loop from "window_boilerplate.py"
from window_boilerplate import window_mainloop

import imgui as im

# These are optional methods to laod images
# useful if you want to do some image manipulation
import cv2
from PIL import Image


class State:

    def __init__(self) -> None:
        # Get a path to our image
        imageFile = os.path.join(
            os.path.split(__file__), "..", "docs", "py-imgui-logo.png"
        )

        # METHOD 1
        # Load via built in image file parsing
        # see the README for more info
        tex1 = im.LoadTextureFile(imageFile)

        # METHOD 2
        # Load via OpenCV
        image = cv2.imread(imageFile, cv2.IMREAD_UNCHANGED)
        # Might need to convert the colors here
        image = cv2.cvtColor(image, cv2.COLOR_BGRA2RGBA)
        # Pass the data to imgui
        tex2 = im.LoadTexture(
            image.tobytes(), image.shape[1], image.shape[0], image.shape[2]
        )

        # METHOD 3
        # Load via PILLOW
        image2 = Image.open(imageFile)
        # Pass the data to imgui
        tex3 = im.LoadTexture(
            image2.tobytes(),
            image2.size[0],
            image2.size[1],
            len(image2.getbands())
        )

        # we no longer need the image data once loaded in a texture
        self.textures = [("built-in", tex1), ("openCV", tex2), ("PIL", tex3)]
        # rendered image size
        self.imSize = im.Vec2(200, 200)

    def render(self):
        im.SetNextWindowSize(im.Vec2(480, 300))
        if im.Begin("Window"):
            if im.BeginTable("_im", len(self.textures)):
                for label, _ in self.textures:
                    im.TableNextColumn()
                    im.Text(label)

                im.TableNextRow()
                for _, texture in self.textures:
                    im.TableNextColumn()
                    # create image object
                    im.Image(texture.texID, self.imSize)

                im.EndTable()
        im.End()

    def cleanup(self):
        for _, tex in self.textures:
            # unload all our textures to be nice :)
            im.UnloadTexture(tex.texID)


if __name__ == '__main__':
    state = State()
    window_mainloop("Images", 1024, 768, state.render, state.cleanup)
