#ifndef WORLD_H
#define WORLD_H

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <map>

#include "game.h"
#include "image.h"
#include "text.h"
#include "tile.h"
#include "../config.h"

using namespace std;

typedef Tile* TILE;
typedef vector<TILE> GRID;


class World {
  private:
    Game* _game;
    Image* _texture;

    float _x = 0;
    float _y = 0;

    int _map_width = 0;
    int _map_height = 0;

    TILE _current_tile = NULL;
    vector<TILE> _neighbor_tiles;
    vector<Text*> _debug_neighbors;
    GRID _tiles;

    vector<Image*> _to_render;


  public:
    World(Game&);

    int width(); // get the world's width
    int height(); // get the world's height

    int x(); // get the world's x
    int y(); // get the world's y
    void x(int); // set the world's x
    void y(int); // set the world's y


    int player_x(); // get the player's x
    int player_y(); // get the player's y

    int player_row(); // get the player's row
    int player_col(); // get the player's col
    string player_row_and_col(); // get the player's row and col, ROWxCOL


    void add_to_grid(const string&); // create tile and add to grid


    void update_current_tile(); // change the value of the current tile (row, col)
    void update_neighbors(); // get all the neighbors around the current tile

    void update(); // handles player movments, player actions, collisions
    void render(); // render the world's texture, player, tile images, tile progress
};

#endif
