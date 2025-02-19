#!/bin/bash
# build a specific python version on linux

# Enable exit on error
set -e

scriptDir=$(realpath $(dirname $0))

# Make sure we are in the docker container
if [[ "$IN_DOCKER" = "" ]]
then
    # if not, start the docker container and run this script again
    cd $scriptDir/..
    ./docker/start.sh /src/scripts/build-version.sh $@
    exit
fi

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
    3.7) PY_PATH=cp37-cp37m ;;
    3.8) PY_PATH=cp38-cp38 ;;
    3.9) PY_PATH=cp39-cp39 ;;
    3.10) PY_PATH=cp310-cp310 ;;
    3.11) PY_PATH=cp311-cp311 ;;
    3.12) PY_PATH=cp312-cp312 ;;
    3.13) PY_PATH=cp313-cp313 ;;
    *) 
        echo "Invalid python version (try 3.12)"
        exit 1
        ;;
esac

# this is the path for the container's installs
export PY_ROOT="/opt/python/${PY_PATH}/bin"
export PATH=${PY_ROOT}:${PATH}

cd /src

# clear dist so we don't have to care about the wheel name below
rm -rf dist/*

echo "Using python $(which python)"
python -m build --wheel
echo "Auditing"
auditwheel repair dist/*.whl