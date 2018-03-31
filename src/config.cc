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
const char* main_font = "fonts/Ubuntu_C.ttf";


// World
const string world_data_path = "maps/main.map";
const string world_texture_path = "images/maps/main_texture.png";
const int world_velocity = 250;


// Entity images
const string character_image_path = "images/char.png";
const int character_grid_size = 64;
const string tree_image_path = "images/tree.png";


// Player
const int max_level = 50;
const uint32_t max_money = 2400000;

const int time_to_display_level_up_message = 3500;