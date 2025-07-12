#!/bin/bash

SRC_ROOT=`dirname $0`
SRC_ROOT=`realpath $SRC_ROOT/..`

ENGINE=podman
type $ENGINE > /dev/null 2>&1 || ENGINE=docker

MISC_ARGS="-ti --rm"

CONTAINER="imgui_build:1"

if [[ -z "$@" ]]
then
    COMMAND="/bin/bash"
else
    COMMAND=$@
fi

echo "Starting Build Container $CONTAINER"

_UID=`id -u`
_GID=`id -g`

$ENGINE run \
    $MISC_ARGS \
    --volume $SRC_ROOT:/src:z \
    --workdir /src \
    --userns=keep-id \
    --env IN_DOCKER=1 \
    --user $_UID:$_GID \
    $CONTAINER \
    $COMMAND
