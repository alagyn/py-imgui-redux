#!/bin/bash
# Enable exit on error

scriptDir=$(realpath $(dirname $0))

if [[ "$IN_DOCKER" = "" ]]
then
    cd $scriptDir
    pwd
    ./start.sh /src/docker/build-version.sh  $@
    exit
fi

set -e

PY_VERSION=

while getopts "p:n" arg
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

export PY_ROOT="/opt/python/${PY_VERSION}/bin"
export PATH=${PY_ROOT}:${PATH}

cd /src

# clear dist so we don't have to care about the wheel name below
rm -rf dist 

echo "Using python $(which python)"
python -m build --wheel
echo "Auditing"
auditwheel repair dist/*.whl