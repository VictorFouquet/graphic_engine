#!/bin/bash
CURRENT_DIR=$(pwd)
if [ ! -d "${CURRENT_DIR}/build" ]
then
    mkdir build
fi
cd build
cmake ..
make
DRI_PRIME=1 ./GraphicEngine