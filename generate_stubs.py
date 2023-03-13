import sys
import subprocess
import os

if __name__ == '__main__':
    # Add the binary dir to the path
    # TODO make this work for Win too
    BUILD_DIR = "build/lib.linux-x86_64-cpython-310"
    sys.path.append(BUILD_DIR)
    # Try to import it
    try:
        import imgui  # type: ignore
    except ModuleNotFoundError:
        print("Cannot find built package")
        exit(1)

    curdir = os.path.abspath(os.curdir)
    out = os.path.join(curdir, "stubs")

    print("Writing stubs to", out)

    subprocess.check_call(
        [
            sys.executable,
            "-m",
            "pybind11_stubgen",
            "--no-setup-py",
            "--log-level=DEBUG",
            "--ignore-invalid=defaultarg",
            "-o",
            out,
            "imgui"
        ],
        cwd=BUILD_DIR
    )
