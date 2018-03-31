#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <vector>

#include "window.h"
#include "images.h"
#include "world.h"

using namespace std;


extern int constrain(int, int, int);

extern int constrain_png_width(int, Window&, PNG&);
extern int constrain_png_height(int, Window&, PNG&);


extern string format_number(int);
extern string to_fixed(float);


extern vector<string> explode_string(string const&, char);

extern void add_cell_to_grid(string const&, GRID&);


#endif