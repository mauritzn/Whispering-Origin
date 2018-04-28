#ifndef WORLD_H
#define WORLD_H

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <map>

#include "window.h"
#include "renderer.h"
#include "images.h"
#include "../config.h"
#include "fps.h"
#include "player.h"
#include "text.h"
#include "tile.h"

using namespace std;

typedef Tile* TILE;
typedef vector<TILE> GRID;


class World {
  private:
    Window* _win;
    Renderer* _ren;
    FPS* _fps; // used to get delta time
    Player* _player; // (will be) used to change the player sprite




    vector<Text*> _debug_neighbor;




    PNG* _texture;
    float _x = 0;
    float _y = 0;

    int _map_width = 0;
    int _map_height = 0;

    bool _moving_up = false;
    bool _moving_down = false;
    bool _moving_left = false;
    bool _moving_right = false;
    bool _action_key_pressed = false;

    TILE _current_tile = NULL;
    vector<TILE> _neighbor_tiles = { NULL, NULL, NULL, NULL };

    GRID _tiles;

    vector<PNG*> _to_render;


  public:
    World(Window&, Renderer&, FPS&, Player&);

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


    void key_pressed(SDL_Keycode);
    void key_released(SDL_Keycode);

    void update();
    void render();
};

#endif
