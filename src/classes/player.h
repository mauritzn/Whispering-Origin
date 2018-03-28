#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include<iostream>

#include "window.h"
#include "renderer.h"

using namespace std;

class Player
{
    private:
        Window* _win;
        Renderer* _ren;

        SDL_Surface* _bmp;
        SDL_Texture* _tex;

    public:
        Player(Window&, Renderer&);
        
        ~Player();
}

