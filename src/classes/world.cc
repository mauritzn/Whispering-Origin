#include <SDL2/SDL.h>

#include <iostream>
#include <cmath>
// #include <string>
#include <vector>

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
  
  
  _test_collisions = {
    {2, 15}, {2, 16}, {2, 17}, {3, 15}, {3, 17}, {3, 25}, {3, 26}, {3, 27}, {3, 28}, {3, 29}, {3, 30}, {3, 31}, {3, 32}, {4, 12}, {4, 13}, {4, 14}, {4, 15}, {4, 17}, {4, 24}, {4, 25}, {4, 28}, {4, 29}, {4, 32}, {4, 33}, {4, 46}, {4, 47}, {4, 48}, {4, 49}, {5, 9}, {5, 10}, {5, 11}, {5, 12}, {5, 17}, {5, 18}, {5, 19}, {5, 20}, {5, 23}, {5, 24}, {5, 33}, {5, 34}, {5, 35}, {5, 36}, {5, 37}, {5, 38}, {5, 39}, {5, 45}, {5, 46}, {5, 49}, {5, 50}, {6, 8}, {6, 9}, {6, 18}, {6, 19}, {6, 20}, {6, 21}, {6, 22}, {6, 23}, {6, 39}, {6, 40}, {6, 41}, {6, 42}, {6, 44}, {6, 45}, {6, 50}, {6, 51}, {6, 52}, {7, 7}, {7, 8}, {7, 42}, {7, 43}, {7, 44}, {7, 52}, {7, 53}, {7, 54}, {8, 6}, {8, 7}, {8, 54}, {8, 55}, {9, 4}, {9, 5}, {9, 6}, {9, 55}, {10, 3}, {10, 4}, {10, 55}, {10, 56}, {11, 3}, {11, 56}, {12, 3}, {12, 56}, {12, 57}, {13, 3}, {13, 57}, {14, 2}, {14, 3}, {14, 57}, {15, 2}, {15, 3}, {15, 53}, {15, 54}, {15, 55}, {15, 56}, {15, 57}, {16, 3}, {16, 52}, {16, 53}, {16, 55}, {16, 56}, {17, 3}, {17, 51}, {17, 52}, {18, 2}, {18, 3}, {18, 51}, {19, 2}, {19, 3}, {19, 51}, {19, 52}, {20, 3}, {20, 51}, {20, 52}, {21, 3}, {21, 4}, {21, 50}, {21, 51}, {22, 4}, {22, 50}, {23, 4}, {23, 5}, {23, 50}, {24, 5}, {24, 50}, {25, 5}, {25, 6}, {25, 50}, {26, 6}, {26, 50}, {26, 51}, {27, 6}, {27, 7}, {27, 50}, {27, 51}, {28, 7}, {28, 8}, {28, 9}, {28, 11}, {28, 12}, {28, 13}, {28, 19}, {28, 20}, {28, 21}, {28, 22}, {28, 25}, {28, 26}, {28, 27}, {28, 28}, {28, 29}, {28, 30}, {28, 33}, {28, 34}, {28, 35}, {28, 50}, {29, 9}, {29, 10}, {29, 11}, {29, 13}, {29, 14}, {29, 15}, {29, 16}, {29, 17}, {29, 18}, {29, 19}, {29, 22}, {29, 23}, {29, 24}, {29, 25}, {29, 30}, {29, 31}, {29, 32}, {29, 33}, {29, 35}, {29, 36}, {29, 50}, {30, 36}, {30, 37}, {30, 38}, {30, 39}, {30, 40}, {30, 41}, {30, 42}, {30, 45}, {30, 46}, {30, 47}, {30, 48}, {30, 49}, {30, 50}, {31, 42}, {31, 43}, {31, 44}, {31, 45}, {31, 48}, {31, 49}, // colliders
    
    {10, 29}, {11, 41}, {12, 37}, {15, 22}, {16, 39} // trees
  };
  
  
  _trees.push_back(new PNG(*_win, *_ren, tree_image_path, 897, 221));
  _trees.push_back(new PNG(*_win, *_ren, tree_image_path, 1281, 253));
  _trees.push_back(new PNG(*_win, *_ren, tree_image_path, 1153, 285));
  _trees.push_back(new PNG(*_win, *_ren, tree_image_path, 673, 381));
  _trees.push_back(new PNG(*_win, *_ren, tree_image_path, 1217, 413));
  
  
  
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
  
  
  for(GRID const& value: _test_collisions) {
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
  
  for(int i = 0; i < (signed) _trees.size(); i++) {
    _trees[i]->set_x(_trees[i]->get_original_x() + this->get_x());
    _trees[i]->set_y(_trees[i]->get_original_y() + this->get_y());
  }
  
  
  for(int row = 0; row < (this->width() / _grid_size); row++) {
    if(this->get_player_row() == row) _player->render();
    
    for(int i = 0; i < (signed) _trees.size(); i++) {
      if(floor((_trees[i]->get_original_y() + 100) / 32) == row) _trees[i]->render();
    }
  }
}