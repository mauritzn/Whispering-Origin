#include <iostream>
#include "images.h"
using namespace std;


BMP::BMP(Window& win, Renderer& ren, string path_to_image, int x, int y) {
  _win = &win;
  _ren = &ren;
  
  _bmp = SDL_LoadBMP(path_to_image.c_str());
  if(_bmp == NULL) {
    cout << "SDL_LoadBMP Error: " << SDL_GetError() << endl;
    SDL_Quit();
  } else {
    _width = _bmp->w;
    _height = _bmp->h;
    
    _tex = SDL_CreateTextureFromSurface(_ren->get(), _bmp);
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
    
    
    if(x == -50) x = ((_win->width() / 2) - (_width / 2));
    if(y == -50) y = ((_win->height() / 2) - (_height / 2));
    
    if(x == -100) x = (_win->width() - _width);
    if(y == -100) y = (_win->height() - _height);
    
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



int BMP::width() {
  return _width;
}

int BMP::height() {
  return _height;
}


void BMP::set_x(int x) {
  if(x == -50) x = ((_win->width() / 2) - (_width / 2));
  if(x == -100) x = (_win->width() - _width);
  
  // defines container position
  _dest_rect.x = x;
}

void BMP::set_y(int y) {
  if(y == -50) y = ((_win->height() / 2) - (_height / 2));
  if(y == -100) y = (_win->height() - _height);
  
  // defines container position
  _dest_rect.y = y;
}

int BMP::get_x() { return _dest_rect.x; }
int BMP::get_y() { return _dest_rect.y; }

void BMP::render() {
  SDL_RenderCopy(_ren->get(), _tex, &_src_rect, &_dest_rect);
}








PNG::PNG(Window& win, Renderer& ren, string path_to_image, int x, int y) {
  _win = &win;
  _ren = &ren;
  
  _png = IMG_Load(path_to_image.c_str());
  if(_png == NULL) {
    cout << "IMG_Load Error: " << IMG_GetError() << endl;
    SDL_Quit();
  } else {
    _width = _png->w;
    _height = _png->h;
    
    _tex = SDL_CreateTextureFromSurface(_ren->get(), _png);
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
    
    
    if(x == -50) x = ((_win->width() / 2) - (_width / 2));
    if(y == -50) y = ((_win->height() / 2) - (_height / 2));
    
    if(x == -100) x = (_win->width() - _width);
    if(y == -100) y = (_win->height() - _height);
    
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



int PNG::width() {
  return _width;
}

int PNG::height() {
  return _height;
}

void PNG::set_image_width(int new_width) { _src_rect.w = new_width; }
void PNG::set_image_height(int new_height) { _src_rect.h = new_height; }

void PNG::set_container_width(int new_width) { _dest_rect.w = new_width; }
void PNG::set_container_height(int new_height) { _dest_rect.h = new_height; }


void PNG::set_absolute_x(int x) {
  // defines image position
  _dest_rect.x = x;
}

void PNG::set_absolute_y(int y) {
  // defines image position
  _dest_rect.y = y;
}

void PNG::set_image_x(int x) { _src_rect.x = x; }
void PNG::set_image_y(int y) { _src_rect.y = y; }


void PNG::set_x(int x) {
  if(x == -50) x = ((_win->width() / 2) - (_width / 2));
  if(x == -100) x = (_win->width() - _width);
  
  // defines container position
  _dest_rect.x = x;
}

void PNG::set_y(int y) {
  if(y == -50) y = ((_win->height() / 2) - (_height / 2));
  if(y == -100) y = (_win->height() - _height);
  
  // defines container position
  _dest_rect.y = y;
}

int PNG::get_x() { return _dest_rect.x; }
int PNG::get_y() { return _dest_rect.y; }


void PNG::render() {
  SDL_RenderCopy(_ren->get(), _tex, &_src_rect, &_dest_rect);
}