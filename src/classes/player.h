#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include<iostream>

#include "window.h"
#include "renderer.h"
#include "images.h"

using namespace std;

class Player
{
    private:
        Window* _win;
        Renderer* _ren;

        PNG* _character;
    
        int _hp = 10;
        uint32_t _money = 0;

        int _player_level = 1;
        int _player_xp = 0;

    public:
        Player(Window&, Renderer&);
        
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

        void increase_xp(int);
        void increase_level(int);

        void render();

};

#endif
