#!/bin/bash
# Enable exit on error
set -e

export PY_ROOT="/opt/python/${1}/bin"

export PATH=${PY_ROOT}:${PATH}

CLEAN=1

while getopts "n" arg
do
    case $arg in
        n) CLEAN=0 ;;
    esac
done

cd /src
if [ CLEAN = 1 ]
then
    echo "Clearing Build Directory"
    rm -rf build
    echo "Clearing Dist Directory"
    rm -rf dist
fi

echo "Using python $(which python)"
python -m build --wheel
echo "Auditing"
auditwheel repair dist/*.whl