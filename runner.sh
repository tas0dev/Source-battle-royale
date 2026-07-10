#!/bin/bash

./src/buildallprojects

./game/mod_hl2mp_linux64 \
    -dev \
    -console \
    -windowed \
    -w 1280 \
    -h 720 \
    +map dm_lockdown