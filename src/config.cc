#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "config.h"
#include <string>
using namespace std;








// General
const int window_width = 1280;
const int window_height = 720;

const char* game_name = "Whispering Origin";
const char* icon_path = "images/icon.png";

bool debug_mode = true;


// Fonts
const char* main_font_path = "fonts/Ubuntu_C.ttf";

TTF_Font* main_font_16;
TTF_Font* main_font_20;
TTF_Font* main_font_32;


// Colors
const SDL_Color color_game_background = { 21, 108, 153, 1 };
const SDL_Color color_white = { 255, 255, 255, 1 };


// World
const string world_data_path = "maps/main.map";
const string world_texture_path = "images/maps/main_texture.png";
const int world_velocity = 250;
int grid_size = 32;


// Entity images
const string character_image_path = "images/char.png";
const int character_grid_size = 64;

const string tree_image_path = "images/trees.png";
const int tree_grid_size = 160;

const string ore_image_path = "images/ores.png";
const int ore_grid_size = 32;

const string monster_image_path = "images/beetle5.PNG";
// const int monster_grid_size = ?;


// Player
const int max_level = 50;
const uint32_t max_money = 2400000;

const int time_to_display_level_up_message = 3500;
