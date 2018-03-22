/*
 * ## Required dependencies ##
 *  - SDL2
 *  - SDL2 ttf
 *  - SDL2 image
 * 
 * ## Installation ##
 *  Use the bundled install file to install the dependencies
 *  > sudo sh ./_install_dependencies.sh
 * 
 *  or do it manually using:
 *  > sudo apt-get install libsdl2-dev
 *  > sudo apt-get install libsdl2-ttf-dev
 *  > sudo apt-get install libsdl2-image-dev
 * 
 * 
 * ## Tested on ##
 *  - Ubuntu 17.10.1
 *  - KDE Neon (Ubuntu with 16.04.1)
 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>

#include "classes/window.h"
#include "classes/renderer.h"
#include "classes/images.h"
#include "classes/text.h"
#include "classes/fps.h"
using namespace std;


int constrain(int number, int min, int max) {
  if(number < min) number = min;
  if(number > max) number = max;
  
  return number;
}


int constrain_png_width(int number, Window& win, PNG& png) {
  return constrain(number, 0, (win.width() - png.width()));
}

int constrain_png_height(int number, Window& win, PNG& png) {
  return constrain(number, 0, (win.height() - png.height()));
}


string format_number(int number_to_format) {
  stringstream formatted_number;
  
  formatted_number.imbue(locale(""));
  formatted_number << fixed << number_to_format;
  
  return formatted_number.str();
}

string to_fixed(float number_to_fix) {
  stringstream fixed_number;
  fixed_number << fixed << setprecision(2) << number_to_fix;
  
  return fixed_number.str();
}






int main() {
  FPS fps;
  uint32_t frames = 0;
  
  const int window_width = 1280;
  const int window_height = 720;
  
  if(SDL_Init(SDL_INIT_VIDEO) != 0) {
    cout << "SDL_Init Error: " << SDL_GetError() << endl;
    return 1;
  }
  
  if(TTF_Init() != 0) {
    cout << "TTF_Init Error: " << SDL_GetError() << endl;
    return 1;
  }
  
  int imgFlags = IMG_INIT_PNG;
  if(!(IMG_Init(imgFlags) & imgFlags)) {
    cout << "IMG_Init Error: " << SDL_GetError() << endl;
    return 1;
  }
  
  
  SDL_DisplayMode DM;
  SDL_GetCurrentDisplayMode(0, &DM);
  int display_width = DM.w;
  int display_height = DM.h;
  
  const int vel = 250;
  
  
  cout << "Display Size: " << display_width << "x" << display_height << endl;
  cout << "Window Size: " << window_width << "x" << window_height << endl << endl;
  
  
  TTF_Font* debug_font = TTF_OpenFont("fonts/Ubuntu_C.ttf", 20);
  TTF_Font* Ubuntu_font = TTF_OpenFont("fonts/Ubuntu_C.ttf", 24);
  SDL_Color background_color = { 240, 240, 240 };
  SDL_Color text_color = { 0, 0, 0 };
  
  
  
  
  Window win("Hello World!", ((display_width / 2) - (window_width / 2)), ((display_height / 2) - (window_height / 2)), window_width, window_height);
  Renderer ren(win, background_color);
  
  SDL_Surface* icon = IMG_Load("images/icon.png");
  SDL_SetWindowIcon(win.get(), icon);
  
  
  BMP demo_720p_map(win, ren, "images/simple_720p_map.bmp", 0, 0);
  
  //BMP test_char(win, ren, "images/test_char_2.bmp", -50, -50); // -50 => centered, -100 => bottom aligned / right aligned
  PNG test_char(win, ren, "images/test_char_3.png", -50, -50); // -50 => centered, -100 => bottom aligned / right aligned
  
  
  vector<PNG*> trees;
  const int tree_count = 5;
  
  for(int i = 0; i < tree_count; i++) {
    trees.push_back(new PNG(win, ren, "images/tree.png", -50, -50));
  }
  
  trees[0]->set_x(win, constrain_png_width(936, win, *trees[0]));
  trees[0]->set_y(win, constrain_png_height(25, win, *trees[0]));
  
  trees[1]->set_x(win, constrain_png_width(1093, win, *trees[1]));
  trees[1]->set_y(win, constrain_png_height(36, win, *trees[1]));
  
  trees[2]->set_x(win, constrain_png_width(986, win, *trees[2]));
  trees[2]->set_y(win, constrain_png_height(200, win, *trees[2]));
  
  trees[3]->set_x(win, constrain_png_width(1161, win, *trees[3]));
  trees[3]->set_y(win, constrain_png_height(168, win, *trees[3]));
  
  trees[4]->set_x(win, constrain_png_width(1103, win, *trees[4]));
  trees[4]->set_y(win, constrain_png_height(342, win, *trees[4]));
  
  
  
  
  Text hello(win, ren, Ubuntu_font, text_color, "<text will be updated ;) >", -50, -100); // -50 => centered, -100 => bottom aligned / right aligned
  hello.set_y(win, (hello.get_y() - 25));
  
  Text debug_ticks(win, ren, debug_font, text_color, "Ticks: 0", 25, 25);
  Text debug_frame_count(win, ren, debug_font, text_color, "Frames: 0", 25, 50);
  Text debug_fps(win, ren, debug_font, text_color, "FPS: 0", 25, 75);
  Text debug_delta_time(win, ren, debug_font, text_color, "Delta Time: 0", 25, 100);
  
  
  
  
  
  
  
  
  
  
  SDL_Event event;
  bool running = true;
  
  bool up_is_down = false;
  bool down_is_down = false;
  bool left_is_down = false;
  bool right_is_down = false;
  
  
  
  while(running) {
    while(SDL_PollEvent(&event)) {
      if(event.type == SDL_QUIT) running = false;
      else if(event.type == SDL_KEYDOWN) {
        if(event.key.keysym.sym == SDLK_UP) up_is_down = true;
        if(event.key.keysym.sym == SDLK_w) up_is_down = true;
        
        if(event.key.keysym.sym == SDLK_DOWN) down_is_down = true;
        if(event.key.keysym.sym == SDLK_s) down_is_down = true;
        
        if(event.key.keysym.sym == SDLK_LEFT) left_is_down = true;
        if(event.key.keysym.sym == SDLK_a) left_is_down = true;
        
        if(event.key.keysym.sym == SDLK_RIGHT) right_is_down = true;
        if(event.key.keysym.sym == SDLK_d) right_is_down = true;
      } else if(event.type == SDL_KEYUP) {
        if(event.key.keysym.sym == SDLK_UP) up_is_down = false;
        if(event.key.keysym.sym == SDLK_w) up_is_down = false;
        
        if(event.key.keysym.sym == SDLK_DOWN) down_is_down = false;
        if(event.key.keysym.sym == SDLK_s) down_is_down = false;
        
        if(event.key.keysym.sym == SDLK_LEFT) left_is_down = false;
        if(event.key.keysym.sym == SDLK_a) left_is_down = false;
        
        if(event.key.keysym.sym == SDLK_RIGHT) right_is_down = false;
        if(event.key.keysym.sym == SDLK_d) right_is_down = false;
      } else {
        //if(event.type != 1024 && event.type != 512) cout << ">> Event: " << event.type << endl;
      }
    }
    
    float temp_vel = (vel * fps.delta_time());
    //float temp_vel = (vel * 0.015000);
    // down and right seem a bit slower than up and left?
    if(up_is_down) {
      test_char.set_y(win, constrain((test_char.get_y() - temp_vel), 0, (window_height - test_char.height())));
    }
    if(down_is_down) {
      test_char.set_y(win, constrain((test_char.get_y() + temp_vel), 0, (window_height - test_char.height())));
    }
    
    if(left_is_down) {
      test_char.set_x(win, constrain((test_char.get_x() - temp_vel), 0, (window_width - test_char.width())));
    }
    if(right_is_down) {
      test_char.set_x(win, constrain((test_char.get_x() + temp_vel), 0, (window_width - test_char.width())));
    }
    
    
    ren.clear();
    demo_720p_map.render(ren);
    
    hello.render(ren);
    
    
    
    test_char.render(ren);
    
    for(int i = 0; i < tree_count; i++) {
      trees[i]->render(ren);
    }
    
    
    debug_frame_count.update(ren, "Frames: " + format_number(frames++));
    debug_frame_count.render(ren);
    
    fps.update();
    
    
    
    debug_ticks.update(ren, "Ticks: " + format_number(fps.ticks()));
    cout << "Ticks: " << format_number(fps.ticks()) << endl;
    debug_ticks.render(ren);
    
    if((fps.ticks() % 500) < 250) {
      debug_fps.update(ren, "FPS: " + to_fixed(fps.get()));
    }
    debug_fps.render(ren);
    
    debug_delta_time.update(ren, "Delta Time: " + to_string(fps.delta_time()));
    debug_delta_time.render(ren);
    
    
    if(fps.ticks() > 1000) {
      hello.update(ren, "Use arrow keys or WASD to move \"the character\" (up, down, left, right)"); // will not mess up alignment ;)
    }
    
    
    ren.update();
    // SDL_Delay(1000);
  }
  
  
  TTF_CloseFont(debug_font);
  TTF_CloseFont(Ubuntu_font);
  
  TTF_Quit();
  SDL_Quit();
  cout << ">> Bye Bye! <<" << endl << endl;
}
