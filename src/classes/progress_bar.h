#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H

#include <SDL2/SDL.h>

#include "window.h"
#include "renderer.h"

using namespace std;


class Progress {
  private:
    Window* _win;
    Renderer* _ren;
    
    int _border_size = 1;
    int _progress = 0; // 0-100
    
    SDL_Color _bar_color;
    SDL_Color _background_color = { 255, 255, 255 };
    SDL_Color _border_color = { 0, 0, 0 };
    
    int _original_x;
    int _original_y;
    
    SDL_Rect _bar_rect;
    SDL_Rect _background_rect;
    SDL_Rect _border_rect;


  public:
    Progress(Window&, Renderer&, SDL_Color, int, int, int, int);
    
    int width();
    int height();
    
    void set_width(int);
    void set_height(int);
    
    int border_size();
    void set_border_size(int);
    
    
    SDL_Color get_bar_color();
    SDL_Color get_background_color();
    SDL_Color get_border_color();
    
    void set_bar_color(SDL_Color);
    void set_background_color(SDL_Color);
    void set_border_color(SDL_Color);
    
    
    int get_original_x();
    int get_original_y();
    
    int get_x();
    int get_y();
    
    void set_x(int);
    void set_y(int);
    
    
    void set_progress(int);
    int get_progress();
    
    
    void render();
};

#endif