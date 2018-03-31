#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <utility>

#include "functions.h"
#include "window.h"
#include "images.h"
#include "world.h"

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


vector<string> explode_string(string const& string_to_explode, char delimiter) {
  vector<string> result;
  istringstream iss(string_to_explode);

  for(string token; getline(iss, token, delimiter); ) {
    result.push_back(move(token));
  }

  return result;
}


void add_cell_to_grid(string const& string_to_parse, GRID& grid) {
  vector<string> exploded = explode_string(string_to_parse, 'x');
  
  grid.push_back(*(new CELL()));
  grid.back().row = stoi(exploded[0]);
  
  
  if(exploded[1].find(':') != string::npos) {
    exploded = explode_string(exploded[1], ':');
    grid.back().col = stoi(exploded[0]);
    grid.back().id = stoi(exploded[1]);
  } else {
    grid.back().col = stoi(exploded[1]);
    grid.back().id = -1;
  }
}