#!/bin/bash
# Enable exit on error
set -e

export PY_ROOT="/opt/python/${1}/bin"

export PATH=${PY_ROOT}:${PATH}

cd /src
echo "Clearing Build Directory"
rm -rf build
echo "Clearing Dist Directory"
rm -rf dist
echo "Using python $(which python)"
python -m build --wheel
echo "Auditing"
auditwheel repair dist/*.whl