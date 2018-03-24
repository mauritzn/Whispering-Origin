/*
 * ## Required dependencies ##
 *  - SDL2
 *
 * ## Installation ##
 *  Use the bundled install file to install the dependencies
 *  > sudo sh ./_install_dependencies.sh
 *
 *  or do it manually using:
 *  > sudo apt-get install libsdl2-dev
 *
 *
 * ## Tested on ##
 *  - Ubuntu 17.10.1
 */
#include <SDL2/SDL.h>

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;


bool get_RGB(SDL_Color& color, SDL_Surface* surface, int x, int y) {
  if(surface->format->BitsPerPixel == 32) {
    uint32_t* pixels = (uint32_t*) surface->pixels;
    uint32_t pixel = pixels[(y * surface->w) + x]; // , 224, 192
    
    SDL_GetRGB(pixel, surface->format, &(color.r), &(color.g), &(color.b));
    return true;
  } else {
    return false;
  }
}



int main() {
  int map_width = 0;
  int map_height = 0;
  
  SDL_Surface* surface = SDL_LoadBMP("images/map/data.bmp");
  //SDL_Texture* map_texture = NULL;
  
  if(surface == NULL) {
    cout << "SDL_LoadBMP Error: " << SDL_GetError() << endl;
    SDL_Quit();
  } else {
    map_width = surface->w;
    map_height = surface->h;
    

     // x: 0, y: 0 (water)
     // x: 223, y: 191 (collider)
     // x: 224, y: 192 (grass)
    const int x = 224;
    const int y = 192;
    
    SDL_Color color = { 255, 255, 255 };
    if(get_RGB(color, surface, x, y)) {
      if(color.r == 21 && color.g == 108 && color.b == 153) cout << "Pixel at \"" << x << ", " << y << "\" is Water!" << endl;
      else if(color.r == 65 && color.g == 170 && color.b == 51) cout << "Pixel at \"" << x << ", " << y << "\" is Grass!" << endl;
      else if(color.r == 245 && color.g == 245 && color.b == 245) cout << "Pixel at \"" << x << ", " << y << "\" is Collider!" << endl;
      
      
      cout << "R: " << (unsigned) (color.r)
          << ", G: " << (unsigned) (color.g)
          << ", B: " << (unsigned) (color.b)
          << endl << endl;
    } else {
      cout << "Image is invalid, a 32-bit image is required, the surface is " << (unsigned) surface->format->BitsPerPixel << "-bit" << endl;
    }
    
    //map_texture = SDL_CreateTextureFromSurface(ren.get(), surface);
    SDL_FreeSurface(surface);
  }
  
  /*
  if(map_texture == NULL) {
    cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << endl;
    SDL_Quit();
  } else {
    
  }
  */
  
  cout << ">> Map width: " << map_width << ", Map height: " << map_height << " <<" << endl << endl;
}