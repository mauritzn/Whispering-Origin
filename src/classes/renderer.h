#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include "window.h"


class Renderer {
  private:
    SDL_Renderer* _ren;

  public:
    Renderer(Window&, SDL_Color);
    ~Renderer();
    
    SDL_Renderer* get();
    
    void clear();
    void update();
};

#endif