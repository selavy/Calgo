#!/bin/bash

tar -xvzf boost_1_55_0.tar.gz
cd boost_1_55_0/tools/build/v2/
./bootstrap.sh
./b2 install --prefix=/tmp/Boost_Build
export PATH=$PATH:/tmp/Boost_Build/bin
cd ../../..
if [ $# -eq 1 ]
    then b2 --prefix=/tmp/build-boost --toolset=$1 stage
else
    b2 --prefix=/tmp/build-boost --toolset=gcc stage
fi
export LD_LIBRARY_PATH=./boost_1_55_0/stage/lib:$LD_LIBRARY_PATH
cd ..
make check_boost
./check_boost < jayne.txt