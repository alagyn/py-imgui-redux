#!/bin/bash

HOME=`dirname $0`

case `uname -s` in
    MINGW*)
        PY_EXEC=${HOME}/venv/Scripts/python 
        EXTRA_ARGS="-- /m"
        ;;
    *) 
        PY_EXEC=${HOME}/venv/bin/python 
        EXTRA_ARGS="-- -j4"
        ;;
esac

cmake -S $HOME -B ${HOME}/build
cmake --build ${HOME}/build --config Release ${EXTRA_ARGS}

${PY_EXEC} -m build --wheel

