#include <SDL2/SDL.h>

#include <iostream>
#include <string>
#include <sstream>

#include "item.h"
#include "../items.h"
#include "functions.h"
#include "images.h"
#include "../config.h"
#include "fps.h"
#include "player.h"
#include "text.h"

using namespace std;


Item::Item(Window& win, Renderer& ren, FPS& fps, Player& player, const tile_type& type, const int id, int row, int col) {
  _win = &win;
  _ren = &ren;
  _fps = &fps;
  //_world = &world;
  _player = &player;

  _type = type;
  _id = id;
  
  
  _row = row;
  _col = col;
  _row_and_col = combine_row_and_col(_row, _col);
  
  
  
  string item_image_path = "";
  
  if(_type == TREE) {
    _item_grid_size = tree_grid_size;
    item_image_path = tree_image_path;
    
    _resources = 5;
    _resources_left = _resources;
  } else if(_type == ORE) {
    _item_grid_size = ore_grid_size;
    item_image_path = ore_image_path;
    
    _resources = 3;
    _resources_left = _resources;
  }
  //else if(_type == FISH) _item_grid_size = fish_grid_size;
  
  
  _progress_text = new Text(*_win, *_ren, main_font_18, color_white, (format_number(_resources_left) + "/" + format_number(_resources)), 0, 0);
  _progress_text->align_center_y();
  //if(item_image_path != "") cout << "Item Image Path: " << item_image_path << endl;
  
  
  _x_start = (_col * grid_size);
  _x_end = (_x_start + grid_size);
  _y_start = (_row * grid_size);
  _y_end = (_y_start + grid_size);
  
  
  if(item_image_path != "") {
    int item_x = _x_start - (_item_grid_size / 2) + (grid_size / 2);
    int item_y = _y_start - (_item_grid_size - grid_size);
    
    
    _item_image = new PNG(*_win, *_ren, item_image_path, item_x, item_y);
    
    _item_image->set_container_width(_item_grid_size);
    _item_image->set_container_height(_item_grid_size);
    _item_image->set_image_width(_item_grid_size);
    _item_image->set_image_height(_item_grid_size);
    
    // 0 value is temporary
    _item_image->set_image_x(0);
    _item_image->set_image_y(0);
  } else {
    _item_image = NULL;
  }
}



int Item::width() {
  if(_item_image != NULL) {
    return _item_image->width();
  } else {
    return 0;
  }
}
int Item::height() {
  if(_item_image != NULL) {
    return _item_image->height();
  } else {
    return 0;
  }
}


int Item::get_x_start() { return _x_start; }
int Item::get_x_end() { return _x_end; }

int Item::get_y_start() { return _y_start; }
int Item::get_y_end() { return _y_end; }


int Item::get_original_x() {
  if(_item_image != NULL) {
    return _item_image->get_original_x();
  } else {
    return 0;
  }
}
int Item::get_original_y() {
  if(_item_image != NULL) {
    return _item_image->get_original_y();
  } else {
    return 0;
  }
}

void Item::set_x(int new_x) {
  if(_item_image != NULL) {
    _item_image->set_x(new_x);
  }
}
void Item::set_y(int new_y) {
  if(_item_image != NULL) {
    _item_image->set_y(new_y);
  }
}


void Item::set_row(int new_row) {
  _row = new_row;
  _row_and_col = combine_row_and_col(_row, _col);
  
  _y_start = (_row * grid_size);
  _y_end = (_y_start + grid_size);
}

void Item::set_col(int new_col) {
  _col = new_col;
  _row_and_col = combine_row_and_col(_row, _col);
  
  _x_start = (_col * grid_size);
  _x_end = (_x_start + grid_size);
}

int Item::get_row() { return _row; }
int Item::get_col() { return _col; }
string Item::get_row_and_col() { return _row_and_col; }


string Item::get_item_name() { return _item_name; }
tile_type Item::get_type() { return _type; }
int Item::get_id() { return _id; }


void Item::action() {
  if((_fps->ticks() - _last_action_at) >= 1000) {
    if(_resources_left > 0) {
      _last_action_at = _fps->ticks();
    
      _resources_left--;
      _progress_text->update((format_number(_resources_left) + "/" + format_number(_resources)));
      
      if(_resources_left == 0) {
        if(_depleted_at == 0) {
          _depleted_at = _fps->ticks();
          _item_image->set_image_x(_item_grid_size);
        }
      }
    }
  }
}

void Item::show_progress() {
  _progress_text->set_x(_item_image->get_x() + ((_item_image->width() / 2) - (_progress_text->width() / 2)));
  _progress_text->set_y(_item_image->get_y());
  
  if(_type == ORE) _progress_text->set_y(_progress_text->get_y() - 30);
  
  _progress_text->render();
}


void Item::update() {
  if(_depleted_at > 0) {
    if(_fps->ticks() - _depleted_at >= 5000) {
      _depleted_at = 0;
      _item_image->set_image_x(0);
      _resources_left = _resources;
      _progress_text->update((format_number(_resources_left) + "/" + format_number(_resources)));
    } else {
      _progress_text->update(format_number(((5000 - (_fps->ticks() - _depleted_at)) / 1000) + 1) + "s");
    }
  }
}

void Item::render() {
  if(_item_image != NULL) {
    _item_image->render();
  }
}