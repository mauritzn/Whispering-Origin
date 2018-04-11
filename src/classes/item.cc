#include <SDL2/SDL.h>

#include <iostream>
#include <string>
#include <sstream>

#include "item.h"
#include "../items.h"
#include "functions.h"
#include "images.h"
#include "../config.h"
#include "player.h"

using namespace std;


Item::Item(Window& win, Renderer& ren, World& world, Player& player, const tile_type& type, const int id, int row, int col) {
  _win = &win;
  _ren = &ren;
  _world = &world;
  _player = &player;

  _texture = new PNG(*_win, *_ren, world_texture_path, 0, 0);
  
  _type = type;
  _id = id;
  
  _row = row;
  _col = col;
  _row_and_col = combine_row_and_col(_row, _col);
}



int Item::get_x_start() { return 0; }
int Item::get_x_end() { return 0; }

int Item::get_y_start() { return 0; }
int Item::get_y_end() { return 0; }


void Item::action() {}

void Item::update() {}
void Item::render() {}