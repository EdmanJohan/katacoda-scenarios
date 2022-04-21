#!/bin/bash

echo "Hello from background script"
echo "Install apt packages"
sudo apt install llvm
sudo apt install clang
sudo apt install python3
sudo apt install python3-pip
sudo apt install git gcc-arm-none-eabi make gcc-multilib openocd gdb-multiarch doxygen wget unzip python3-serial
pip3 install pyelftools


echo "Clone Git repository"
git clone https://github.com/future-proof-iot/Femto-Container_tutorials.git
cd Femto-Container_tutorials
git submodule init
git submodule update
