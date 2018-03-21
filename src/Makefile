###############################
#
# Makefile for SDL Development
#
###############################

CC      = g++
CFLAGS  = -Wall -std=c++14
TARGET  = SDL_testing
SRC     = main.cc
HEADER  = window.h renderer.h images.h

# Linker flags
LFLAGS = -lSDL2 -lSDL2_ttf -lSDL2_image


all : $(TARGET)

$(TARGET) : $(SRC) $(HEADERS)
	$(CC) $(SRC) $(CFLAGS) $(LFLAGS) -o $(TARGET)

clean :
	rm $(TARGET)
