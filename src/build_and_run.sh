#!/bin/bash

sh cleanup.sh

for i in {1..25}
do
	printf "\n\n\n\n\n\n\n\n\n\n"
done
clear

make
#printf "g++ main.o -L/usr/local/lib -lSDL2 -Wl,-rpath=/usr/local/lib -o SDL_testing"
printf "============================================================================\n\n"
./SDL_testing
