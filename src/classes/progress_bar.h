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
    SDL_Color _background_color = { 255, 255, 255 };
    SDL_Color _border_color = { 0, 0, 0 };

    int _original_x;
    int _original_y;

    SDL_Rect _bar_rect;
    SDL_Rect _background_rect;
    SDL_Rect _border_rect;


  public:
    Progress(Game&, SDL_Color, int, int, int, int);

    int width();
    int height();

    void width(int);
    void height(int);

    int border_size();
    void border_size(int);


    SDL_Color bar_color();
    SDL_Color background_color();
    SDL_Color border_color();

    void bar_color(SDL_Color);
    void background_color(SDL_Color);
    void border_color(SDL_Color);


    int original_x();
    int original_y();

    int x();
    int y();
    void x(int);
    void y(int);


    void progress(int);
    int progress();


    void render();
};

#endif
