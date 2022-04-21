#!/bin/bash

sudo apt install -y llvm clang python3 python3-pip git gcc-arm-none-eabi make gcc-multilib openocd gdb-multiarch doxygen wget unzip python3-serial
pip3 install pyelftools

git clone https://github.com/future-proof-iot/Femto-Container_tutorials.git
cd Femto-Container_tutorials
git submodule init
git submodule update

echo "done" >> /opt/.backgroundfinished
