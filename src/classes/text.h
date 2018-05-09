#ifndef TEXT_H
#define TEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <string>
#include "game.h"
using namespace std;


class Text {
  private:
    Game* _game;

    SDL_Surface* _surface;
    SDL_Texture* _tex;

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
    Text(Game&, TTF_Font*, SDL_Color, string, int, int);
    ~Text(); // free the textures when the object is destroyed


    void update(string); // change the text value

    int width(); // get the text's width
    int height(); // get the text's height

    // also sets alignment, this keeps it aligned properly when the text is updated
    void align_center(); // set x & y to the center of the screen
    void align_center_x(); // set x to the center of the screen
    void align_center_y(); // set y to the center of the screen

    void align_top(); // set y to the top of the screen
    void align_bottom(); // set y to the bottom of the screen
    void align_left(); // set x to the left of the screen
    void align_right(); // set x to the right of the screen


    int x(); // get the texts x position
    int y(); // get the texts y position

    void x(int); // set the texts x position
    void y(int); // set the texts y position

    void render(); // render the text to the renderer (-> window)
};

#endif