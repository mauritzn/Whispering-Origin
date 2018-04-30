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

    int width();
    int height();

    int x();
    int y();

    void x(int);
    void y(int);


    int player_x();
    int player_y();


    int player_row();
    int player_col();
    string player_row_and_col();


    void add_to_grid(const string&);


    void update_current_tile();
    void update_neighbors();

    void update();
    void render();
};

#endif
