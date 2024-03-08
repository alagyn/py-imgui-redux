#!/bin/bash
# Enable exit on error
set -e

CLEAN=1
PY_VERSION=

while getopts "p:n" arg
do
    case $arg in
        n) CLEAN=0 ;;
        p) PY_VERSION=$OPTARG ;;
    esac
done

if [ "$PY_VERSION" = "" ]
then
    echo "Please supply a python version with -p"
    exit 1
fi

export PY_ROOT="/opt/python/${PY_VERSION}/bin"
export PATH=${PY_ROOT}:${PATH}

cd /src
if [ $CLEAN -eq 1 ]
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