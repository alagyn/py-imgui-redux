#!/bin/bash

home=$(realpath $(dirname $0)/..)

PY_VERSIONS="cp37-cp37m cp38-cp38 cp39-cp39 cp310-cp310 cp311-cp311 cp312-cp312"

cd $home

for ver in $PY_VERSIONS
do
    echo "Building $ver"
    $home/docker/build-version.sh -p $ver
    error=$?
    if [ $error -ne 0 ]
    then
        echo Build exited with error $error
        exit 1
    fi
done

echo "Done"