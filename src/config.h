/*
 * The ultimate config file for main.cc
 * char*  => used for options passed directly to SDL functions
 * string => used for options passed to class constructors
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>
#include <map>
using namespace std;


enum grid_tile_type {
  COLLIDER = 0,
  TREE = 10,
  ORE = 20,
  FISH = 30
};

enum grid_tile_data {
  TREE_OAK = 1000,
  ORE_COPPER = 2000,
  FISH_SALMON = 3000
};


typedef map<grid_tile_data, grid_tile_type> TILE_DATA;
typedef map<grid_tile_data, string> TILE_NAMES;

extern const vector<grid_tile_type> grid_tile_types;
extern const TILE_DATA grid_tiles;
extern const TILE_NAMES grid_tile_names;


enum neighbor_direction {
  N_NORTH,
  N_NORTH_EAST,
  N_EAST,
  N_SOUTH_EAST,
  N_SOUTH,
  N_SOUTH_WEST,
  N_WEST,
  N_NORTH_WEST
};

enum tree_state {
  UNCUT = 0,
  CUT = 160
};

enum tree_type {
  OAK = 0
};


enum player_direction {
  NORTH = 0,
  SOUTH = 128,
  WEST = 64,
  EAST = 192
};


enum inventory_slot_positions {
  TOOL_1 = 300,
  TOOL_2 = 342,
  TOOL_3 = 384,
  TOOL_4 = 426,

  SLOT_1 = 475,
  SLOT_2 = 517,
  SLOT_3 = 559,
  SLOT_4 = 601,
  SLOT_5 = 643,
  SLOT_6 = 685,
  SLOT_7 = 727,
  SLOT_8 = 769,
  SLOT_9 = 811,
  SLOT_10 = 853,
  SLOT_11 = 895,
  SLOT_12 = 937
};

extern const vector<inventory_slot_positions> inv_slot_pos;


enum items {
  I_OAK_LOG,
  I_COPPER_ORE,
  I_SALMON
};

struct pos_xy {
  int x = 0;
  int y = 0;
};

typedef map<grid_tile_data, items> TILE_DROPS;
typedef map<items, string> ITEM_NAMES;
typedef map<items, pos_xy> ITEM_POS;
extern const TILE_DROPS grid_tile_drops;
extern const ITEM_NAMES item_names;
extern const ITEM_POS item_pos;


enum skill_anchor {
  PLAYER_SKILL,
  WOODCUTTING_SKILL,
  MINING_SKILL,
  SMITHING_SKILL,
  FISHING_SKILL,
  COOKING_SKILL
};



// General
extern const int window_width; // define the window's width created by SDL
extern const int window_height; // define the window's height created by SDL

extern const char* game_name; // define the title of the game (will display in the window's title bar)
extern const char* icon_path; // define where the icon image is stored (icon will show in the taskbar) [Image]

extern bool debug_mode; // define if debug mode should be on by default

extern const int debug_info_x_start;
extern const int debug_info_y_start;
extern const int debug_info_y_padding;

extern const int SDL_image_flags;

extern vector<int> xp_rates;
extern const vector<string> dir_text;


// UI
extern const string base_ui_image_path;
extern const string active_slot_image_path;


// Fonts
extern const bool anti_aliased_font;
extern const char* main_font_path; // define where the main font is stored [TTF]
extern map<string, TTF_Font*> fonts;


// Colors
extern const SDL_Color color_game_background;
extern const SDL_Color color_white;


// World
extern const string world_data_path; // define where the main world's data is stored [MAP]
extern const string world_texture_path; // define where the main world's texture image is stored [Image]
extern const int world_velocity; // defines how fast the world moves around
extern int grid_size; // defines the world default grid size


// Entity images
extern const string character_image_path; // define where the player's character image is stored [Image]
extern const int character_grid_size; // define how big one character image is (used for sprites)

extern const string tree_image_path; // define where the tree image is stored [Image]
extern const int tree_grid_size; // define how big one tree image is (used for sprites)

extern const string ore_image_path;
extern const int ore_grid_size;


// Player
extern const int max_level; // define how far the player can level
extern const uint32_t max_money; // define how much money the player can have
extern const int max_item_stack;

extern const int time_to_display_level_up_message; // define how long the level up message should be shown (in milliseconds)


// Items
extern const string items_image_path;
extern const int item_grid_size;


#endif
