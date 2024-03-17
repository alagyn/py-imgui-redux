#!/bin/bash

home=`dirname $0`
home=`realpath $home`

libdir=build/lib.linux-x86_64-cpython-310
PYTHONPATH=${libdir} ${home}/venv/bin/python ${home}/pybind11_stubgen.py imgui --no-setup-py

if [ $? -ne 0 ]
then
    exit
fi

mkdir imgui
mv stubs/imgui-stubs/* imgui