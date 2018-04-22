#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <utility>
#include <map>

#include "functions.h"
#include "window.h"
#include "images.h"
#include "fps.h"
#include "player.h"
#include "world.h"
#include "../config.h"

using namespace std;


int constrain(int number, int min, int max) {
  if(number < min) number = min;
  if(number > max) number = max;

  return number;
}


int constrain_png_width(int number, Window& win, PNG& png) {
  return constrain(number, 0, (win.width() - png.width()));
}

int constrain_png_height(int number, Window& win, PNG& png) {
  return constrain(number, 0, (win.height() - png.height()));
}


string format_number(int number_to_format) {
  stringstream formatted_number;

  formatted_number.imbue(locale(""));
  formatted_number << fixed << number_to_format;

  return formatted_number.str();
}

string to_fixed(float number_to_fix) {
  stringstream fixed_number;
  fixed_number << fixed << setprecision(2) << number_to_fix;

  return fixed_number.str();
}


vector<string> explode_string(const string& string_to_explode, char delimiter) {
  vector<string> result;
  istringstream iss(string_to_explode);

  for(string token; getline(iss, token, delimiter); ) {
    result.push_back(move(token));
  }

  return result;
}


string combine_row_and_col(int row, int col) {
  stringstream row_and_col_string;
  row_and_col_string << row << "x" << col;

  return row_and_col_string.str();
}






bool get_RGB(SDL_Color& color, SDL_Surface* surface, int x, int y) {
  if(surface->format->BitsPerPixel == 32) {
    uint32_t* pixels = (uint32_t*) surface->pixels;
    uint32_t pixel = pixels[(y * surface->w) + x];

    SDL_GetRGB(pixel, surface->format, &(color.r), &(color.g), &(color.b));
    return true;
  } else {
    return false;
  }
}

int concat_RGB(SDL_Color& color) {
  stringstream concat;

  concat << (unsigned) color.r
         << (unsigned) color.g
         << (unsigned) color.b;

  return stoi(concat.str());
}



bool is_valid_type(SDL_Color& color) {
  grid_tile_type type = (grid_tile_type) color.r;

  if(type == TREE) return true;
  else if(type == ORE) return true;
  else if(type == FISH) return true;
  else return false;
}

bool is_valid_tile(int data) {
  auto search = grid_tiles.find((grid_tile_data) data);

  if(search != grid_tiles.end()) {
    return true;
  } else {
    return false;
  }
}

grid_tile_type get_tile_type(grid_tile_data tile) {
  if(is_valid_tile((int) tile)) {
    return grid_tiles.at(tile);
  }

  return TREE;
}

string get_tile_name(grid_tile_data tile) {
  if(is_valid_tile((int) tile)) {
    return grid_tile_names.at(tile);
  }

  return "";
}






bool init_SDL() {
  if(SDL_Init(SDL_INIT_VIDEO) != 0) {
    cout << "SDL_Init Error: " << SDL_GetError() << endl;
    return false;
  }

  if(TTF_Init() != 0) {
    cout << "TTF_Init Error: " << SDL_GetError() << endl;
    return false;
  }

  int SDL_image_flags = IMG_INIT_PNG;
  if(!(IMG_Init(SDL_image_flags) & SDL_image_flags)) {
    cout << "IMG_Init Error: " << SDL_GetError() << endl;
    return false;
  }


  // set the fonts
  fonts["main_12"] = TTF_OpenFont(main_font_path, 12);
  fonts["main_14"] = TTF_OpenFont(main_font_path, 14);
  fonts["main_16"] = TTF_OpenFont(main_font_path, 16);
  fonts["main_18"] = TTF_OpenFont(main_font_path, 18);
  fonts["main_20"] = TTF_OpenFont(main_font_path, 20);
  fonts["main_32"] = TTF_OpenFont(main_font_path, 32);

  return true;
}


void init_game() {
  for(int i = 1; i < max_level; i++) {
    xp_rates.push_back(pow((i * 2), 3));
  }
}



void init_debug_info_position(const map<string, Text*>& info) {
  Text* first_debug_text;
  for(const auto& value : info) {
    if(value.second->get_y() == 1) {
      first_debug_text = value.second;
      first_debug_text->set_y(debug_info_y_start);
    }

    value.second->set_x(debug_info_x_start);
  }

  for(const auto& value : info) {
    int pos = value.second->get_y();

    if(pos != debug_info_y_start) {
      value.second->set_y((first_debug_text->get_y() + (value.second->height() * (pos - 1))) + (debug_info_y_padding * (pos - 1)));
    }
  }
}


void update_debug_info(map<string, Text*>& info, FPS& fps, Player& player, World& world) {
  info["frames"]->update("Frames: " + format_number(fps.frame_count()));
  info["ticks"]->update("Ticks: " + format_number(fps.ticks()));

  if((fps.ticks() % 500) < 250) {
    info["fps"]->update("FPS: " + to_fixed(fps.get()));
  }

  info["delta_time"]->update("Delta Time: " + to_string(fps.delta_time()));

  // Char-specific text-update
  info["player_hp"]->update("Health: " + format_number(player.health()) + "/" + format_number(player.max_health()));
  info["player_xp"]->update("XP: " + format_number(player.xp()) + "/" + format_number(player.xp_to_level()));
  info["player_lvl"]->update("Level: " + format_number(player.level()) + "/" + to_string(max_level));
  info["player_money"]->update("Money: " + format_number(player.money()));
  info["player_xy"]->update("X: " + to_string(world.get_player_x()) + ", Y: " + to_string(world.get_player_y()));
  info["player_pos"]->update("Position (ROW x COL): " + world.get_player_row_and_col());
}


void render_debug_info(const map<string, Text*>& info) {
  for(const auto& value : info) {
    value.second->render();
  }
}
