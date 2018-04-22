#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

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
#include "text.h"
#include "tile.h"

using namespace std;


World::World(Window& win, Renderer& ren, FPS& fps, Player& player) {
  _win = &win;
  _ren = &ren;
  _fps = &fps;
  _player = &player;

  _texture = new PNG(*_win, *_ren, world_texture_path, 0, 0);



  for(int i = 0; i < 4; i++) {
  _debug_neighbor.push_back(new Text(*_win, *_ren, fonts["main_16"], color_white, dir_text[i], 0, 0));
  }

  _debug_neighbor[N_NORTH]->align_center();
  _debug_neighbor[N_NORTH]->set_y((_debug_neighbor[N_NORTH]->get_y() - 40));

  _debug_neighbor[N_SOUTH]->align_center();
  _debug_neighbor[N_SOUTH]->set_y((_debug_neighbor[N_SOUTH]->get_y() + 50));

  _debug_neighbor[N_WEST]->align_center_y();
  _debug_neighbor[N_WEST]->align_right();
  _debug_neighbor[N_WEST]->set_x(((window_width / 2) - (_debug_neighbor[N_WEST]->width() / 2)) - 45);

  _debug_neighbor[N_EAST]->align_center_y();
  _debug_neighbor[N_EAST]->set_x(((window_width / 2) - (_debug_neighbor[N_EAST]->width() / 2)) + 45);



  string line;
  string data;
  vector<string> tiles_to_add;
  for(int i = 0; i < 4; i++) _neighbor_tiles.push_back(NULL);

  ifstream map_data(world_data_path);

  if(map_data.fail()) {
    cout << "!! FAILED TO READ MAP DATA (using default grid size) !!" << endl;
  } else {
    int line_nr = 1;
    while(getline(map_data, line)) {
      //cout << line << endl;

      if(line_nr == 1) {
        vector<string> map_header = explode_string(line, ':');
        vector<string> map_size = explode_string(map_header[0], 'x');

        _map_width = stoi(map_size[0]);
        _map_height = stoi(map_size[1]);
        grid_size = stoi(map_header[1]);
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


int World::get_x() { return _texture->get_x(); }
int World::get_y() { return _texture->get_y(); }

void World::set_x(int new_x) { _texture->set_x(new_x); }
void World::set_y(int new_y) { _texture->set_y(new_y); }


int World::get_player_x() {
  int test_x = this->get_x() - (window_width / 2) + (grid_size / 2);
  test_x *= -1;
  return test_x;
}
int World::get_player_y() {
  int test_y = this->get_y() - (window_height / 2);
  test_y *= -1;
  return test_y;
}


int World::get_player_row() {
  return round(this->get_player_y() / (float) grid_size);
}
int World::get_player_col() {
  return round(this->get_player_x() / (float) grid_size);
}

string World::get_player_row_and_col() {
  return combine_row_and_col(this->get_player_row(), this->get_player_col());
}



void World::add_to_grid(const string& string_to_parse, const tile_type& type) {
  vector<string> exploded = explode_string(string_to_parse, 'x');

  int row = stoi(exploded[0]);
  int col = 0;
  int id = -1;

  if(exploded[1].find(':') != string::npos) {
    exploded = explode_string(exploded[1], ':');
    col = stoi(exploded[0]);
    id = stoi(exploded[1]);
  } else {
    col = stoi(exploded[1]);
  }

  _tiles.push_back(new Tile(*_win, *_ren, *_fps, *_player, type, id, row, col));
}



void World::update_current_tile() {
  if(_current_tile != NULL) {
    if(_current_tile->get_row() != this->get_player_row()) {
      _current_tile->set_row(this->get_player_row());
    }

    if(_current_tile->get_col() != this->get_player_col()) {
      _current_tile->set_col(this->get_player_col());
    }
  } else {
    _current_tile = new Tile(*_win, *_ren, *_fps, *_player, TERRAIN, -1, this->get_player_row(), this->get_player_col());
  }
}

void World::update_neighbors() {
  bool neighbor_found = false;
  neighbor_direction n_dir = N_SOUTH;

  string row_and_col_north = combine_row_and_col((_current_tile->get_row() - 1), _current_tile->get_col());
  string row_and_col_south = combine_row_and_col((_current_tile->get_row() + 1), _current_tile->get_col());
  string row_and_col_west = combine_row_and_col(_current_tile->get_row(), (_current_tile->get_col() - 1));
  string row_and_col_east = combine_row_and_col(_current_tile->get_row(), (_current_tile->get_col() + 1));


  // reset neighbors
  for(int i = 0; i < 4; i++) {
    _neighbor_tiles[i] = NULL;
  }



  for(TILE const& value: _tiles) {
    if(value->get_type() != TERRAIN) {
      if(value->get_row_and_col() == row_and_col_north) {
        n_dir = N_NORTH;
        neighbor_found = true;
      } else if(value->get_row_and_col() == row_and_col_south) {
        n_dir = N_SOUTH;
        neighbor_found = true;
      } else if(value->get_row_and_col() == row_and_col_west) {
        n_dir = N_WEST;
        neighbor_found = true;
      } else if(value->get_row_and_col() == row_and_col_east) {
        n_dir = N_EAST;
        neighbor_found = true;
      } else {
        neighbor_found = false;
      }

      if(neighbor_found) _neighbor_tiles[n_dir] = value;
    }
  }
}



void World::key_pressed(SDL_Keycode key) {
  if(key == SDLK_w) _moving_up = true;
  if(key == SDLK_s) _moving_down = true;
  if(key == SDLK_a) _moving_left = true;
  if(key == SDLK_d) _moving_right = true;
  if(key == SDLK_SPACE) _action_key_pressed = true;
}

void World::key_released(SDL_Keycode key){
  if(key == SDLK_w) _moving_up = false;
  if(key == SDLK_s) _moving_down = false;
  if(key == SDLK_a) _moving_left = false;
  if(key == SDLK_d) _moving_right = false;
  if(key == SDLK_SPACE) _action_key_pressed = false;
}



void World::update() {
  float delta_velocity = (world_velocity * _fps->delta_time());

  if(_moving_up) {
    _player->set_direction(NORTH);

    if((this->get_player_y() - delta_velocity) > 0) {
      if(_neighbor_tiles[N_NORTH] == NULL) {
        _y += delta_velocity;
      } else {
        if(_neighbor_tiles[N_NORTH]->get_type() == TERRAIN) {
          _y += delta_velocity;
        } else {
          if((this->get_player_y() - delta_velocity) > (_neighbor_tiles[N_NORTH]->get_y_end() - 15)) {
            _y += delta_velocity;
          }
        }
      }
    }
  }

  if(_moving_down) {
    _player->set_direction(SOUTH);

    if((this->get_player_y() + delta_velocity) < (_texture->height() - grid_size)) {
      if(_neighbor_tiles[N_SOUTH] == NULL) {
        _y -= delta_velocity;
      } else {
        if(_neighbor_tiles[N_SOUTH]->get_type() == TERRAIN) {
          _y -= delta_velocity;
        } else {
          if((this->get_player_y() + delta_velocity) < ((_neighbor_tiles[N_SOUTH]->get_y_start() - grid_size) + 0)) {
            _y -= delta_velocity;
          }
        }
      }
    }
  }


  if(_moving_left) {
    _player->set_direction(WEST);

    if((this->get_player_x() - delta_velocity) > 0) {
      if(_neighbor_tiles[N_WEST] == NULL) {
        _x += delta_velocity;
      } else {
        if(_neighbor_tiles[N_WEST]->get_type() == TERRAIN) {
          _x += delta_velocity;
        } else {
          if((this->get_player_x() - delta_velocity) > (_neighbor_tiles[N_WEST]->get_x_end() - 10)) {
            _x += delta_velocity;
          }
        }
      }
    }
  }

  if(_moving_right) {
    _player->set_direction(EAST);

    if((this->get_player_x() + delta_velocity) < (_texture->width() - grid_size)) {
      //_x -= delta_velocity;

      if(_neighbor_tiles[N_EAST] == NULL) {
        _x -= delta_velocity;
      } else {
        if(_neighbor_tiles[N_EAST]->get_type() == TERRAIN) {
          _x -= delta_velocity;
        } else {
          if((this->get_player_x() + delta_velocity) < ((_neighbor_tiles[N_EAST]->get_x_start() - grid_size) + 8)) {
            _x -= delta_velocity;
          }
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


  if(this->get_player_row_and_col() != _current_tile->get_row_and_col()) {
    this->update_current_tile();
    this->update_neighbors();

    /*
    if(debug_mode) {
      cout << "PLAYER moved to new tile (" << _current_tile->get_row_and_col() << ")" << endl;
      for(int i = 0; i < 4; i++) {
        cout << " > Neighbor " << dir_text[i] << ": " << _neighbor_tiles[i]->row_and_col << " => " << type_text[(_neighbor_tiles[i]->get_type())]
             << " || x: " << _neighbor_tiles[i]->get_x_start() << ", y: " << _neighbor_tiles[i]->get_y_start() << endl;
      }
      cout << endl;
    }
    */

    for(int i = 0; i < 4; i++) {
      if(_neighbor_tiles[i] != NULL) _debug_neighbor[i]->update(type_text[(_neighbor_tiles[i]->get_type())]);
      else _debug_neighbor[i]->update(type_text[4]);
    }
  }



  player_direction to_check = NORTH;

  for(int i = 0; i < 4; i++) {
    if(i == N_NORTH) to_check = NORTH;
    else if(i == N_SOUTH) to_check = SOUTH;
    else if(i == N_WEST) to_check = WEST;
    else if(i == N_EAST) to_check = EAST;


    if(_player->get_direction() == to_check) {
      if(_neighbor_tiles[i] != NULL) {
        if(_action_key_pressed) {
          if(_neighbor_tiles[i]->get_type() != TERRAIN && _neighbor_tiles[i]->get_type() != COLLIDER) {
            _neighbor_tiles[i]->action();
          }
        }

        if(debug_mode) {
          if(_neighbor_tiles[i]->action_on_cooldown()) {
            _debug_neighbor[i]->update(type_text[(_neighbor_tiles[i]->get_type())] + " [ACTION]");
          } else {
            _debug_neighbor[i]->update(type_text[(_neighbor_tiles[i]->get_type())]);
          }
        }
      }
    }
  }



  for(TILE const& value: _tiles) {
    if(value->get_type() != TERRAIN && value->get_type() != COLLIDER) {
      value->update();
    }
  }
}


void World::render() {
  _texture->render();

  for(TILE const& value: _tiles) {
    if(value->get_type() != TERRAIN && value->get_type() != COLLIDER) {
      value->set_x(value->get_original_x() + this->get_x());
      value->set_y(value->get_original_y() + this->get_y());
    }
  }

  for(int row = 0; row < (this->width() / grid_size); row++) {
    if(this->get_player_row() == row) _player->render();

    for(TILE const& value: _tiles) {
      // needs to be tweaked a bit
      if(floor((value->get_original_y() + (value->height() - grid_size)) / grid_size) == row) {
        value->render();
      }
    }
  }


  neighbor_direction n_dir = N_SOUTH;
  if(_player->get_direction() == NORTH) n_dir = N_NORTH;
  else if(_player->get_direction() == SOUTH) n_dir = N_SOUTH;
  else if(_player->get_direction() == WEST) n_dir = N_WEST;
  else if(_player->get_direction() == EAST) n_dir = N_EAST;

  if(_neighbor_tiles[n_dir] != NULL) {
    if(_neighbor_tiles[n_dir]->get_type() != TERRAIN && _neighbor_tiles[n_dir]->get_type() != COLLIDER) {
      _neighbor_tiles[n_dir]->show_progress();
    }
  }


  if(debug_mode) {
    for(int i = 0; i < 4; i++) {
      _debug_neighbor[i]->render();
    }
  }
}
