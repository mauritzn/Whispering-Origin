#!/bin/bash

clear
printf ">> Updating apt... <<\n"
sudo apt-get update
clear

printf ">> Installing SDL2... <<\n"
sudo apt-get install libsdl2-dev

printf "\n\n>> Installing SDL2 Extension for TTF Fonts... <<\n"
sudo apt-get install libsdl2-ttf-dev

printf "\n\n>> Installing SDL2 Extension for JPG & PNG images... <<\n"
sudo apt-get install libsdl2-image-dev
