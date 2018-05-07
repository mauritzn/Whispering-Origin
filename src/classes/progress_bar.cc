#include "progress_bar.h"
#include "functions.h"
#include "../config.h"

using namespace std;


Progress::Progress(Game& game, SDL_Color bar_color, int width, int height, int x, int y) {
  _game = &game;
  _bar_color = bar_color;

  _original_x = x;
  _original_y = y;


  this->x(_original_x);
  this->y(_original_y);

  this->width(width);
  this->height(height);
}



int Progress::width() { return _background_rect.w; }
int Progress::height() { return _background_rect.h; }

void Progress::width(int new_width) {
  _border_rect.w = new_width;
  _background_rect.w = (_border_rect.w - (_border_size * 2));
  _bar_rect.w = _background_rect.w * ((float) _progress / 100.0);
}

void Progress::height(int new_height) {
  _border_rect.h = new_height;
  _background_rect.h = (_border_rect.h - (_border_size * 2));
  _bar_rect.h = _background_rect.h;
}


int Progress::border_size() { return _border_size; }

void Progress::border_size(int new_size) {
  _border_size = new_size;

  // update width, height, x, y
  this->width(this->width());
  this->height(this->height());

  this->x(this->x());
  this->y(this->y());
}


SDL_Color Progress::bar_color() { return _bar_color; }
SDL_Color Progress::background_color() { return _background_color; }
SDL_Color Progress::border_color() { return _border_color; }

void Progress::bar_color(SDL_Color new_color) {
  _bar_color = new_color;
}

void Progress::background_color(SDL_Color new_color) {
  _background_color = new_color;
}

void Progress::border_color(SDL_Color new_color) {
  _border_color = new_color;
}


int Progress::original_x() { return _original_x; }
int Progress::original_y() { return _original_y; }


int Progress::x() { return _border_rect.x; }
int Progress::y() { return _border_rect.y; }

void Progress::x(int new_x) {
  _border_rect.x = new_x;
  _background_rect.x = (_border_rect.x + _border_size);
  _bar_rect.x = _background_rect.x;
}
void Progress::y(int new_y) {
  _border_rect.y = new_y;
  _background_rect.y = (_border_rect.y + _border_size);
  _bar_rect.y = _background_rect.y;
}


int Progress::progress() { return _progress; }

void Progress::progress(int new_progress) {
  _progress = constrain(new_progress, 0, 100);
  _bar_rect.w = _background_rect.w * ((float) _progress / 100.0);
}


void Progress::render() {
  SDL_SetRenderDrawColor(_game->renderer()->get(), _border_color.r, _border_color.g, _border_color.b, 255);
  SDL_RenderFillRect(_game->renderer()->get(), &_border_rect);

  SDL_SetRenderDrawColor(_game->renderer()->get(), _background_color.r, _background_color.g, _background_color.b, 255);
  SDL_RenderFillRect(_game->renderer()->get(), &_background_rect);

  SDL_SetRenderDrawColor(_game->renderer()->get(), _bar_color.r, _bar_color.g, _bar_color.b, 255);
  SDL_RenderFillRect(_game->renderer()->get(), &_bar_rect);


  SDL_SetRenderDrawColor(_game->renderer()->get(), color_game_background.r, color_game_background.g, color_game_background.b, 255); // reset
}
