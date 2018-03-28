###############################
#
# Makefile for SDL Development
#
###############################

CC      = g++
CFLAGS  = -Wall -std=c++14
TARGET  = Whispering\ Origin
SRC     = main.cc config.cc classes/fps.cc classes/images.cc classes/renderer.cc classes/text.cc classes/window.cc classes/character.cc
HEADER  = config.h classes/fps.h classes/images.h classes/renderer.h classes/text.h classes/window.h classes/character.h

# Linker flags
LFLAGS = -lSDL2 -lSDL2_ttf -lSDL2_image


all : $(TARGET)

$(TARGET) : $(SRC) $(HEADERS)
	$(CC) $(SRC) $(CFLAGS) $(LFLAGS) -o $(TARGET)

clean :
	rm $(TARGET)
