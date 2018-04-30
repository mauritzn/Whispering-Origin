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
