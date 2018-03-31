#ifndef WORLD_H
#define WORLD_H

#include <SDL2/SDL.h>

#include "window.h"
#include "renderer.h"
#include "images.h"
#include "fps.h"
#include "player.h"

using namespace std;

enum tree_state {
  UNCUT = 0,
  CUT = 160
};

struct grid_cell {
  int row;
  int col;
  int id;
};

typedef struct grid_cell CELL;
typedef vector<CELL> GRID;
  

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
    
    GRID _colliders;
    GRID _trees;
    GRID _ores;
    GRID _fish;
    
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
    
    
    void key_pressed(SDL_Keycode);
    void key_released(SDL_Keycode);
    
    void update();
    void render();
};

#endif