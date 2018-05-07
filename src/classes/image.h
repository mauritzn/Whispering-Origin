#ifndef IMAGE_H
#define IMAGE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>
#include "game.h"


class Image {
  private:
    Game* _game;

    SDL_Surface* _img;
    SDL_Texture* _tex;

    SDL_Rect _src_rect;  // defines the images position inside the container
    SDL_Rect _dest_rect; // defines the images position inside the window

    int _width = 0;
    int _height = 0;


  public:
    Image(Game&, string, int, int);
    ~Image(); // free textures when the object is destroyed

    int width();  // get image file real width
    int height(); // get image file real height

    void image_width(int); // get the image's width
    void image_height(int); // get the image's height

    void container_width(int); // get the container's width
    void container_height(int); // get the container's height


    void align_center(); // set x & y to the center of the screen
    void align_center_x(); // set x to the center of the screen
    void align_center_y(); // set y to the center of the screen

    void align_top(); // set y to the top of the screen
    void align_bottom(); // set y to the bottom of the screen
    void align_left(); // set x to the left of the screen
    void align_right(); // set x to the right of the screen


    int image_x(); // get the image's x position
    int image_y(); // get the image's y position

    void image_x(int); // set the image's x position (without centering check)
    void image_y(int); // set the image's y position (without centering check)

    int x(); // get the container's x position
    int y(); // get the container's y position

    void x(int); // set the container's x position
    void y(int); // set the container's y position

    void render(); // render the texture to the renderer (-> window)
};

#endif
