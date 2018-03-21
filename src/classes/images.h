#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <string>
using namespace std;


class BMP {
  private:
    SDL_Surface* _bmp;
    SDL_Texture* _tex;
    
    SDL_Rect _src_rect;
    SDL_Rect _dest_rect;
    
    int _width = 0;
    int _height = 0;

    
  public:
    BMP(Window& win, Renderer& ren, string path_to_image, int x, int y) {
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
    
    ~BMP() {
      SDL_DestroyTexture(_tex);
    }
    
    
    SDL_Texture* get() {
      return _tex;
    }
    
    
    int width() {
      return _width;
    }
    
    int height() {
      return _height;
    }
    
    
    SDL_Rect& src_rect() {
      return _src_rect;
    }
    
    SDL_Rect& dest_rect() {
      return _dest_rect;
    }
    
    void set_x(Window& win, int x) {
      if(x == -50) x = ((win.width() / 2) - (_width / 2));
      if(x == -100) x = (win.width() - _width);
      
      // defines container position
      _dest_rect.x = x;
    }
    
    void set_y(Window& win, int y) {
      if(y == -50) y = ((win.height() / 2) - (_height / 2));
      if(y == -100) y = (win.height() - _height);
      
      // defines container position
      _dest_rect.y = y;
    }
    
    int get_x() { return _dest_rect.x; }
    int get_y() { return _dest_rect.y; }
    
    void render(Renderer& ren) {
      SDL_RenderCopy(ren.get(), _tex, &_src_rect, &_dest_rect);
    }
};








class PNG {
  private:
    SDL_Surface* _png;
    SDL_Texture* _tex;
    
    SDL_Rect _src_rect;
    SDL_Rect _dest_rect;
    
    int _width = 0;
    int _height = 0;

    
  public:
    PNG(Window& win, Renderer& ren, string path_to_image, int x, int y) {
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
    
    ~PNG() {
      SDL_DestroyTexture(_tex);
    }
    
    
    SDL_Texture* get() {
      return _tex;
    }
    
    
    int width() {
      return _width;
    }
    
    int height() {
      return _height;
    }
    
    
    SDL_Rect& src_rect() {
      return _src_rect;
    }
    
    SDL_Rect& dest_rect() {
      return _dest_rect;
    }
    
    void set_x(Window& win, int x) {
      if(x == -50) x = ((win.width() / 2) - (_width / 2));
      if(x == -100) x = (win.width() - _width);
      
      // defines container position
      _dest_rect.x = x;
    }
    
    void set_y(Window& win, int y) {
      if(y == -50) y = ((win.height() / 2) - (_height / 2));
      if(y == -100) y = (win.height() - _height);
      
      // defines container position
      _dest_rect.y = y;
    }
    
    int get_x() { return _dest_rect.x; }
    int get_y() { return _dest_rect.y; }
    
    void render(Renderer& ren) {
      SDL_RenderCopy(ren.get(), _tex, &_src_rect, &_dest_rect);
    }
};
