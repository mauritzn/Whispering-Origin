/* Character.h as Player class */
#ifndef CHARACTER_H
#define CHARACTER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>
#include <iostream>
#include "window.h"
#include "renderer.h"

using namespace std;

class Character 
{
    private:
        Window* _win;
        Renderer* _ren;

        SDL_Surface* _bmp;
        SDL_Texture* _tex;

        int _health;
        int _char_exp;
        int _level;
        int _money;
    
    public:
        // Constructor
        Character(Window&, Renderer&);
        // Destructor
        // more functions to come.
        int exp_left();
        int health();
        int char_exp();
        int level();
        int money();
};

#endif
