#! /bin/zsh

cmake -B build
cmake --build build -j 4
build/Engine