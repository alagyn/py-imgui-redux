#!/bin/bash

home=`dirname $0 | xargs realpath`

PY_VERSIONS="cp37-cp37m cp38-cp38 cp39-cp39 cp310-cp310 cp311-cp311"


for ver in $PY_VERSIONS
do
    echo "Building $ver"
    $home/docker/start.sh /src/docker/build-version.sh $ver
done

echo "Done"