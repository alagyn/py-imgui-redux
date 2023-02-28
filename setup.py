import os
import re
import subprocess
import sys
from pathlib import Path

from setuptools import Extension, setup
from setuptools.command.build_ext import build_ext

# Convert distutils Windows platform specifiers to CMake -A arguments
PLAT_TO_CMAKE = {
    "win32": "Win32",
    "win-amd64": "x64",
    "win-arm32": "ARM",
    "win-arm64": "ARM64",
}

cmake_args = [
    f"-DCMAKE_BUILD_TYPE=RELEASE"
]

if sys.platform.startswith("darwin"):
    # Cross-compile support for macOS - respect ARCHFLAGS if set
    archs = re.findall(r"-arch (\S+)", os.environ.get("ARCHFLAGS", ""))
    if archs:
        cmake_args += ["-DCMAKE_OSX_ARCHITECTURES={}".format(";".join(archs))]

# Adding CMake arguments set as environment variable
# (needed e.g. to build for ARM OSx on conda-forge)
if "CMAKE_ARGS" in os.environ:
    cmake_args += [item for item in os.environ["CMAKE_ARGS"].split(" ") if item]


subprocess.run(
    ["cmake", "-S", ".", "-B", "build", *cmake_args], check=True
)


class CMakeExtension(Extension):
    def __init__(self, name: str, target: str) -> None:
        super().__init__(name, sources=[])
        self.target = target


class CMakeBuild(build_ext):
    def build_extension(self, ext: CMakeExtension) -> None:
        build_args = []

        # Set CMAKE_BUILD_PARALLEL_LEVEL to control the parallel build level
        # across all generators.
        if "CMAKE_BUILD_PARALLEL_LEVEL" not in os.environ:
            # self.parallel is a Python 3 only way to set parallel jobs by hand
            # using -j in the build_ext call, not supported by pip or PyPA-build.
            if hasattr(self, "parallel") and self.parallel:
                # CMake 3.12+ only.
                build_args += [f"-j{self.parallel}"]

        build_args += ["--target", ext.target]

        subprocess.run(
            ["cmake", "--build", "build", "--config=Release", *build_args], check=True
        )


# The information here can also be placed in setup.cfg - better separation of
# logic and declaration, and simpler if you include description/version in a file.
setup(
    ext_modules=[CMakeExtension("pyimgui-redux", "imgui")],
    cmdclass={"build_ext": CMakeBuild},
    zip_safe=False
)
