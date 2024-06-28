#!/bin/bash

# build every wheel we distribute.
# works on linux and windows gitbash/ming

home=$(realpath $(dirname $0)/..)

PY_VERSIONS="3.7 3.8 3.9 3.10 3.11 3.12"

cd $home

# Check if we are on windows
IS_WINDOWS=0
case "$(uname -s)" in
    MINGW*) IS_WINDOWS=1
esac

for ver in $PY_VERSIONS
do
    echo "Building $ver"
    if [[ $IS_WINDOWS = 0 ]]
    then
        ./scripts/build-version.sh -p $ver
    else
        ./scripts/build-version-win.sh -p $ver
    fi
    error=$?
    if [ $error -ne 0 ]
    then
        echo Build exited with error $error
        exit 1
    fi
done

echo "Done"