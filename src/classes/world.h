#ifndef WORLD_H
#define WORLD_H

#include <SDL2/SDL.h>

#include "window.h"
#include "renderer.h"
#include "images.h"
#include "fps.h"
#include "player.h"

using namespace std;


class World {
  private:
    Window* _win;
    Renderer* _ren;
    FPS* _fps; // used to get delta time
    Player* _player; // (will be) used to change the player sprite

    PNG* _texture;
    float _x = 0;
    float _y = 0;
    int _grid_size = 32;
    
    bool _moving_up = false;
    bool _moving_down = false;
    bool _moving_left = false;
    bool _moving_right = false;


  public:
    World(Window&, Renderer&, FPS&, Player&);
    
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