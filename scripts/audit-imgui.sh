#!/bin/bash

venvDir=$1
wheel=$2

LIBS=`ls $venvDir/lib/python*/site-packages/py_glfw_redux.libs/*.so*`

EXCLUDES=""
for x in $LIBS
do
    EXCLUDES+="--exclude $(basename $x) "
done

auditwheel repair $wheel $EXCLUDES