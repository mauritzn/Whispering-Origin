#ifndef IMAGES_H
#define IMAGES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>
#include "window.h"
#include "renderer.h"


class BMP {
  private:
    Window* _win;
    Renderer* _ren;
    
    SDL_Surface* _bmp;
    SDL_Texture* _tex;
    
    SDL_Rect _src_rect;
    SDL_Rect _dest_rect;
    
    int _width = 0;
    int _height = 0;

    
  public:
    BMP(Window&, Renderer&, string, int, int);
    ~BMP();
    
    
    SDL_Texture* get();
    
    int width();
    int height();
    
    SDL_Rect& src_rect();
    SDL_Rect& dest_rect();
    
    void set_x(int);
    void set_y(int);
    
    int get_x();
    int get_y();
    
    void render();
};







class PNG {
  private:
    Window* _win;
    Renderer* _ren;
    
    SDL_Surface* _png;
    SDL_Texture* _tex;
    
    SDL_Rect _src_rect;
    SDL_Rect _dest_rect;
    
    int _width = 0;
    int _height = 0;

    
  public:
    PNG(Window&, Renderer&, string, int, int);
    ~PNG();
    
    
    SDL_Texture* get();
    
    int width();
    int height();
    
    SDL_Rect& src_rect();
    SDL_Rect& dest_rect();
    
    void set_x(int);
    void set_y(int);
    
    int get_x();
    int get_y();
    
    void render();
};

#endif