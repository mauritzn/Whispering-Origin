#ifndef IMAGES_H
#define IMAGES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>
#include "window.h"
#include "renderer.h"


class BMP {
  private:
    Window* _win;
    Renderer* _ren;
    
    SDL_Surface* _bmp;
    SDL_Texture* _tex;
    
    SDL_Rect _src_rect;  // defines the images position inside the container
    SDL_Rect _dest_rect; // defines the images position inside the window
    
    int _width = 0;
    int _height = 0;

    
  public:
    BMP(Window&, Renderer&, string, int, int);
    ~BMP(); // free textures when the object is destroyed
    
    
    int width();  // get image width
    int height(); // get image height
    
    void set_x(int); // set the images x position
    void set_y(int); // set the images y position
    
    int get_x(); // get the images x position
    int get_y(); // get the images y position
    
    void render(); // render the texture to the renderer (-> window)
};







class PNG {
  private:
    Window* _win;
    Renderer* _ren;
    
    SDL_Surface* _png;
    SDL_Texture* _tex;
    
    SDL_Rect _src_rect;  // defines the images position inside the container
    SDL_Rect _dest_rect; // defines the images position inside the window
    
    int _width = 0;
    int _height = 0;

    
  public:
    PNG(Window&, Renderer&, string, int, int);
    ~PNG(); // free textures when the object is destroyed
    
    
    int width();  // get image width
    int height(); // get image height
    
    void set_x(int); // set the images x position
    void set_y(int); // set the images y position
    
    int get_x(); // get the images x position
    int get_y(); // get the images y position
    
    void render(); // render the texture to the renderer (-> window)
};

#endif