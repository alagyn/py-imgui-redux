#!/bin/bash
# Enable exit on error
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

echo "Using python $(which python)"
python -m build --wheel
echo "Auditing"
auditwheel repair dist/*.whl