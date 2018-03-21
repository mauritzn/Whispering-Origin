#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <string>
using namespace std;


class Window {
  private:
    SDL_Window* _win;
    int _width = 0;
    int _height = 0;

  public:
    Window(string title, int x, int y, int width, int height) {
      _width = width;
      _height = height;
      
      _win = SDL_CreateWindow(title.c_str(), x, y, _width, _height, SDL_WINDOW_SHOWN);
      
      
      if(_win == NULL) {
        cout << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
        SDL_Quit();
      }
    }
    
    ~Window() {
      SDL_DestroyWindow(_win);
    }
    
    
    SDL_Window* get() {
      return _win;
    }
    
    
    int width() {
      return _width;
    }
    
    int height() {
      return _height;
    }
};