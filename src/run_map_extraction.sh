#!/bin/bash

#rm -rf extract_map_data
printf "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"

clear
g++ extract_map_data.cc -Wall -std=c++14 -lSDL2 -o extract_map_data
./extract_map_data

rm -rf ./extract_map_data
