#!/bin/bash

#clear
#make

#rm -rf extract_map_data
printf "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"

clear
printf "Building..."
#g++ extract_map_data.cc -Wall -std=c++14 -lSDL2 -o extract_map_data
g++ extract_map_data.cc config.cc classes/functions.cc classes/fps.cc classes/image.cc classes/renderer.cc classes/text.cc classes/window.cc classes/player.cc classes/world.cc classes/tile.cc classes/progress_bar.cc classes/skill.cc classes/ui.cc classes/game.cc -Wall -std=c++14 -lSDL2 -lSDL2_ttf -lSDL2_image -o extract_map_data
clear

./extract_map_data

rm -rf ./extract_map_data