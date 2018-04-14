###############################
#
# Makefile for SDL Development
#
###############################

CC      = g++
CFLAGS  = -Wall -std=c++14
TARGET  = Whispering\ Origin
SRC     = main.cc config.cc items.cc classes/functions.cc classes/fps.cc classes/images.cc classes/renderer.cc classes/text.cc classes/window.cc classes/player.cc classes/world.cc classes/item.cc classes/progress_bar.cc
HEADER  = config.h items.h classes/functions.h classes/fps.h classes/images.h classes/renderer.h classes/text.h classes/window.h classes/player.h classes/world.h classes/item.h classes/progress_bar.h

# Linker flags
LFLAGS = -lSDL2 -lSDL2_ttf -lSDL2_image


all : $(TARGET)

$(TARGET) : $(SRC) $(HEADERS)
	$(CC) $(SRC) $(CFLAGS) $(LFLAGS) -o $(TARGET)

clean :
	rm $(TARGET)
