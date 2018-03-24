#ifndef TEXT_H
#define TEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <string>
#include "window.h"
#include "renderer.h"
using namespace std;


class Text {
  private:
    SDL_Surface* _surface;
    SDL_Texture* _text;
    
    TTF_Font* _font;
    SDL_Color _color;
    
    // -1 = left, 0 = center, 1 = right
    int _x_alignment = -1;
    int _y_alignment = -1;
    
    int _x = 0;
    int _y = 0;
    int _width = 0;
    int _height = 0;
    
    SDL_Rect _src_rect;
    SDL_Rect _dest_rect;

    
  public:
    Text(Window&, Renderer&, TTF_Font*, SDL_Color, string, int, int);
    ~Text();
    
    
    SDL_Texture* get();
    SDL_Rect& dest_rect();
    
    void update(Renderer& ren, string text);
    
    void set_x(Window& win, int x);
    void set_y(Window& win, int y);
    
    int get_x();
    int get_y();
    
    void render(Renderer& ren);
};

#endif