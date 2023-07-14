#!/bin/bash

HOME=`dirname $0`

case `uname -s` in
    MINGW*)
        PY_EXEC=${HOME}/venv/Scripts/python
        ;;
    *) 
        PY_EXEC=${HOME}/venv/bin/python 
        ;;
esac

upload()
{
    ${PY_EXEC} -m twine upload -r imgui wheelhouse/*.whl
    exit $?
}

build()
{
    ${PY_EXEC} -m build --wheel
    ret=$?
    if [ $ret != 0 ]
    then
        exit $ret
    fi
    # No exit so we can do a build and upload
}

while getopts "ub" arg
do
    case $arg in
        u) 
            upload
            ;;
        b)
            build
            ;;
    esac
done

# Default
build

