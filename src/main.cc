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
#include <vector>
#include <cmath>

#include "config.h"
#include "items.h"
#include "classes/window.h"
#include "classes/renderer.h"
#include "classes/functions.h"
#include "classes/images.h"
#include "classes/text.h"
#include "classes/fps.h"
#include "classes/player.h"
#include "classes/world.h"
using namespace std;





int main() {
  FPS fps;
  SDL_Event event;
  
  bool game_running = true;
  bool debug_test_refresh_done = false;
  
  init_SDL();

  
  SDL_DisplayMode DM;
  SDL_GetCurrentDisplayMode(0, &DM);
  int display_width = DM.w;
  int display_height = DM.h;

  cout << "Display Size: " << display_width << "x" << display_height << endl;
  cout << "Window Size: " << window_width << "x" << window_height << endl << endl;




  Window win(game_name, ((display_width / 2) - (window_width / 2)), ((display_height / 2) - (window_height / 2)), window_width, window_height);
  Renderer ren(win, color_game_background);

  SDL_Surface* icon = IMG_Load(icon_path);
  SDL_SetWindowIcon(win.get(), icon);

  

  //BMP test_char(win, ren, "images/test_char_2.bmp", 0, 0);
  Player test_player(win, ren);
  World test_world(win, ren, fps, test_player);



  Text level_up(win, ren, main_font_32, color_white, "Level up! You are now level ", 0, 0);
  level_up.align_center();
  level_up.set_y((level_up.get_y() - 55));


  Text hello_text(win, ren, main_font_20, color_white, "<text will be updated ;) >", 0, 0);
  hello_text.align_center_x();
  hello_text.align_bottom();
  hello_text.set_y((hello_text.get_y() - 25));

  
  Text debug_ticks(win, ren, main_font_20, color_white, "Ticks: 0", 25, 25);
  Text debug_frame_count(win, ren, main_font_20, color_white, "Frames: 0", 25, 50);
  Text debug_fps(win, ren, main_font_20, color_white, "FPS: 0", 25, 75);
  Text debug_delta_time(win, ren, main_font_20, color_white, "Delta Time: 0", 25, 100);

  
  // Character-specific debug
  Text debug_health(win, ren, main_font_20, color_white, "Health: ", 25, 150);
  Text debug_level(win, ren, main_font_20, color_white, "Level: ", 25, 175);
  Text debug_exp(win, ren, main_font_20, color_white, "XP: ", 25, 200);
  Text debug_money(win, ren, main_font_20, color_white, "Money: ", 25, 225);
  Text debug_xy(win, ren, main_font_20, color_white, "X: , Y: ", 25, 250);
  Text debug_pos(win, ren, main_font_20, color_white, "Position (ROW x COL): ", 25, 275);

  
  
  PNG UI_debug(win, ren, "images/UI_debug.png", 0, 0);
  
  
  



  while(game_running) {
    while(SDL_PollEvent(&event)) {
      if(event.type == SDL_QUIT) game_running = false;
      else if(event.type == SDL_KEYDOWN) {
        if(event.key.keysym.sym == SDLK_F5) test_player.increase_xp(5);
        else if(event.key.keysym.sym == SDLK_F4) debug_mode = !debug_mode;
        else {
          test_world.key_pressed(event.key.keysym.sym);
        }
      } else if(event.type == SDL_KEYUP) {
        test_world.key_released(event.key.keysym.sym);
      } else {
        //if(event.type != 1024 && event.type != 512) cout << ">> Event: " << event.type << endl;
      }
    }
    
    fps.update();
    test_world.update();
    

    ren.clear();
    test_world.render();

    hello_text.render();
    
    
    
    if(test_player.has_leveled_up()) {
      level_up.update("Level up! You are now level " + format_number(test_player.level()));
      level_up.render();
    }
    
    
    if(fps.ticks() >= 1000) {
      if(!debug_test_refresh_done) {
        debug_test_refresh_done = true;
        hello_text.update("Use WASD to move, F4 to toggle debug menu, F5 to give 5 xp"); // will not mess up alignment ;)
        
        test_player.decrease_money(50);
        test_player.damage(5);
      }
    }
    
    
    
    // BEGIN, DEBUG TEXT UPDATING & RENDERING
    debug_frame_count.update("Frames: " + format_number(fps.frame_count()));
    debug_ticks.update("Ticks: " + format_number(fps.ticks()));
    
    if((fps.ticks() % 500) < 250) {
      debug_fps.update("FPS: " + to_fixed(fps.get()));
    }
    
    debug_delta_time.update("Delta Time: " + to_string(fps.delta_time()));
    
    // Char-specific text-update
    debug_health.update("Health: " + format_number(test_player.health()));
    debug_exp.update("XP: " + format_number(test_player.xp()) + "/" + format_number(test_player.xp_to_level()));
    debug_level.update("Level: " + format_number(test_player.level()) + "/" 
            + to_string(max_level));
    debug_money.update("Money: " + format_number(test_player.money()));
    debug_xy.update("X: " + to_string(test_world.get_player_x()) + ", Y: " + to_string(test_world.get_player_y()));
    debug_pos.update("Position (ROW x COL): " + test_world.get_player_row_and_col());


    //UI_debug.render();
    
    if(debug_mode) {
      debug_frame_count.render();
      debug_ticks.render();
      debug_fps.render();
      debug_delta_time.render();

      debug_health.render();
      debug_exp.render();
      debug_level.render();
      debug_money.render();
      debug_xy.render();
      debug_pos.render();
    }
    // END, DEBUG TEXT UPDATING & RENDERING

    
    ren.update(); // update the screen
    // SDL_Delay(1000); // <= sometimes used for debuggning issues
  }


  TTF_CloseFont(main_font_16);
  TTF_CloseFont(main_font_20);
  TTF_CloseFont(main_font_32);

  TTF_Quit();
  SDL_Quit();
  cout << ">> Bye Bye! <<" << endl << endl;
}
