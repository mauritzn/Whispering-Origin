#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "image.h"
#include "functions.h"
using namespace std;

Image::Image(Window& win, Renderer& ren, string path_to_image, int x, int y) {
  _win = &win;
  _ren = &ren;

  vector<string> path_exploded = explode_string(path_to_image, '.');
  string ext = path_exploded.back();
  transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

  if(ext == "bmp") _img = SDL_LoadBMP(path_to_image.c_str());
  else if(ext == "png" || ext == "jpg") {
    _img = IMG_Load(path_to_image.c_str());
  }

  if(_img == NULL) {
    if(ext == "bmp") cout << "SDL_LoadBMP Error: " << SDL_GetError() << endl;
    else cout << "IMG_Load Error: " << IMG_GetError() << endl;
    SDL_Quit();
  } else {
    _width = _img->w;
    _height = _img->h;

    _tex = SDL_CreateTextureFromSurface(_ren->get(), _img);
    SDL_FreeSurface(_img);
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

    // TEMP (only used until ITEM class is completed)
    _original_x = x;
    _original_y = y;

    // defines container positions
    _dest_rect.x = x;
    _dest_rect.y = y;

    _dest_rect.w = _width;
    _dest_rect.h = _height;
  }
}

Image::~Image() {
  SDL_DestroyTexture(_tex);
}



int Image::width() {
  return _width;
}

int Image::height() {
  return _height;
}

void Image::image_width(int new_width) { _src_rect.w = new_width; }
void Image::image_height(int new_height) { _src_rect.h = new_height; }

void Image::container_width(int new_width) {
  _width = new_width;
  _dest_rect.w = new_width;
}
void Image::container_height(int new_height) {
  _height = new_height;
  _dest_rect.h = new_height;
}



void Image::align_center() {
  // defines container positions
  _dest_rect.x = ((_win->width() / 2) - (_width / 2));
  _dest_rect.y = ((_win->height() / 2) - (_height / 2));
}
void Image::align_center_x() {
  // defines container position
  _dest_rect.x = ((_win->width() / 2) - (_width / 2));
}
void Image::align_center_y() {
  // defines container position
  _dest_rect.y = ((_win->height() / 2) - (_height / 2));
}

void Image::align_top() {
  // defines container position
  _dest_rect.y = 0;
}

void Image::align_bottom() {
  // defines container position
  _dest_rect.y = (_win->height() - _height);
}

void Image::align_left() {
  // defines container position
  _dest_rect.x = 0;
}

void Image::align_right() {
  // defines container position
  _dest_rect.x = (_win->width() - _width);
}



void Image::image_x(int x) { _src_rect.x = x; }
void Image::image_y(int y) { _src_rect.y = y; }


int Image::x() { return _dest_rect.x; }
int Image::y() { return _dest_rect.y; }

void Image::x(int x) { _dest_rect.x = x; }
void Image::y(int y) { _dest_rect.y = y; }


int Image::image_x() { return _src_rect.x; }
int Image::image_y() { return _src_rect.y; }

int Image::original_x() { return _original_x; }
int Image::original_y() { return _original_y; }


void Image::render() {
  SDL_RenderCopy(_ren->get(), _tex, &_src_rect, &_dest_rect);
}
