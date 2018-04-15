#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include<iostream>
#include <vector>

#include "window.h"
#include "renderer.h"
#include "images.h"

using namespace std;

enum player_direction {
  NORTH = 0,
  SOUTH = 128,
  WEST = 64,
  EAST = 192
};

class Player {
  private:
    Window* _win;
    Renderer* _ren;

    PNG* _character;
    
    int _hp = 10;
    uint32_t _money = 0;
    int _acc = 7;   // Player Accuracy
    

    uint32_t _leveled_up_at = 0;
    int _player_level = 1;
    int _player_xp = 0;


  public:
    Player(Window&, Renderer&);
    
    int get_x();
    int get_y();
    
    void set_x(int);
    void set_y(int);
    
    
    player_direction get_direction();
    void set_direction(player_direction);
    
    int health();
    uint32_t money();
    int level();
    int xp();

    void heal(int);
    void damage(int);
    bool is_alive();

    void increase_money(int);
    void decrease_money(int);
    void set_money(int);

    int xp_to_level();
    void increase_xp(int);
    bool has_leveled_up();

    void render();
};

#endif