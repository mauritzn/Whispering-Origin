#include <SDL2/SDL.h>

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

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
  vector<string> tiles_to_add;
  for(int i = 0; i < 4; i++) _neighbor_tiles.push_back(new TILE());
  
  ifstream map_data(world_data_path);
  
  if(map_data.fail()) {
    cout << "!! FAILED TO READ MAP DATA (using default grid size) !!" << endl;
    _grid_size = 32; // default back to 32 to avoid error with dividing a float by 0
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
          tiles_to_add = explode_string(data, '|');
          
          for(string const& value: tiles_to_add) {
            if(line[0] == 'C') {
              this->add_to_grid(value, COLLIDER);
            } else if(line[0] == 'T') {
              this->add_to_grid(value, TREE);
            } else if(line[0] == 'O') {
              this->add_to_grid(value, ORE);
            } else if(line[0] == 'F') {
              this->add_to_grid(value, FISH);
            }
          }
        }
      }
      
      line_nr++;
    }
    
    map_data.close();
  }
  
  
  
  
  for(TILE const& value: _items) {
    if(value.type == TREE) {
      int tree_x = (value.col * _grid_size) - (tree_grid_size / 2) + (_grid_size / 2);
      int tree_y = (value.row * _grid_size) - (tree_grid_size - _grid_size);
      
      /*cout << "X: " << tree_x << ", Y: " << tree_y << " || "
          << value.row << "x" << value.col << endl;*/
      
      
      _to_render.push_back(new PNG(*_win, *_ren, tree_image_path, tree_x, tree_y));
      
      _to_render.back()->set_container_width(tree_grid_size);
      _to_render.back()->set_container_height(tree_grid_size);
      _to_render.back()->set_image_width(tree_grid_size);
      _to_render.back()->set_image_height(tree_grid_size);
      
      _to_render.back()->set_image_x(UNCUT);
      _to_render.back()->set_image_y(OAK);
    } else {
      //if(value.type != COLLIDER) _to_render.push_back(new PNG(*_win, *_ren, "images/debug_tile.png", value.x_start, value.y_start));
    }
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
  
  
  this->update_current_tile();
  this->update_neighbors();
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

string World::get_player_row_and_col() {
  stringstream row_and_col;
  row_and_col << this->get_player_row() << "x" << this->get_player_col();
  
  return row_and_col.str();
}



void World::add_to_grid(const string& string_to_parse, const tile_type& type) {
  stringstream row_and_col_string;
  vector<string> exploded = explode_string(string_to_parse, 'x');
  
  _items.push_back(*(new TILE()));
  _items.back().row = stoi(exploded[0]);
  
  
  if(exploded[1].find(':') != string::npos) {
    exploded = explode_string(exploded[1], ':');
    _items.back().col = stoi(exploded[0]);
    _items.back().id = stoi(exploded[1]);
  } else {
    _items.back().col = stoi(exploded[1]);
    //_items.back().id = -1;
  }
  
  
  _items.back().x_start = (_items.back().col * _grid_size);
  _items.back().x_end = (_items.back().x_start + _grid_size);
  
  _items.back().y_start = (_items.back().row * _grid_size);
  _items.back().y_end = (_items.back().y_start + _grid_size);
  
  
  _items.back().type = type;
  
  row_and_col_string << _items.back().row << "x" << _items.back().col;
  _items.back().row_and_col = row_and_col_string.str();
}



void World::update_current_tile() {
  _current_tile.row = this->get_player_row();
  _current_tile.col = this->get_player_col();
  _current_tile.row_and_col = this->get_player_row_and_col();
}

void World::update_neighbors() {
  bool neighbor_found = false;
  neighbor_direction n_dir = N_SOUTH;
  
  stringstream row_and_col_north;
  stringstream row_and_col_south;
  stringstream row_and_col_west;
  stringstream row_and_col_east;
  
  row_and_col_north << (_current_tile.row - 1) << "x" << _current_tile.col;
  row_and_col_south << (_current_tile.row + 1) << "x" << _current_tile.col;
  row_and_col_west << _current_tile.row << "x" << (_current_tile.col - 1);
  row_and_col_east << _current_tile.row << "x" << (_current_tile.col + 1);
  
  
  // reset neighbors
  for(int i = 0; i < 4; i++) {
    _neighbor_tiles[i]->row_and_col = "0x0";
    _neighbor_tiles[i]->row = 0;
    _neighbor_tiles[i]->col = 0;
    
    _neighbor_tiles[i]->x_start = 0;
    _neighbor_tiles[i]->x_end = 0;
    _neighbor_tiles[i]->y_start = 0;
    _neighbor_tiles[i]->y_end = 0;
    
    _neighbor_tiles[i]->type = TERRAIN;
    _neighbor_tiles[i]->id = -1;
  }
  
  
  
  for(TILE const& value: _items) {
    if(value.type != TERRAIN) {
      if(value.row_and_col == row_and_col_north.str()) {
        n_dir = N_NORTH;
        neighbor_found = true;
      } else if(value.row_and_col == row_and_col_south.str()) {
        n_dir = N_SOUTH;
        neighbor_found = true;
      } else if(value.row_and_col == row_and_col_west.str()) {
        n_dir = N_WEST;
        neighbor_found = true;
      } else if(value.row_and_col == row_and_col_east.str()) {
        n_dir = N_EAST;
        neighbor_found = true;
      } else {
        neighbor_found = false;
      }
      
      if(neighbor_found) {
        _neighbor_tiles[n_dir]->row_and_col = value.row_and_col;
        _neighbor_tiles[n_dir]->row = value.row;
        _neighbor_tiles[n_dir]->col = value.col;
        
        _neighbor_tiles[n_dir]->x_start = value.x_start;
        _neighbor_tiles[n_dir]->x_end = value.x_end;
        _neighbor_tiles[n_dir]->y_start = value.y_start;
        _neighbor_tiles[n_dir]->y_end = value.y_end;
        
        _neighbor_tiles[n_dir]->type = value.type;
        _neighbor_tiles[n_dir]->id = value.id;
      }
    }
  }
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
  //float temp_x = _x;
  //float temp_y = _y;
  
  //int temp_row = this->get_player_row();
  //int temp_col = this->get_player_col();
  
  
  if(_moving_up) {
    _player->set_direction(NORTH);
    
    if((this->get_player_y() - delta_velocity) > 0) {
      if(_neighbor_tiles[N_NORTH]->type == TERRAIN) {
        _y += delta_velocity;
      } else {
        if((this->get_player_y() - delta_velocity) > (_neighbor_tiles[N_NORTH]->y_end - 15)) {
          _y += delta_velocity;
        }
      }
    }
  }
  
  if(_moving_down) {
    _player->set_direction(SOUTH);
    
    if((this->get_player_y() + delta_velocity) < (_texture->height() - _grid_size)) {
      if(_neighbor_tiles[N_SOUTH]->type == TERRAIN) {
        _y -= delta_velocity;
      } else {
        if((this->get_player_y() + delta_velocity) < ((_neighbor_tiles[N_SOUTH]->y_start - _grid_size) + 0)) {
          _y -= delta_velocity;
        }
      }
    }
  }

  
  if(_moving_left) {
    _player->set_direction(WEST);
    
    if((this->get_player_x() - delta_velocity) > 0) {
      if(_neighbor_tiles[N_WEST]->type == TERRAIN) {
        _x += delta_velocity;
      } else {
        if((this->get_player_x() - delta_velocity) > (_neighbor_tiles[N_WEST]->x_end - 10)) {
          _x += delta_velocity;
        }
      }
    }
  }
  
  if(_moving_right) {
    _player->set_direction(EAST);
    
    if((this->get_player_x() + delta_velocity) < (_texture->width() - _grid_size)) {
      //_x -= delta_velocity;
      
      if(_neighbor_tiles[N_EAST]->type == TERRAIN) {
        _x -= delta_velocity;
      } else {
        if((this->get_player_x() + delta_velocity) < ((_neighbor_tiles[N_EAST]->x_start - _grid_size) + 8)) {
          _x -= delta_velocity;
        }
      }
    }
  }
  
  
  if(_moving_up || _moving_down) {
    _texture->set_y((int) _y);
  }
  
  if(_moving_left || _moving_right) {
    _texture->set_x((int) _x);
  }
  
  
  if(this->get_player_row_and_col() != _current_tile.row_and_col) {
    this->update_current_tile();
    this->update_neighbors();
    
    /*
    if(debug_mode) {
      string dir_text[4] = {
        "North",
        "East",
        "South",
        "West"
      };
      
      string type_text[5] = {
        "Collider",
        "Tree",
        "Ore",
        "Fish",
        "Terrain"
      };
      
      cout << "PLAYER moved to new tile (" << _current_tile.row_and_col << ")" << endl;
      for(int i = 0; i < 4; i++) {
        cout << " > Neighbor " << dir_text[i] << ": " << _neighbor_tiles[i]->row_and_col << " => " << type_text[(_neighbor_tiles[i]->type)]
             << " || x: " << _neighbor_tiles[i]->x_start << ", y: " << _neighbor_tiles[i]->y_start << endl;
      }
      cout << endl;
    }*/
  }
}


void World::render() {
  _texture->render();
  
  for(PNG* const& value: _to_render) {
    value->set_x(value->get_original_x() + this->get_x());
    value->set_y(value->get_original_y() + this->get_y());
  }
  
  for(int row = 0; row < (this->width() / _grid_size); row++) {
    if(this->get_player_row() == row) _player->render();
    
    for(PNG* const& value: _to_render) {
      // needs to be tweaked a bit
      if(floor((value->get_original_y() + (value->height() - _grid_size)) / _grid_size) == row) {
        value->render();
      }
    }
  }
}