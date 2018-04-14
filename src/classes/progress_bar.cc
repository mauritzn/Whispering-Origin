#include <SDL2/SDL.h>

#include <iostream>

#include "progress_bar.h"
#include "functions.h"
#include "../config.h"

using namespace std;


Progress::Progress(Window& win, Renderer& ren, SDL_Color bar_color, int width, int height, int x, int y) {
  _win = &win;
  _ren = &ren;
  
  _bar_color = bar_color;
  
  _original_x = x;
  _original_y = y;
  
  
  this->set_x(_original_x);
  this->set_y(_original_y);
  
  this->set_width(width);
  this->set_height(height);
}



int Progress::width() { return _background_rect.w; }
int Progress::height() { return _background_rect.h; }

void Progress::set_width(int new_width) {
  _border_rect.w = new_width;
  _background_rect.w = (_border_rect.w - (_border_size * 2));
  _bar_rect.w = _background_rect.w * ((float) _progress / 100.0);
}

void Progress::set_height(int new_height) {
  _border_rect.h = new_height;
  _background_rect.h = (_border_rect.h - (_border_size * 2));
  _bar_rect.h = _background_rect.h;
}


int Progress::border_size() { return _border_size; }

void Progress::set_border_size(int new_size) {
  _border_size = new_size;
  
  // update width, height, x, y
  this->set_width(this->width());
  this->set_height(this->height());
  
  this->set_x(this->get_x());
  this->set_y(this->get_y());
}


SDL_Color Progress::get_bar_color() { return _bar_color; }
SDL_Color Progress::get_background_color() { return _background_color; }
SDL_Color Progress::get_border_color() { return _border_color; }

void Progress::set_bar_color(SDL_Color new_color) {
  _bar_color = new_color;
}

void Progress::set_background_color(SDL_Color new_color) {
  _background_color = new_color;
}

void Progress::set_border_color(SDL_Color new_color) {
  _border_color = new_color;
}


int Progress::get_original_x() { return _original_x; }
int Progress::get_original_y() { return _original_y; }

int Progress::get_x() { return _border_rect.x; }
int Progress::get_y() { return _border_rect.y; }

void Progress::set_x(int new_x) {
  _border_rect.x = new_x;
  _background_rect.x = (_border_rect.x + _border_size);
  _bar_rect.x = _background_rect.x;
}
void Progress::set_y(int new_y) {
  _border_rect.y = new_y;
  _background_rect.y = (_border_rect.y + _border_size);
  _bar_rect.y = _background_rect.y;
}


void Progress::set_progress(int new_progress) {
  _progress = constrain(new_progress, 0, 100);
  _bar_rect.w = _background_rect.w * ((float) _progress / 100.0);
}

int Progress::get_progress() {
  return _progress;
}


void Progress::render() {
  SDL_SetRenderDrawColor(_ren->get(), _border_color.r, _border_color.g, _border_color.b, 255);
  SDL_RenderFillRect(_ren->get(), &_border_rect);
  
  SDL_SetRenderDrawColor(_ren->get(), _background_color.r, _background_color.g, _background_color.b, 255);
  SDL_RenderFillRect(_ren->get(), &_background_rect);
  
  SDL_SetRenderDrawColor(_ren->get(), _bar_color.r, _bar_color.g, _bar_color.b, 255);
  SDL_RenderFillRect(_ren->get(), &_bar_rect);
  
  
  SDL_SetRenderDrawColor(_ren->get(), color_game_background.r, color_game_background.g, color_game_background.b, 255); // reset
}