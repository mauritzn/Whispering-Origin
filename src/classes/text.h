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
    Window* _win;
    Renderer* _ren;
    
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
    ~Text(); // free the textures when the object is destroyed
    
    
    void update(string); // change the text value
    
    int width();
    int height();
    
    void align_center();
    void align_center_x();
    void align_center_y();

    void align_top();
    void align_bottom();
    void align_left();
    void align_right();
    
    
    void set_x(int); // set the texts x position
    void set_y(int); // set the texts y position
    
    int get_x(); // get the texts x position
    int get_y(); // get the texts y position
    
    void render(); // render the text to the renderer (-> window)
};

#endif