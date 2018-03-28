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
        int _x;
        int _y;

        int _hp = 10;
        uint32_t _money = 0;

    public:
        Player(Window&, Renderer&);
        
        int get_x();
        int get_y();
        void set_x(int);
        void set_y(int);
        
        int health();
        uint32_t money();

        void heal(int);
        void damage(int);
        bool is_alive();

        void increase_money(int);
        void decrease_money(int);
        void set_money(int);

        void render();
        ~Player();
}

