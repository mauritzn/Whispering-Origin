#include <SDL2/SDL.h>

#include <iostream>
#include <string>
#include <sstream>

#include "tile.h"
#include "../items.h"
#include "functions.h"
#include "images.h"
#include "../config.h"
#include "fps.h"
#include "player.h"
#include "text.h"

using namespace std;


Tile::Tile(Window& win, Renderer& ren, FPS& fps, Player& player, const grid_tile_data& id, int row, int col) {
  _win = &win;
  _ren = &ren;
  _fps = &fps;
  //_world = &world;
  _player = &player;

  _id = id;
  if(_id != -1) {
    _type = get_tile_type(_id);
    _tile_name = get_tile_name(_id);
  } else {
    _type = COLLIDER;
    _tile_name = "Collider";
  }


  _row = row;
  _col = col;
  _row_and_col = combine_row_and_col(_row, _col);



  string tile_image_path = "";

  if(_type == TREE) {
    _tile_grid_size = tree_grid_size;
    tile_image_path = tree_image_path;

    _resources = 5;
    _resources_left = _resources;
  } else if(_type == ORE) {
    _tile_grid_size = ore_grid_size;
    tile_image_path = ore_image_path;

    _resources = 3;
    _resources_left = _resources;
  }
  //else if(_type == FISH) _tile_grid_size = fish_grid_size;


  _progress_text = new Text(*_win, *_ren, fonts["main_18"], color_white, (format_number(_resources_left) + "/" + format_number(_resources)), 0, 0);
  _progress_text->align_center_y();
  //if(tile_image_path != "") cout << "tile Image Path: " << tile_image_path << endl;


  _x_start = (_col * grid_size);
  _x_end = (_x_start + grid_size);
  _y_start = (_row * grid_size);
  _y_end = (_y_start + grid_size);


  if(tile_image_path != "") {
    int tile_x = _x_start - (_tile_grid_size / 2) + (grid_size / 2);
    int tile_y = _y_start - (_tile_grid_size - grid_size);


    _tile_image = new PNG(*_win, *_ren, tile_image_path, tile_x, tile_y);

    _tile_image->set_container_width(_tile_grid_size);
    _tile_image->set_container_height(_tile_grid_size);
    _tile_image->set_image_width(_tile_grid_size);
    _tile_image->set_image_height(_tile_grid_size);

    // 0 value is temporary
    _tile_image->set_image_x(0);
    _tile_image->set_image_y(0);
  } else {
    _tile_image = NULL;
  }
}



int Tile::width() {
  if(_tile_image != NULL) {
    return _tile_image->width();
  } else {
    return 0;
  }
}
int Tile::height() {
  if(_tile_image != NULL) {
    return _tile_image->height();
  } else {
    return 0;
  }
}


int Tile::get_x_start() { return _x_start; }
int Tile::get_x_end() { return _x_end; }

int Tile::get_y_start() { return _y_start; }
int Tile::get_y_end() { return _y_end; }


int Tile::get_original_x() {
  if(_tile_image != NULL) {
    return _tile_image->get_original_x();
  } else {
    return 0;
  }
}
int Tile::get_original_y() {
  if(_tile_image != NULL) {
    return _tile_image->get_original_y();
  } else {
    return 0;
  }
}

void Tile::set_x(int new_x) {
  if(_tile_image != NULL) {
    _tile_image->set_x(new_x);
  }
}
void Tile::set_y(int new_y) {
  if(_tile_image != NULL) {
    _tile_image->set_y(new_y);
  }
}


void Tile::set_row(int new_row) {
  _row = new_row;
  _row_and_col = combine_row_and_col(_row, _col);

  _y_start = (_row * grid_size);
  _y_end = (_y_start + grid_size);
}

void Tile::set_col(int new_col) {
  _col = new_col;
  _row_and_col = combine_row_and_col(_row, _col);

  _x_start = (_col * grid_size);
  _x_end = (_x_start + grid_size);
}

int Tile::get_row() { return _row; }
int Tile::get_col() { return _col; }
string Tile::get_row_and_col() { return _row_and_col; }


grid_tile_data Tile::id() { return _id; }
grid_tile_type Tile::type() { return _type; }
string Tile::tile_name() { return _tile_name; }


void Tile::action() {
  if((_fps->ticks() - _last_action_at) >= 1000) {
    if(_resources_left > 0) {
      _last_action_at = _fps->ticks();

      _resources_left--;
      _progress_text->update((format_number(_resources_left) + "/" + format_number(_resources)));

      if(_type == TREE) _player->skill("Woodcutting")->increase_xp(5);
      else if(_type == ORE) _player->skill("Mining")->increase_xp(5);
      //else if(_type == FISH) _player->skill("Fishing")->increase_xp(5);

      if(_resources_left == 0) {
        if(_depleted_at == 0) {
          _depleted_at = _fps->ticks();
          _tile_image->set_image_x(_tile_grid_size);
        }
      }
    }
  }
}

bool Tile::action_on_cooldown() {
  if((_fps->ticks() - _last_action_at) >= 1000) {
    return false;
  } else {
    return true;
  }
}


void Tile::show_progress() {
  _progress_text->set_x(_tile_image->get_x() + ((_tile_image->width() / 2) - (_progress_text->width() / 2)));
  _progress_text->set_y(_tile_image->get_y());

  if(_type == ORE) _progress_text->set_y(_progress_text->get_y() - 30);

  _progress_text->render();
}


void Tile::update() {
  if(_depleted_at > 0) {
    if(_fps->ticks() - _depleted_at >= 5000) {
      _depleted_at = 0;
      _tile_image->set_image_x(0);
      _resources_left = _resources;
      _progress_text->update((format_number(_resources_left) + "/" + format_number(_resources)));
    } else {
      _progress_text->update(format_number(((5000 - (_fps->ticks() - _depleted_at)) / 1000) + 1) + "s");
    }
  }
}

void Tile::render() {
  if(_tile_image != NULL) {
    _tile_image->render();
  }
}
