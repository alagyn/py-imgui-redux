from distutils.command.install_data import install_data
from setuptools import find_packages, setup, Extension
from setuptools.command.build_ext import build_ext
from setuptools.command.install_lib import install_lib
from setuptools.command.install_scripts import install_scripts
import struct
import os
import shutil
import pathlib
import sys
import subprocess

BITS = struct.calcsize("P") * 8
SOURCE_DIR, _ = os.path.split(__file__)

IS_WINDOWS = sys.platform == "win32"


def log(msg: str):
    print(f"\x1b[1;33m{msg}\x1b[0m")


class CMakeExtension(Extension):
    """
    An extension to run the cmake build

    This simply overrides the base extension class so that setuptools
    doesn't try to build your sources for you
    """

    def __init__(self, name, sources=[]):
        super().__init__(name=name, sources=sources)


class InstallCMakeLibsData(install_data):
    """
    Just a wrapper to get the install data into the egg-info

    Listing the installed files in the egg-info guarantees that
    all of the package files will be uninstalled when the user
    uninstalls your package through pip
    """

    def run(self):
        """
        Outfiles are the libraries that were built using cmake
        """

        # There seems to be no other way to do this; I tried listing the
        # libraries during the execution of the InstallCMakeLibs.run() but
        # setuptools never tracked them, seems like setuptools wants to
        # track the libraries through package data more than anything...
        # help would be appriciated

        self.outfiles = self.distribution.data_files


class InstallCMakeLibs(install_lib):
    """
    Get the libraries from the parent distribution, use those as the outfiles

    Skip building anything; everything is already built, forward libraries to
    the installation step
    """

    def run(self):
        """
        Copy libraries from the bin directory and place them as appropriate
        """

        log("Moving library files")

        # We have already built the libraries in the previous build_ext step

        self.skip_build = True

        bin_dir = self.distribution.bin_dir

        # Depending on the files that are generated from your cmake
        # build chain, you may need to change the below code, such that
        # your files are moved to the appropriate location when the installation
        # is run

        FILE_TYPES = {".so", ".dll", ".pyd"}
        libs = []
        for file in os.listdir(bin_dir):
            # TODO parameterize?
            # Skip the non-renamed lib
            if file == "imgui.so" or file == "imgui.pyd":
                continue
            _, ext = os.path.splitext(file)
            if ext in FILE_TYPES:
                libs.append(os.path.join(bin_dir, file))

        log(f"Library files: {libs}")
        log(f"Destination: {self.build_dir}")
        """
        libs = [os.path.join(bin_dir, _lib) for _lib in 
                os.listdir(bin_dir) if 
                os.path.isfile(os.path.join(bin_dir, _lib)) and 
                os.path.splitext(_lib)[1] in [".dll", ".so"]
                and not (_lib.startswith("python") or _lib.startswith(PACKAGE_NAME))]
        """

        for lib in libs:
            shutil.copy(
                lib, os.path.join(self.build_dir, os.path.basename(lib))
            )

        log("Generating stubs")
        env = dict(os.environ)
        try:
            oldPath = env["PYTHONPATH"]
        except KeyError:
            oldPath = ""

        if IS_WINDOWS:
            oldPath += f";{self.build_dir}"
        else:
            oldPath += f":{self.build_dir}"

        env["PYTHONPATH"] = oldPath

        subprocess.check_call(
            [
                sys.executable,
                os.path.join(SOURCE_DIR, "pybind11_stubgen.py"),
                "--no-setup-py",
                "imgui"
            ],
            env=env,
            cwd=self.build_dir
        )

        stub_dir = os.path.join(self.build_dir, "imgui")
        if os.path.exists(stub_dir):
            shutil.rmtree(stub_dir)

        shutil.move(
            os.path.join(self.build_dir, "stubs/imgui-stubs"), stub_dir
        )
        # Mark the libs for installation, adding them to
        # distribution.data_files seems to ensure that setuptools' record
        # writer appends them to installed-files.txt in the package's egg-info
        #
        # Also tried adding the libraries to the distribution.libraries list,
        # but that never seemed to add them to the installed-files.txt in the
        # egg-info, and the online recommendation seems to be adding libraries
        # into eager_resources in the call to setup(), which I think puts them
        # in data_files anyways.
        #
        # What is the best way?

        # These are the additional installation files that should be
        # included in the package, but are resultant of the cmake build
        # step; depending on the files that are generated from your cmake
        # build chain, you may need to modify the below code

        self.distribution.data_files = [
            os.path.join(self.install_dir, os.path.basename(lib))
            for lib in libs
        ]

        # Must be forced to run after adding the libs to data_files

        self.distribution.run_command("install_data")

        super().run()


class InstallCMakeScripts(install_scripts):
    """
    Install the scripts in the build dir
    """

    def run(self):
        """
        Copy the required directory to the build directory and super().run()
        """

        log("Moving scripts files")

        # Scripts were already built in a previous step

        self.skip_build = True

        bin_dir = self.distribution.bin_dir
        # TODO? no scripts for now, and this is copying all the CMake directory which is bad
        scripts_dirs = []
        """
        scripts_dirs = [
            os.path.join(bin_dir, _dir) for _dir in os.listdir(bin_dir)
            if os.path.isdir(os.path.join(bin_dir, _dir))
        ]
        """

        log(f"Script dirs: {scripts_dirs}")
        log(f"Destination: {self.build_dir}")

        for scripts_dir in scripts_dirs:

            shutil.move(
                scripts_dir,
                os.path.join(self.build_dir, os.path.basename(scripts_dir))
            )

        # Mark the scripts for installation, adding them to
        # distribution.scripts seems to ensure that the setuptools' record
        # writer appends them to installed-files.txt in the package's egg-info

        self.distribution.scripts = scripts_dirs

        super().run()


class BuildCMakeExt(build_ext):
    """
    Builds using cmake instead of the python setuptools implicit build
    """

    def run(self):
        """
        Perform build_cmake before doing the 'normal' stuff
        """

        for extension in self.extensions:
            if isinstance(extension, CMakeExtension):
                self.build_cmake(extension)

        super().run()

    def build_cmake(self, extension: Extension):
        """
        The steps required to build the extension
        """

        log("Preparing the build environment")

        build_dir = pathlib.Path(self.build_temp)

        extension_path = pathlib.Path(self.get_ext_fullpath(extension.name))

        os.makedirs(build_dir, exist_ok=True)
        os.makedirs(extension_path.parent.absolute(), exist_ok=True)

        # Now that the necessary directories are created, build

        log("Configuring cmake project")

        PY_ROOT, _ = os.path.split(sys.executable)
        try:
            PY_ROOT = os.environ['PY_ROOT']
        except KeyError:
            pass
        log(f"Using Py Root: {PY_ROOT}")

        args = [
            "cmake",
            "-E",
            "env",
            "CMAKE_BUILD_PARALLEL_LEVEL=8",
            f"Python3_ROOT_DIR={PY_ROOT}"
            "--",
            'cmake',
            '-S',
            SOURCE_DIR,
            '-B',
            self.build_temp
        ]

        self.spawn(args)

        log("Building binaries")

        self.spawn(
            [
                "cmake",
                "-E",
                "env",
                "CMAKE_BUILD_PARALLEL_LEVEL=8",
                "--",
                "cmake",
                "--build",
                self.build_temp,
                "--target",
                extension.name,
                "--config",
                "Release"
            ]
        )

        # Build finished, now copy the files into the copy directory
        # The copy directory is the parent directory of the extension (.pyd)

        bin_dir = os.path.join(build_dir, "bind-imgui")

        if IS_WINDOWS:
            bin_dir = os.path.join(bin_dir, "Release")

        pyd_path = [
            os.path.join(bin_dir, _pyd) for _pyd in os.listdir(bin_dir)
            if os.path.isfile(os.path.join(bin_dir, _pyd))
            and os.path.splitext(_pyd)[0].startswith(extension.name)
            and os.path.splitext(_pyd)[1] in [".pyd", ".so"]
        ][0]

        self.distribution.bin_dir = bin_dir

        log("Moving built python module")
        shutil.copy(pyd_path, extension_path)

        # After build_ext is run, the following commands will run:
        #
        # install_lib
        # install_scripts
        #
        # These commands are subclassed above to avoid pitfalls that
        # setuptools tries to impose when installing these, as it usually
        # wants to build those libs and scripts as well or move them to a
        # different place. See comments above for additional information


# Most of this is pulled from pyproject.toml
setup(
    ext_modules=[CMakeExtension(name="imgui")],
    packages=[],
    cmdclass={
        'build_ext': BuildCMakeExt,
        'install_data': InstallCMakeLibsData,
        'install_lib': InstallCMakeLibs,
        'install_scripts': InstallCMakeScripts
    }
)
