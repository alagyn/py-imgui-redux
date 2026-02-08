"""
Basic example of imnodes usage.
See the ImNodes docs for more info.
"""

import sys
import os
from typing import List, Tuple

# Add this file's dir to the path just in case we can't find the other files
sys.path.append(os.path.split(__file__)[0])
# Import the boilerplate loop from "window_boilerplate.py"
from window_boilerplate import window_mainloop

from imgui import imnodes
import imgui


class Node:

    def __init__(
        self, id: int, inputIDs: List[int], outputIDs: List[int]
    ) -> None:
        self.id = id
        self.inputIDs = inputIDs
        self.outputIDs = outputIDs

    def render(self):
        imnodes.BeginNode(self.id)
        imnodes.BeginNodeTitleBar()
        imgui.Text(f'Node {self.id}')
        imnodes.EndNodeTitleBar()

        for x in self.inputIDs:
            imnodes.BeginInputAttribute(x)
            imgui.Text(f"input {x}")
            imnodes.EndInputAttribute()

        for x in self.outputIDs:
            imnodes.BeginOutputAttribute(x)
            imgui.Text(f'output {x}')
            imnodes.EndOutputAttribute()

        imnodes.EndNode()


class State:

    def __init__(self) -> None:
        self.nodes: List[Node] = []
        self.links: List[Tuple[int, int]] = []

    def setup(self):
        # Define some nodes
        self.nodes = [
            Node(1, [], [1, 2]),
            Node(2, [3], [4]),
            Node(3, [5, 6], []),
        ]

        # define some links
        self.links = [(1, 3), (2, 6), (4, 5)]

        io = imnodes.GetIO()

        # User must hold shift to disconnect a link
        io.SetLinkDetachedWithModifierClick(imgui.ImKey.Mod_Shift)

        self.context1 = imnodes.EditorContextCreate()
        self.context2 = imnodes.EditorContextCreate()

    def render(self) -> bool:
        imgui.SetNextWindowSize(imgui.Vec2(600, 600), imgui.Cond.Once)
        if imgui.Begin("Nodes"):
            if imgui.BeginChild("editor_1", imgui.Vec2(0, 500)):
                imnodes.EditorContextSet(self.context1)
                imnodes.BeginNodeEditor()

                for n in self.nodes:
                    n.render()

                for idx, (idA, idB) in enumerate(self.links):
                    imnodes.Link(idx, idA, idB)

                imnodes.EndNodeEditor()

                start = imgui.IntRef()
                end = imgui.IntRef()
                if imnodes.IsLinkCreated(start, end):
                    self.links.append((start.val, end.val))

                linkID = imgui.IntRef()
                if imnodes.IsLinkDestroyed(linkID):
                    self.links.pop(linkID.val)
            imgui.EndChild()
            imgui.Separator()

            if imgui.BeginChild("editor_2", imgui.Vec2(0, 500)):
                imnodes.EditorContextSet(self.context2)

                imnodes.BeginNodeEditor()

                imnodes.BeginNode(4)
                imnodes.BeginNodeTitleBar()
                imgui.Text("Look at this")
                imnodes.EndNodeTitleBar()

                imgui.Text("My data here")
                imnodes.EndNode()

                imnodes.EndNodeEditor()
            imgui.EndChild()

        imgui.End()

        return False


if __name__ == '__main__':
    state = State()
    window_mainloop(
        "ImNodes Demo", 1024, 768, init=state.setup, draw=state.render
    )
