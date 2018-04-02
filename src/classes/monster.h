#ifndef MONSTER_H
#define MONSTER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>

#include "window.h"
#include "renderer.h"
#include "images.h"


using namespace std;

class Monster
{
    private:
        Window* _win;
        Renderer* _ren;

        PNG* _monster;

        int _hp;
        uint32_t reward_money = 10;
        int _acc;
        int _level;
        int _min_dmg;
        int _max_dmg;

    public:
        Monster(Window&, Renderer&);
       
        bool is_alive();
        int deal_damage();
        void take_damage(int);
        int give_reward();

        
        // For debugging purposes.
        void set_damage(int, int);
        void set_level(int);
        void set_accuracy(int);
        
        int get_level();
        int get_accuracy();
        
        void render();
};

#endif
