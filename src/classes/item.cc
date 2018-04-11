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


Item::Item(Window& win, Renderer& ren, Player& player, const tile_type& type, const int id, int row, int col) {
  _win = &win;
  _ren = &ren;
  //_world = &world;
  _player = &player;

  _type = type;
  _id = id;
  
  
  _row = row;
  _col = col;
  _row_and_col = combine_row_and_col(_row, _col);
  
  
  
  int item_grid_size = 0;
  string item_image_path = "";
  
  if(_type == TREE) {
    item_grid_size = tree_grid_size;
    item_image_path = tree_image_path;
  } else if(_type == ORE) {
    item_grid_size = ore_grid_size;
    item_image_path = ore_image_path;
  }
  //else if(_type == FISH) item_grid_size = fish_grid_size;
  
  //if(item_image_path != "") cout << "Item Image Path: " << item_image_path << endl;
  
  
  _x_start = (_col * grid_size);
  _x_end = (_x_start + grid_size);
  _y_start = (_row * grid_size);
  _y_end = (_y_start + grid_size);
  
  
  if(item_image_path != "") {
    int item_x = _x_start - (item_grid_size / 2) + (grid_size / 2);
    int item_y = _y_start - (item_grid_size - grid_size);
    
    
    _item_image = new PNG(*_win, *_ren, item_image_path, item_x, item_y);
    
    _item_image->set_container_width(item_grid_size);
    _item_image->set_container_height(item_grid_size);
    _item_image->set_image_width(item_grid_size);
    _item_image->set_image_height(item_grid_size);
    
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
  cout << "!! ACTION OCCURED !!" << endl;
}
void Item::show_progress() {}


void Item::update() {}

void Item::render() {
  if(_item_image != NULL) {
    _item_image->render();
  }
}