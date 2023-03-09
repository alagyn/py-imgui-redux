from pybind11_stubgen import ModuleStubsGenerator
import sys

sys.path.append("../build/bind-imgui/Release")

import imgui

module = ModuleStubsGenerator(imgui)
module.parse()
module.write_setup_py = False

with open("imgui.pyi", mode='w') as f:
    f.write("\n".join(module.to_lines()))