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
  uint32_t frames = 0;

  
  /*
  int id_to_check = 6381181;
  cout << "Tree ID '" << id_to_check << "' is ";
  if(item_exists(id_to_check, trees)) {
    cout << "valid, and it's name is: " << get_item_name(id_to_check, trees) << endl << endl;
  } else {
    cout << "NOT a valid ID valid" << endl << endl;
  }
  */
  
  
  if(SDL_Init(SDL_INIT_VIDEO) != 0) {
    cout << "SDL_Init Error: " << SDL_GetError() << endl;
    return 1;
  }

  if(TTF_Init() != 0) {
    cout << "TTF_Init Error: " << SDL_GetError() << endl;
    return 1;
  }

  int SDL_image_flags = IMG_INIT_PNG;
  if(!(IMG_Init(SDL_image_flags) & SDL_image_flags)) {
    cout << "IMG_Init Error: " << SDL_GetError() << endl;
    return 1;
  }


  SDL_DisplayMode DM;
  SDL_GetCurrentDisplayMode(0, &DM);
  int display_width = DM.w;
  int display_height = DM.h;


  cout << "Display Size: " << display_width << "x" << display_height << endl;
  cout << "Window Size: " << window_width << "x" << window_height << endl << endl;


  TTF_Font* debug_font = TTF_OpenFont(main_font, 20);
  TTF_Font* Ubuntu_font = TTF_OpenFont(main_font, 20);
  TTF_Font* Level_font = TTF_OpenFont(main_font, 32);
  SDL_Color background_color = { 21, 108, 153 };
  SDL_Color text_color = { 255, 255, 255 };




  Window win(game_name, ((display_width / 2) - (window_width / 2)), ((display_height / 2) - (window_height / 2)), window_width, window_height);
  Renderer ren(win, background_color);

  SDL_Surface* icon = IMG_Load(icon_path);
  SDL_SetWindowIcon(win.get(), icon);



  //BMP test_char(win, ren, "images/test_char_2.bmp", 0, 0);
  Player test_player(win, ren);
  
  World test_world(win, ren, fps, test_player);


  vector<PNG*> trees;
  const int tree_count = 5;

  for(int i = 0; i < tree_count; i++) {
    trees.push_back(new PNG(win, ren, tree_image_path, 0, 0));
  }

  trees[0]->set_x(545);
  trees[0]->set_y(125);

  trees[1]->set_x(929);
  trees[1]->set_y(157);

  trees[2]->set_x(801);
  trees[2]->set_y(189);

  trees[3]->set_x(321);
  trees[3]->set_y(285);

  trees[4]->set_x(865);
  trees[4]->set_y(317);

/*
  trees[0]->set_x(constrain_png_width(936, win, *trees[0]));
  trees[0]->set_y(constrain_png_height(25, win, *trees[0]));

  trees[1]->set_x(constrain_png_width(1093, win, *trees[1]));
  trees[1]->set_y(constrain_png_height(36, win, *trees[1]));

  trees[2]->set_x(constrain_png_width(986, win, *trees[2]));
  trees[2]->set_y(constrain_png_height(200, win, *trees[2]));

  trees[3]->set_x(constrain_png_width(1161, win, *trees[3]));
  trees[3]->set_y(constrain_png_height(168, win, *trees[3]));

  trees[4]->set_x(constrain_png_width(1103, win, *trees[4]));
  trees[4]->set_y(constrain_png_height(342, win, *trees[4]));
  */

  
  Text level_up(win, ren, Level_font, text_color, "Level up! You are now level ", 0, 0);
  level_up.align_center();
  level_up.set_y((level_up.get_y() - 55));


  Text hello_text(win, ren, Ubuntu_font, text_color, "<text will be updated ;) >", 0, 0);
  hello_text.align_center_x();
  hello_text.align_bottom();
  hello_text.set_y((hello_text.get_y() - 25));

  Text debug_ticks(win, ren, debug_font, text_color, "Ticks: 0", 25, 25);
  Text debug_frame_count(win, ren, debug_font, text_color, "Frames: 0", 25, 50);
  Text debug_fps(win, ren, debug_font, text_color, "FPS: 0", 25, 75);
  Text debug_delta_time(win, ren, debug_font, text_color, "Delta Time: 0", 25, 100);

  // Character-specific debug
  Text debug_health(win, ren, debug_font, text_color, "Health: ", 25, 150);
  Text debug_level(win, ren, debug_font, text_color, "Level: ", 25, 175);
  Text debug_exp(win, ren, debug_font, text_color, "XP: ", 25, 200);
  Text debug_money(win, ren, debug_font, text_color, "Money: ", 25, 225);









  SDL_Event event;
  bool running = true;

//   bool up_is_down = false;
//   bool down_is_down = false;
//   bool left_is_down = false;
//   bool right_is_down = false;
  
  bool debug_test_refresh_done = false;



  while(running) {
    while(SDL_PollEvent(&event)) {
      if(event.type == SDL_QUIT) running = false;
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
    
    
    test_player.render();

    
    
    
    trees[0]->set_x(865 + test_world.get_x());
    trees[0]->set_y(189 + test_world.get_y());

    trees[1]->set_x(1249 + test_world.get_x());
    trees[1]->set_y(221 + test_world.get_y());

    trees[2]->set_x(1121 + test_world.get_x());
    trees[2]->set_y(253 + test_world.get_y());

    trees[3]->set_x(641 + test_world.get_x());
    trees[3]->set_y(349 + test_world.get_y());

    trees[4]->set_x(1185 + test_world.get_x());
    trees[4]->set_y(381 + test_world.get_y());
    
    
    for(int i = 0; i < tree_count; i++) {
      trees[i]->render();
    }
    
    
    if(test_player.has_leveled_up()) {
        level_up.update("Level up! You are now level " + format_number(test_player.level()));
        level_up.render();
    }
    
    
    if(fps.ticks() >= 1000) {
      if(!debug_test_refresh_done) {
        debug_test_refresh_done = true;
        hello_text.update("Use WASD to move \"the character\" (up, down, left, right), F4 to toggle debug menu, F5 to give 5 xp"); // will not mess up alignment ;)
        
        test_player.decrease_money(50);
        test_player.damage(5);
      }
    }
    
    
    
    // BEGIN, DEBUG TEXT UPDATING & RENDERING
    debug_frame_count.update("Frames: " + format_number(frames++));
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


    if(debug_mode) {
      debug_frame_count.render();
      debug_ticks.render();
      debug_fps.render();
      debug_delta_time.render();

      debug_health.render();
      debug_exp.render();
      debug_level.render();
      debug_money.render();

    }
    // END, DEBUG TEXT UPDATING & RENDERING

    
    ren.update(); // update the screen
    // SDL_Delay(1000); // <= sometimes used for debuggning issues
  }


  TTF_CloseFont(debug_font);
  TTF_CloseFont(Ubuntu_font);

  TTF_Quit();
  SDL_Quit();
  cout << ">> Bye Bye! <<" << endl << endl;
}
