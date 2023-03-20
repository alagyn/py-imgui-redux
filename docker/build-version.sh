#!/bin/bash

PY_PATH="/opt/python/${1}/bin"

export PATH=${PY_PATH}:${PATH}

cd /src
rm -rf build
rm -rf dist
python -m build --wheel
auditwheel repair dist/*.whl