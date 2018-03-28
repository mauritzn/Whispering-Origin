/*
 * The ultimate config file for main.cc
 * char*  => used for options passed directly to SDL functions
 * string => used for options passed to class constructors
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <string>
using namespace std;


// General
extern const int window_width; // define the window's width created by SDL
extern const int window_height; // define the window's height created by SDL

extern const char* game_name; // define the title of the game (will display in the window's title bar)
extern const char* icon_path; // define where the icon image is stored (icon will show in the taskbar) [PNG]

extern bool debug_mode; // define if debug mode should be on by default


// Fonts
extern const char* main_font; // define where the main font is stored [TTF]


// World
extern const string world_texture_path; // define where the main world's texture image is stored [PNG]
extern const int velocity; // defines how fast the world moves around


// Entity images
extern const char* character_image_path; // define where the player's character image is stored [PNG]
extern const char* tree_image_path; // define where the TEMP tree image is stored [PNG]


// Player
extern const int max_level; // define how far the player can level
extern const uint32_t max_money; // define how much money the player can have


#endif