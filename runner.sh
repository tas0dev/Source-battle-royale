#!/bin/bash

./src/buildallprojects

if [ $? -ne 0 ]; then
    echo "Build failed"
    exit 1
fi
./game/mod_hl2mp_linux64 \
    -dev \
    -console \
    -windowed \
    -w 1280 \
    -h 720 \
    +map dm_lockdown