#ifndef UI_H
#define UI_H

#include <SDL2/SDL.h>
#include <map>
#include <string>

#include "game.h"
#include "image.h"
#include "text.h"
#include "tile.h"
#include "../config.h"

using namespace std;


class UI {
  private:
    Game* _game;
    Image* _base;
    map<string, Text*> _text;
    map<string, Text*> _debug_info;


  public:
    UI(Game&);

    void update(); // update debug info
    void render(); // renders UI base, text and debug info
};

#endif