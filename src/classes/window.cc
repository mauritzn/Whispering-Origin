#include <iostream>
#include "window.h"


Window::Window(string title, int x, int y, int width, int height) {
  _width = width;
  _height = height;
  
  _win = SDL_CreateWindow(title.c_str(), x, y, _width, _height, SDL_WINDOW_SHOWN);
  
  
  if(_win == NULL) {
    cout << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
    SDL_Quit();
  }
}

Window::~Window() {
  SDL_DestroyWindow(_win);
}


SDL_Window* Window::get() {
  return _win;
}


int Window::width() {
  return _width;
}

int Window::height() {
  return _height;
}