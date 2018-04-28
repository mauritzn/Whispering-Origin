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

    int x(); // get the images x position
    int y(); // get the images y position

    void x(int); // set the images x position
    void y(int); // set the images y position

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

    // TEMP (only used until ITEM class is completed)
    int _original_x = 0;
    int _original_y = 0;


  public:
    PNG(Window&, Renderer&, string, int, int);
    ~PNG(); // free textures when the object is destroyed


    int width();  // get image width
    int height(); // get image height

    void image_width(int);
    void image_height(int);

    void container_width(int);
    void container_height(int);


    void align_center();
    void align_center_x();
    void align_center_y();

    void align_top();
    void align_bottom();
    void align_left();
    void align_right();


    void image_x(int); // set the image's x position (without centering check)
    void image_y(int); // set the image's y position (without centering check)

    int x(); // get the container's x position
    int y(); // get the container's y position

    void x(int); // set the container's x position
    void y(int); // set the container's y position

    int image_x(); // get the image's x position
    int image_y(); // get the image's y position

    // TEMP (only used until ITEM class is completed)
    int original_x(); // get the container's original x position
    int original_y(); // get the container's original y position

    void render(); // render the texture to the renderer (-> window)
};

#endif
