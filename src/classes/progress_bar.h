#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H

#include <SDL2/SDL.h>
#include "game.h"

using namespace std;


class Progress {
  private:
    Game* _game;

    int _border_size = 1;
    int _progress = 0; // 0-100

    SDL_Color _bar_color;
    SDL_Color _background_color = { 255, 255, 255, 255 };
    SDL_Color _border_color = { 0, 0, 0, 255 };

    int _original_x;
    int _original_y;

    SDL_Rect _bar_rect;
    SDL_Rect _background_rect;
    SDL_Rect _border_rect;


  public:
    Progress(Game&, SDL_Color, int, int, int, int);

    int width(); // get the progress bar's width
    int height(); // get the progress bar's height
    void width(int); // set the progress bar's width
    void height(int); // set the progress bar's height

    int border_size(); // get the progress bar's border size
    void border_size(int); // set the progress bar's border size


    SDL_Color bar_color(); // get the progress color
    SDL_Color background_color(); // get the progress bar's background color
    SDL_Color border_color(); // get the progress bar's border color

    void bar_color(SDL_Color); // set the progress color
    void background_color(SDL_Color); // set the progress bar's background color
    void border_color(SDL_Color); // set the progress bar's border color


    int original_x(); // get the progress bar's creation x value
    int original_y(); // get the progress bar's creation y value

    int x(); // get the progress bar's x value
    int y(); // get the progress bar's y value
    void x(int); // set the progress bar's x value
    void y(int); // set the progress bar's y value


    int progress(); // get the progress bar's progress (0-100)
    void progress(int); // set the progress bar's progress (0-100)


    void render(); // render the progress bar
};

#endif
