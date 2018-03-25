#include <iostream>
#include "text.h"


Text::Text(Window& win, Renderer& ren, TTF_Font* font, SDL_Color color, string text, int x, int y) {
  _win = &win;
  _ren = &ren;
  
  _font = font;
  _color = color;
  _x = x;
  _y = y;
  
  if(_x == -50) _x_alignment = 0;
  else if(_x == -100) _x_alignment = 1;
  
  if(_y == -50) _y_alignment = 0;
  else if(_y == -100) _y_alignment = 1;
  
  
  _surface = TTF_RenderText_Solid(_font, text.c_str(), _color);
  if(_surface == NULL) {
    cout << "TTF_RenderText_Solid Error: " << SDL_GetError() << endl;
    SDL_Quit();
  }
  
  _text = SDL_CreateTextureFromSurface(_ren->get(), _surface);
  SDL_FreeSurface(_surface);
  
  if(_text == NULL) {
    cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << endl;
    SDL_Quit();
  } else {
    SDL_QueryTexture(_text, NULL, NULL, &_width, &_height);
    
    
    if(_x_alignment == 0) _x = ((_win->width() / 2) - (_width / 2));
    if(_x_alignment == 1) _x = (_win->width() - _width);
    
    if(_y_alignment == 0) _y = ((_win->height() / 2) - (_height / 2));
    if(_y_alignment == 1) _y = (_win->height() - _height);
    
    _dest_rect = { _x, _y, _width, _height };
  }
}

Text::~Text() {
  SDL_DestroyTexture(_text);
}


SDL_Texture* Text::get() {
  return _text;
}

SDL_Rect& Text::dest_rect() {
  return _dest_rect;
}

void Text::update(string text) {
  _surface = TTF_RenderText_Solid(_font, text.c_str(), _color);
  if(_surface == NULL) {
    cout << "TTF_RenderText_Solid Error: " << SDL_GetError() << endl;
    SDL_Quit();
  }
  
  SDL_DestroyTexture(_text);
  _text = SDL_CreateTextureFromSurface(_ren->get(), _surface);
  SDL_FreeSurface(_surface);
  
  if(_text == NULL) {
    cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << endl;
    SDL_Quit();
  } else {
    int old_width = _width;
    
    SDL_QueryTexture(_text, NULL, NULL, &_width, &_height);
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


void Text::set_x(int x) {
  if(x == -50) _x_alignment = 0;
  else if(x == -100) _x_alignment = 1;
  
  if(x == -50) x = ((_win->width() / 2) - (_width / 2));
  if(x == -100) x = (_win->width() - _width);
  
  // defines container position
  _x = x;
  _dest_rect.x = x;
}

void Text::set_y(int y) {
  if(y == -50) _y_alignment = 0;
  else if(y == -100) _y_alignment = 1;
  
  if(y == -50) y = ((_win->height() / 2) - (_height / 2));
  if(y == -100) y = (_win->height() - _height);
  
  // defines container position
  _y = y;
  _dest_rect.y = y;
}

int Text::get_x() { return _dest_rect.x; }
int Text::get_y() { return _dest_rect.y; }


void Text::render() {
  SDL_RenderCopy(_ren->get(), _text, NULL, &_dest_rect);
}