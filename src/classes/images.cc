#include <iostream>
#include "images.h"
using namespace std;


BMP::BMP(Window& win, Renderer& ren, string path_to_image, int x, int y) {
  _bmp = SDL_LoadBMP(path_to_image.c_str());
  if(_bmp == NULL) {
    cout << "SDL_LoadBMP Error: " << SDL_GetError() << endl;
    SDL_Quit();
  } else {
    _width = _bmp->w;
    _height = _bmp->h;
    
    _tex = SDL_CreateTextureFromSurface(ren.get(), _bmp);
    SDL_FreeSurface(_bmp);
  }
  
  if(_tex == NULL) {
    cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << endl;
    SDL_Quit();
  } else {
    // defines image position
    _src_rect.x = 0;
    _src_rect.y = 0;
    _src_rect.w = _width;
    _src_rect.h = _height;
    
    
    if(x == -50) x = ((win.width() / 2) - (_width / 2));
    if(y == -50) y = ((win.height() / 2) - (_height / 2));
    
    if(x == -100) x = (win.width() - _width);
    if(y == -100) y = (win.height() - _height);
    
    // defines container positions
    _dest_rect.x = x;
    _dest_rect.y = y;
    
    _dest_rect.w = _width;
    _dest_rect.h = _height;
  }
}

BMP::~BMP() {
  SDL_DestroyTexture(_tex);
}


SDL_Texture* BMP::get() {
  return _tex;
}


int BMP::width() {
  return _width;
}

int BMP::height() {
  return _height;
}


SDL_Rect& BMP::src_rect() {
  return _src_rect;
}

SDL_Rect& BMP::dest_rect() {
  return _dest_rect;
}

void BMP::set_x(Window& win, int x) {
  if(x == -50) x = ((win.width() / 2) - (_width / 2));
  if(x == -100) x = (win.width() - _width);
  
  // defines container position
  _dest_rect.x = x;
}

void BMP::set_y(Window& win, int y) {
  if(y == -50) y = ((win.height() / 2) - (_height / 2));
  if(y == -100) y = (win.height() - _height);
  
  // defines container position
  _dest_rect.y = y;
}

int BMP::get_x() { return _dest_rect.x; }
int BMP::get_y() { return _dest_rect.y; }

void BMP::render(Renderer& ren) {
  SDL_RenderCopy(ren.get(), _tex, &_src_rect, &_dest_rect);
}








PNG::PNG(Window& win, Renderer& ren, string path_to_image, int x, int y) {
  _png = IMG_Load(path_to_image.c_str());
  if(_png == NULL) {
    cout << "IMG_Load Error: " << IMG_GetError() << endl;
    SDL_Quit();
  } else {
    _width = _png->w;
    _height = _png->h;
    
    _tex = SDL_CreateTextureFromSurface(ren.get(), _png);
    SDL_FreeSurface(_png);
  }
  
  if(_tex == NULL) {
    cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << endl;
    SDL_Quit();
  } else {
    // defines image position
    _src_rect.x = 0;
    _src_rect.y = 0;
    _src_rect.w = _width;
    _src_rect.h = _height;
    
    
    if(x == -50) x = ((win.width() / 2) - (_width / 2));
    if(y == -50) y = ((win.height() / 2) - (_height / 2));
    
    if(x == -100) x = (win.width() - _width);
    if(y == -100) y = (win.height() - _height);
    
    // defines container positions
    _dest_rect.x = x;
    _dest_rect.y = y;
    
    _dest_rect.w = _width;
    _dest_rect.h = _height;
  }
}

PNG::~PNG() {
  SDL_DestroyTexture(_tex);
}


SDL_Texture* PNG::get() {
  return _tex;
}


int PNG::width() {
  return _width;
}

int PNG::height() {
  return _height;
}


SDL_Rect& PNG::src_rect() {
  return _src_rect;
}

SDL_Rect& PNG::dest_rect() {
  return _dest_rect;
}

void PNG::set_x(Window& win, int x) {
  if(x == -50) x = ((win.width() / 2) - (_width / 2));
  if(x == -100) x = (win.width() - _width);
  
  // defines container position
  _dest_rect.x = x;
}

void PNG::set_y(Window& win, int y) {
  if(y == -50) y = ((win.height() / 2) - (_height / 2));
  if(y == -100) y = (win.height() - _height);
  
  // defines container position
  _dest_rect.y = y;
}

int PNG::get_x() { return _dest_rect.x; }
int PNG::get_y() { return _dest_rect.y; }

void PNG::render(Renderer& ren) {
  SDL_RenderCopy(ren.get(), _tex, &_src_rect, &_dest_rect);
}