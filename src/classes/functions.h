#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <SDL2/SDL.h>
#include <string>
#include <vector>

#include "window.h"
#include "game.h"
#include "image.h"
#include "../config.h"

using namespace std;


extern int constrain(int, int, int); // limit the range of a number

extern string format_number(int); // format text into groups, so 1000 becoms 1,000
extern string to_fixed(float); // fix float to 2 decimals, 2 => 2.00, 2.9 => 2.90


extern vector<string> explode_string(const string&, char); // split up a string into a vector, split happens at the delimiter

extern string combine_row_and_col(int, int); // combines row int and row col into ROWxCOL



extern bool get_RGB(SDL_Color&, SDL_Surface*, int, int); // returns true since this can fail, the first SDL_Color is where to store the result
extern int concat_RGB(SDL_Color&); // combines the red/green/blue values into one number (used for tile IDs)


extern bool is_valid_type(SDL_Color&); // check if the type of a tile is valid (the red value of the pixel)
extern bool is_valid_tile(int); // check if a tile is valid using the number recived from concat_RGB

extern grid_tile_type get_tile_type(grid_tile_data); // get the tile type using the tile's ID
extern string get_tile_name(grid_tile_data); // get the tile's name using the tile's ID



extern bool init_SDL(); // init SDL, Image and TTF, also sets up the main fonts
extern void init_game(); // create XP rates

extern void init_debug_info_position(const map<string, Text*>&); // set the position of all the info rows, y defines their row
extern void update_debug_info(map<string, Text*>&, Game&); // update debug info using values from Game
extern void render_debug_info(const map<string, Text*>&); // render all debug info

#endif