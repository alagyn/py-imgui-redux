#!/bin/bash

home=`dirname $0`
home=`realpath $home`

cd docs
PYTHONPATH=${home}/build/lib.linux-x86_64-cpython-310/ make html