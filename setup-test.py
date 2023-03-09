import os
import subprocess
import sys
import platform
import glob

from setuptools import Extension, find_packages, setup
from setuptools.command.build_ext import build_ext
from pybind11_stubgen import ModuleStubsGenerator

BUILD_DIR = "build/bind-imgui/Release"
sys.path.append(BUILD_DIR)
import imgui
module = ModuleStubsGenerator(imgui)
module.parse()
module.write_setup_py = False

with open(os.path.join(BUILD_DIR, "imgui.pyi"), mode='w') as f:
    f.write("\n".join(module.to_lines()))

files = []

if platform.system() == "Windows":
    fileglob = glob.glob(os.path.join(BUILD_DIR, "*.pyd"))
else:
    fileglob = glob.glob(os.path.join(BUILD_DIR, "*.so"))

files.extend(fileglob)
files.extend(glob.glob(os.path.join(BUILD_DIR, "*.pyi")))

try:
    from wheel.bdist_wheel import bdist_wheel as _bdist_wheel

    class bdist_wheel(_bdist_wheel):
        def finalize_options(self):
            _bdist_wheel.finalize_options(self)
            self.root_is_pure = False
except ImportError:
    bdist_wheel = None


setup(
    packages=['imgui'],
    package_dir={"imgui": BUILD_DIR},
    data_files=[("", files)],
)
