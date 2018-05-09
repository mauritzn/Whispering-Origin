#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <string>
using namespace std;


class Window {
  private:
    SDL_Window* _win;
    int _width = 0;
    int _height = 0;

  public:
    Window(string, int, int, int, int);
    ~Window(); // free the SDL_Window instance when the object is destroyed


    SDL_Window* get(); // get the SDL_Window instance

    int width();  // get the windows width
    int height(); // get the windows height
};

#endif