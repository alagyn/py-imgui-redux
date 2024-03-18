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

PY_EXEC=/opt/python/${PY_VERSION}/bin/python
#export PY_ROOT="/opt/python/${PY_VERSION}/bin"
#export PATH=${PY_ROOT}:${PATH}

cd /src
if [ $CLEAN -eq 1 ]
then
    echo "Clearing Build Directory"
    rm -rf build
    mkdir build
    echo "Clearing Dist Directory"
    rm -rf dist
fi

echo "Using python $PY_EXEC"
$PY_EXEC -m venv build/build-venv
build/build-venv/bin/python -m pip install cmake build wheel py-glfw-redux 
build/build-venv/bin/python -m build --wheel -n
echo "Auditing"

GLFW_LIB_ABS=`ls build/build-venv/lib/python*/site-packages/py_glfw_redux.libs/libglfw*.so.*`
GLFW_LIB=`basename $GLFW_LIB_ABS`
auditwheel repair dist/*.whl --exclude $GLFW_LIB