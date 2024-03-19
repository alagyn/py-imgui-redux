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

cd /src
if [ $CLEAN -eq 1 ]
then
    echo "Clearing Build Directory"
    rm -rf build
    echo "Clearing Dist Directory"
    rm -rf dist
fi

echo "Using python $PY_EXEC"

# We are building outside an environment so that we can
# check the venv and find the name of the glfw lib and exclude it
# necessary because auditwheel appends a hash to the end of the libname

B_ENV=build/build-venv
B_PY=$B_ENV/bin/python

echo Creating virtual env in $B_ENV
$PY_EXEC -m venv $B_ENV
echo Retrieving build dependencies
$B_PY -m pip install tomli
DEPS=`$B_PY docker/getBuildDeps.py`
echo Installing build dependecies $DEPS
$B_PY -m pip install build $DEPS
echo Building wheel
$B_PY -m build --wheel -n
echo "Auditing"

GLFW_LIB_ABS=`ls build/build-venv/lib/python*/site-packages/py_glfw_redux.libs/libglfw*.so.*`
GLFW_LIB=`basename $GLFW_LIB_ABS`
auditwheel repair dist/*.whl --exclude $GLFW_LIB