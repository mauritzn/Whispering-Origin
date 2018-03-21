#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <string>
using namespace std;


class Text {
  private:
    SDL_Surface* _surface;
    SDL_Texture* _text;
    
    TTF_Font* _font;
    SDL_Color _color;
    
    // -1 = left, 0 = center, 1 = right
    int _x_alignment = -1;
    int _y_alignment = -1;
    
    int _x = 0;
    int _y = 0;
    int _width = 0;
    int _height = 0;
    
    SDL_Rect _src_rect;
    SDL_Rect _dest_rect;

    
  public:
    Text(Window& win, Renderer& ren, TTF_Font* font, SDL_Color color, string text, int x, int y) {
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
      
      _text = SDL_CreateTextureFromSurface(ren.get(), _surface);
      SDL_FreeSurface(_surface);
      
      if(_text == NULL) {
        cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << endl;
        SDL_Quit();
      } else {
        SDL_QueryTexture(_text, NULL, NULL, &_width, &_height);
        
        
        if(_x_alignment == 0) _x = ((win.width() / 2) - (_width / 2));
        if(_x_alignment == 1) _x = (win.width() - _width);
        
        if(_y_alignment == 0) _y = ((win.height() / 2) - (_height / 2));
        if(_y_alignment == 1) _y = (win.height() - _height);
        
        _dest_rect = { _x, _y, _width, _height };
      }
    }
    
    ~Text() {
      SDL_DestroyTexture(_text);
    }
    
    
    SDL_Texture* get() {
      return _text;
    }
    
    SDL_Rect& dest_rect() {
      return _dest_rect;
    }
    
    void update(Renderer& ren, string text) {
      _surface = TTF_RenderText_Solid(_font, text.c_str(), _color);
      if(_surface == NULL) {
        cout << "TTF_RenderText_Solid Error: " << SDL_GetError() << endl;
        SDL_Quit();
      }
      
      SDL_DestroyTexture(_text);
      _text = SDL_CreateTextureFromSurface(ren.get(), _surface);
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
    
    
    void set_x(Window& win, int x) {
      if(x == -50) _x_alignment = 0;
      else if(x == -100) _x_alignment = 1;
      
      if(x == -50) x = ((win.width() / 2) - (_width / 2));
      if(x == -100) x = (win.width() - _width);
      
      // defines container position
      _x = x;
      _dest_rect.x = x;
    }
    
    void set_y(Window& win, int y) {
      if(y == -50) _y_alignment = 0;
      else if(y == -100) _y_alignment = 1;
      
      if(y == -50) y = ((win.height() / 2) - (_height / 2));
      if(y == -100) y = (win.height() - _height);
      
      // defines container position
      _y = y;
      _dest_rect.y = y;
    }
    
    int get_x() { return _dest_rect.x; }
    int get_y() { return _dest_rect.y; }
    
    
    void render(Renderer& ren) {
      SDL_RenderCopy(ren.get(), _text, NULL, &_dest_rect);
    }
};