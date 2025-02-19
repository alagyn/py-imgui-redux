#!/bin/bash
# build a specific python version on windows

# Enable exit on error
set -e

scriptDir=$(realpath $(dirname $0))

# use var if defined, else set default python root
# define PY_ROOT externally to override
_DEF_PY_ROOT=/c/Python/bin/Python-
PY_ROOT=${PY_ROOT:-$_DEF_PY_ROOT}

PY_VERSION=

# Parse args
while getopts "p:" arg
do
    case $arg in
        p) PY_VERSION=$OPTARG ;;
    esac
done

if [ "$PY_VERSION" = "" ]
then
    echo "Please supply a python version with -p"
    exit 1
fi


PY_PATH=

case $PY_VERSION in
    3.7) PY_PATH=3.7.16 ;;
    3.8) PY_PATH=3.8.16 ;;
    3.9) PY_PATH=3.9.16 ;;
    3.10) PY_PATH=3.10.11 ;;
    3.11) PY_PATH=3.11.3 ;;
    3.12) PY_PATH=3.12.1 ;;
    3.13) PY_PATH=3.13.2 ;;
    *) 
    echo "Invalid python version (try 3.12)"
        exit 1
        ;;
esac

PY_EXEC=${PY_ROOT}${PY_PATH}/python.exe
echo "Using python ${PY_EXEC}"

$PY_EXEC -m build --wheel
