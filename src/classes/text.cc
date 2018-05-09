#include <iostream>
#include "text.h"
#include "../config.h"


Text::Text(Game& game, TTF_Font* font, SDL_Color color, string text, int x, int y) {
  _game = &game;

  _font = font;
  _color = color;
  _x = x;
  _y = y;

  if(_x == -50) _x_alignment = 0;
  else if(_x == -100) _x_alignment = 1;

  if(_y == -50) _y_alignment = 0;
  else if(_y == -100) _y_alignment = 1;


  if(anti_aliased_font) _surface = TTF_RenderUTF8_Blended(_font, text.c_str(), _color);
  else _surface = TTF_RenderUTF8_Solid(_font, text.c_str(), _color);

  if(_surface == NULL) {
    cout << "TTF_RenderText_Solid Error: " << SDL_GetError() << endl;
    SDL_Quit();
  }

  _tex = SDL_CreateTextureFromSurface(_game->renderer()->get(), _surface);
  SDL_FreeSurface(_surface);

  if(_tex == NULL) {
    cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << endl;
    SDL_Quit();
  } else {
    SDL_QueryTexture(_tex, NULL, NULL, &_width, &_height);


    if(_x_alignment == 0) _x = ((_game->window()->width() / 2) - (_width / 2));
    if(_x_alignment == 1) _x = (_game->window()->width() - _width);

    if(_y_alignment == 0) _y = ((_game->window()->height() / 2) - (_height / 2));
    if(_y_alignment == 1) _y = (_game->window()->height() - _height);

    _dest_rect = { _x, _y, _width, _height };
  }
}

Text::~Text() {
  SDL_DestroyTexture(_tex);
}



void Text::update(string text) {
  if(anti_aliased_font) _surface = TTF_RenderUTF8_Blended(_font, text.c_str(), _color);
  else _surface = TTF_RenderUTF8_Solid(_font, text.c_str(), _color);

  if(_surface == NULL) {
    cout << "TTF_RenderText_Solid Error: " << SDL_GetError() << endl;
    SDL_Quit();
  }

  SDL_DestroyTexture(_tex);
  _tex = SDL_CreateTextureFromSurface(_game->renderer()->get(), _surface);
  SDL_FreeSurface(_surface);

  if(_tex == NULL) {
    cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << endl;
    SDL_Quit();
  } else {
    int old_width = _width;

    SDL_QueryTexture(_tex, NULL, NULL, &_width, &_height);
    if(_x_alignment == 0) {
      if(_width > old_width) _x -= (_width - old_width) / 2;
      else if(_width < old_width) _x += (old_width - _width) / 2;
    }

    if(_x_alignment == 1) {
      if(_width > old_width) _x -= (_width - old_width);
      else if(_width < old_width) _x += (old_width - _width);
    }

    _dest_rect = { _x, _y, _width, _height };
  }
}



int Text::width() { return _width; }
int Text::height() { return _height; }



void Text::align_center() {
  _x_alignment = 0;

  // defines container positions
  _x = ((_game->window()->width() / 2) - (_width / 2));
  _y = ((_game->window()->height() / 2) - (_height / 2));

  _dest_rect.x = _x;
  _dest_rect.y = _y;
}
void Text::align_center_x() {
  _x_alignment = 0;

  // defines container position
  _x = ((_game->window()->width() / 2) - (_width / 2));
  _dest_rect.x = _x;
}
void Text::align_center_y() {
  // defines container position
  _y = ((_game->window()->height() / 2) - (_height / 2));
  _dest_rect.y = _y;
}

void Text::align_top() {
  // defines container position
  _y = 0;
  _dest_rect.y = _y;
}

void Text::align_bottom() {
  // defines container position
  _y = (_game->window()->height() - _height);
  _dest_rect.y = _y;
}

void Text::align_left() {
  _x_alignment = -1;

  // defines container position
  _x = 0;
  _dest_rect.x = _x;
}

void Text::align_right() {
  _x_alignment = 1;

  // defines container position
  _x = (_game->window()->width() - _width);
  _dest_rect.x = _x;
}




int Text::x() { return _dest_rect.x; }
int Text::y() { return _dest_rect.y; }

void Text::x(int x) {
  // defines container position
  _x = x;
  _dest_rect.x = x;
}

void Text::y(int y) {
  // defines container position
  _y = y;
  _dest_rect.y = y;
}


void Text::render() {
  SDL_RenderCopy(_game->renderer()->get(), _tex, NULL, &_dest_rect);
}