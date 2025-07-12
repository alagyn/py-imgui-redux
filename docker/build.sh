#!/bin/bash

VERSION=1

home=`dirname $0`

ENGINE=podman
type $ENGINE > /dev/null 2>&1 || ENGINE=docker

$ENGINE build -t imgui_build:$VERSION $home