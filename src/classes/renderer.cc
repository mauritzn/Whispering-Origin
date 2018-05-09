#include <iostream>
#include "renderer.h"
using namespace std;


Renderer::Renderer(Window& win, SDL_Color bg_color) {
  _ren = SDL_CreateRenderer(win.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if(_ren == NULL) {
    cout << "SDL_CreateRenderer Error: " << SDL_GetError() << endl;
    SDL_Quit();
  } else {
    SDL_SetRenderDrawColor(_ren, bg_color.r, bg_color.g, bg_color.b, 255);
  }
}

Renderer::~Renderer() {
  SDL_DestroyRenderer(_ren);
}


SDL_Renderer* Renderer::get() {
  return _ren;
}


void Renderer::clear() {
  SDL_RenderClear(_ren); // clear the renderer
}

void Renderer::update() {
  SDL_RenderPresent(_ren); // update the screen
}