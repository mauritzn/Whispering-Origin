#ifndef WORLD_H
#define WORLD_H

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <map>

#include "window.h"
#include "renderer.h"
#include "images.h"
#include "fps.h"
#include "player.h"

using namespace std;

enum tile_type {
  COLLIDER,
  TREE,
  ORE,
  FISH,
  GRASS
};

enum tree_state {
  UNCUT = 0,
  CUT = 160
};

enum tree_type {
  OAK = 0
};

struct grid_tile {
  string row_and_col;
  
  int row;
  int col;
  
  tile_type type;
  int id;
};

typedef struct grid_tile TILE;
typedef vector<TILE> GRID;
typedef map<string, const TILE*> COLLISIONS;
  

class World {
  private:
    Window* _win;
    Renderer* _ren;
    FPS* _fps; // used to get delta time
    Player* _player; // (will be) used to change the player sprite

    PNG* _texture;
    float _x = 0;
    float _y = 0;
    
    int _map_width = 0;
    int _map_height = 0;
    int _grid_size = 0;
    
    bool _moving_up = false;
    bool _moving_down = false;
    bool _moving_left = false;
    bool _moving_right = false;
    
    TILE current_tile;
    
    GRID _colliders;
    GRID _trees;
    GRID _ores;
    GRID _fish;
    
    COLLISIONS _collisions;
    
    vector<PNG*> _trees_to_render;


  public:
    World(Window&, Renderer&, FPS&, Player&);
    
    int width();
    int height();
    int grid_size();
    
    int get_x();
    int get_y();
    
    void set_x(int);
    void set_y(int);
    
    
    int get_player_x();
    int get_player_y();
    
    int get_player_row();
    int get_player_col();
    string get_player_row_and_col();
    
    
    void key_pressed(SDL_Keycode);
    void key_released(SDL_Keycode);
    
    void update();
    void render();
};

#endif