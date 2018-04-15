#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <vector>

#include "window.h"
#include "images.h"
#include "fps.h"
#include "player.h"
#include "world.h"

using namespace std;


extern int constrain(int, int, int);

extern int constrain_png_width(int, Window&, PNG&);
extern int constrain_png_height(int, Window&, PNG&);


extern string format_number(int);
extern string to_fixed(float);


extern vector<string> explode_string(const string&, char);

extern string combine_row_and_col(int, int);
//extern void add_tile_to_grid(const string&, const tile_type&, GRID&);

extern bool init_SDL();
extern void init_game();

extern void init_debug_info_position(const map<string, Text*>&);
extern void update_debug_info(map<string, Text*>&, FPS&, Player&, World&);
extern void render_debug_info(const map<string, Text*>&);

#endif