#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <utility>

#include "functions.h"
#include "window.h"
#include "images.h"
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


void add_tile_to_grid(const string& string_to_parse, const tile_type& type, GRID& grid) {
  vector<string> exploded = explode_string(string_to_parse, 'x');
  
  grid.push_back(*(new TILE()));
  grid.back().row = stoi(exploded[0]);
  
  
  if(exploded[1].find(':') != string::npos) {
    exploded = explode_string(exploded[1], ':');
    grid.back().col = stoi(exploded[0]);
    grid.back().id = stoi(exploded[1]);
  } else {
    grid.back().col = stoi(exploded[1]);
    grid.back().id = -1;
  }
  
  grid.back().row_and_col = combine_row_and_col(grid.back().row, grid.back().col);
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
  main_font_16 = TTF_OpenFont(main_font_path, 16);
  main_font_20 = TTF_OpenFont(main_font_path, 20);
  main_font_32 = TTF_OpenFont(main_font_path, 32);
  
  return true;
}