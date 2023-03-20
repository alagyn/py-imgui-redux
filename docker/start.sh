#!/bin/bash

SRC_ROOT=`dirname $0`
SRC_ROOT=`realpath $SRC_ROOT/..`

MISC_ARGS="-ti --rm"

CONTAINER="imgui_build:1"

if [[ -z "$@" ]]
then
    COMMAND="/bin/bash"
else
    COMMAND=$@
fi

docker run \
    $MISC_ARGS \
    -v $SRC_ROOT:/src \
    -w /src \
    $CONTAINER \
    $COMMAND
