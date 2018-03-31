#include <SDL2/SDL.h>

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>

#include "world.h"
#include "functions.h"
#include "images.h"
#include "../config.h"
#include "fps.h"
#include "player.h"

using namespace std;


World::World(Window& win, Renderer& ren, FPS& fps, Player& player) {
  _win = &win;
  _ren = &ren;
  _fps = &fps;
  _player = &player;

  _texture = new PNG(*_win, *_ren, world_texture_path, 0, 0);
  
  
  string line;
  string data;
  vector<string> cells_to_add;
  
  ifstream map_data(world_data_path);
  
  if(map_data.fail()) {
    cout << "!! FAILED TO READ MAP DATA (using default grid size) !!" << endl;
    _grid_size = 32;
  } else {
    int line_nr = 1;
    while(getline(map_data, line)) {
      //cout << line << endl;
      
      if(line_nr == 1) {
        vector<string> map_header = explode_string(line, ':');
        vector<string> map_size = explode_string(map_header[0], 'x');
        
        _map_width = stoi(map_size[0]);
        _map_height = stoi(map_size[1]);
        _grid_size = stoi(map_header[1]);
      } else {
        if(line.length() > 2) {
          data = line.substr(2); // remove data type
          cells_to_add = explode_string(data, '|');
          
          for(string const& value: cells_to_add) {
            if(line[0] == 'C') {
              add_cell_to_grid(value, _colliders);
            } else if(line[0] == 'T') {
              add_cell_to_grid(value, _trees);
            } else if(line[0] == 'O') {
              add_cell_to_grid(value, _ores);
            } else if(line[0] == 'F') {
              add_cell_to_grid(value, _fish);
            }
          }
        }
      }
      
      line_nr++;
    }
    
    map_data.close();
  }
  
  
  for(CELL const& value: _trees) {
    //                                    TREE_WIDTH
    int tree_x = (value.col * _grid_size) - ((94 / 2) - (_grid_size / 2));
    //                                    TREE_HEIGHT
    int tree_y = (value.row * _grid_size) - (132 - _grid_size);
    tree_y += 1; // fix 1 px error
    
    /*cout << "X: " << tree_x << ", Y: " << tree_y << " || "
         << value.row << "x" << value.col << endl;*/
    
    _trees_to_render.push_back(new PNG(*_win, *_ren, tree_image_path, tree_x, tree_y));
  }
  
  // min value is 0
  // max value is -640 ((window_width / 2) * -1)
  //_texture->set_x((window_width / 4) * -1); // center
  _texture->set_x(304 * -1); // center
  
  // min value is 0
  // max value is -360 ((window_height / 2) * -1)
  //_texture->set_y((window_height / 4) * -1); // center
  _texture->set_y(184 * -1); // center
  
  _x = (float) _texture->get_x();
  _y = (float) _texture->get_y();
}


int World::width() { return _texture->width(); }
int World::height() { return _texture->height(); }
int World::grid_size() { return _grid_size; }


int World::get_x() { return _texture->get_x(); }
int World::get_y() { return _texture->get_y(); }

void World::set_x(int new_x) { _texture->set_x(new_x); }
void World::set_y(int new_y) { _texture->set_y(new_y); }


int World::get_player_x() {
  int test_x = this->get_x() - (window_width / 2) + (_grid_size / 2);
  test_x *= -1;
  return test_x;
}
int World::get_player_y() {
  int test_y = this->get_y() - (window_height / 2);
  test_y *= -1;
  return test_y;
}

int World::get_player_row() {
  return round(this->get_player_y() / (float) _grid_size);
}
int World::get_player_col() {
  return round(this->get_player_x() / (float) _grid_size);
}



void World::key_pressed(SDL_Keycode key) {
  if(key == SDLK_w) _moving_up = true;
  if(key == SDLK_s) _moving_down = true;
  if(key == SDLK_a) _moving_left = true;
  if(key == SDLK_d) _moving_right = true;
}

void World::key_released(SDL_Keycode key){
  if(key == SDLK_w) _moving_up = false;
  if(key == SDLK_s) _moving_down = false;
  if(key == SDLK_a) _moving_left = false;
  if(key == SDLK_d) _moving_right = false;
}



void World::update() {
  float delta_velocity = (world_velocity * _fps->delta_time());
  float temp_x = _x;
  float temp_y = _y;
  
  if(_moving_up) {
    _player->set_direction(NORTH);
    _y += delta_velocity;
    _texture->set_y((int) _y);
  }
  
  if(_moving_down) {
    _player->set_direction(SOUTH);
    _y -= delta_velocity;
    _texture->set_y((int) _y);
  }

  
  if(_moving_left) {
    _player->set_direction(WEST);
    _x += delta_velocity;
    _texture->set_x((int) _x);
  }
  
  if(_moving_right) {
    _player->set_direction(EAST);
    _x -= delta_velocity;
    _texture->set_x((int) _x);
  }
  
  
  
  // This needs to be cleaned up and done better, but for now it works...
  for(CELL const& value: _colliders) {
    if(this->get_player_row() == value.row && this->get_player_col() == value.col) {
      if(_moving_up || _moving_down) {
        _y = temp_y;
        _texture->set_y((int) temp_y);
      }
      
      if(_moving_left || _moving_right) {
        _x = temp_x;
        _texture->set_x((int) temp_x);
      }
    }
  }
  
  
  for(CELL const& value: _trees) {
    if(this->get_player_row() == value.row && this->get_player_col() == value.col) {
      if(_moving_up || _moving_down) {
        _y = temp_y;
        _texture->set_y((int) temp_y);
      }
      
      if(_moving_left || _moving_right) {
        _x = temp_x;
        _texture->set_x((int) temp_x);
      }
    }
  }
  
  
  
  if(this->get_player_row() < 0) {
    _y = temp_y;
    _texture->set_y((int) temp_y);
  }
  
  if(this->get_player_col() < 0) {
    _x = temp_x;
    _texture->set_x((int) temp_x);
  }
  
  
  if(this->get_player_row() > ((_texture->height() / _grid_size) - 1)) {
    _y = temp_y;
    _texture->set_y((int) temp_y);
  }
  
  if(this->get_player_col() > ((_texture->width() / _grid_size) - 1)) {
    _x = temp_x;
    _texture->set_x((int) temp_x);
  }
}


void World::render() {
  _texture->render();
  
  for(PNG* const& tree: _trees_to_render) {
    tree->set_x(tree->get_original_x() + this->get_x());
    tree->set_y(tree->get_original_y() + this->get_y());
  }
  
  for(int row = 0; row < (this->width() / _grid_size); row++) {
    if(this->get_player_row() == row) _player->render();
    
    for(PNG* const& tree: _trees_to_render) {
      if(floor((tree->get_original_y() + 100) / 32) == row) tree->render();
    }
  }
}