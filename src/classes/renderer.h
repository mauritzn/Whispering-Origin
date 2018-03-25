#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include "window.h"


class Renderer {
  private:
    SDL_Renderer* _ren;

  public:
    Renderer(Window&, SDL_Color);
    ~Renderer(); // free the SDL_Renderer instance when the object is destroyed
    
    SDL_Renderer* get(); // get the SDL_Renderer instance
    
    void clear();  // clear the renderer
    void update(); // update the screen
};

#endif