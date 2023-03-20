#!/bin/bash

VERSION=1

home=`dirname $0`

docker build -t imgui_build:$VERSION $home