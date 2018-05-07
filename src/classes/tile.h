#ifndef TILE_H
#define TILE_H

#include <string>

#include "game.h"
#include "image.h"
#include "text.h"
#include "progress_bar.h"
#include "../config.h"

using namespace std;


class Tile {
  private:
    Game* _game;

    Image* _tile_image;
    Text* _progress_text;
    Progress* _progress_bar;
    int _tile_grid_size;

    grid_tile_data _id;
    grid_tile_type _type;
    string _tile_name = "";

    int _original_x = 0;
    int _original_y = 0;

    int _x_start = 0;
    int _x_end = 0;
    int _y_start = 0;
    int _y_end = 0;

    int _row = 0;
    int _col = 0;
    string _row_and_col = "0x0";


    int _resources = 0; // how much resources can the player get from this tile (in total)
    int _resources_left = 0; // how many resources are left in this tile
    float _resource_percentage = 100.0; // what is the percentage of getting one resource (when 0 give 1 resource, and reset to 100%) [0-100]%

    uint32_t _depleted_at = 0; // used to see if an tile has depleted all it's resources and when it happend (-1 = not depleted, > 0 = depleted)
    uint32_t _last_action_at = 0; // used to see when an action was last taken (will be used for timing the deplition)


  public:
    Tile(Game&, const grid_tile_data&, int, int);

    int width(); // get the tile's width
    int height(); // get the tile's height

    int x_start(); // get the x value where the tile starts
    int x_end(); // get the x value where the tile ends

    int y_start(); // get the y value where the tile starts
    int y_end(); // get the y value where the tile ends


    int original_x(); // get the tile's creation x value
    int original_y(); // get the tile's creation y value

    int x(); // get the tile image's x value
    int y(); // get the tile image's y value
    void x(int); // set the tile image's x value
    void y(int); // set the tile image's y value



    int row(); // get the tile's row
    int col(); // get the tile's col
    void row(int); // set the tile's row
    void col(int); // set the tile's col

    string row_and_col(); // get the tile's row and col, ROWxCOL


    grid_tile_data id(); // get the tile's ID
    grid_tile_type type(); // get the tile's type
    string tile_name(); // get the name of the tile


    void action(); // do action on tile
    bool action_on_cooldown(); // check if another action can be done on the tile
    void show_progress(); // show progress above the tile

    void update(); // refresh resources after depletion, update countdown, update resources left text
    void render(); // render the tile's image
};

#endif
