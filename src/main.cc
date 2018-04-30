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
#include <map>
#include <cmath>

#include "config.h"
#include "classes/window.h"
#include "classes/renderer.h"
#include "classes/functions.h"
#include "classes/image.h"
#include "classes/text.h"
#include "classes/fps.h"
#include "classes/player.h"
#include "classes/world.h"
#include "classes/progress_bar.h"
#include "classes/skill.h"
#include "classes/game.h"
using namespace std;


int main() {
  SDL_Event event;

  bool game_running = true;
  bool debug_test_refresh_done = false;

  Game game;
  game.player(*(new Player(game)));
  game.world(*(new World(game)));



  Image UI_base(game, base_ui_image_path, 0, 0);


  /*map<string, Text*> UI_text {
    { "player_title", new Text(game, fonts["main_16"], color_white, "Player", 30, 22) },
    { "player_level", new Text(game, fonts["main_14"], color_white, "Level 1", 0, 23) },
    { "player_xp", new Text(game, fonts["main_12"], color_white, ("0/" + format_number(xp_rates[0]) + " xp"), 157, 40) }
  };

  UI_text["player_level"]->align_right();
  UI_text["player_level"]->x(114);*/



  Text level_up(game, fonts["main_32"], color_white, "Level up! You are now level ", 0, 0);
  level_up.align_center();
  level_up.y((level_up.y() - 55));



  Text hello_text(game, fonts["main_20"], color_white, "Use WASD to move, F1 to toggle debug menu, F5-10 to give 5 xp, Q / E to switch inventory slots, G to drop", 0, 0);
  hello_text.align_center_x();
  hello_text.align_bottom();
  hello_text.y((hello_text.y() - 60));



  map<string, Text*> debug_info {
    { "ticks", new Text(game, fonts["main_20"], color_white, "Ticks: 0", 0, 1) },
    { "frames", new Text(game, fonts["main_20"], color_white, "Frames: 0", 0, 2) },
    { "fps", new Text(game, fonts["main_20"], color_white, "FPS: 0", 0, 3) },
    { "delta_time", new Text(game, fonts["main_20"], color_white, "Delta Time: 0", 0, 4) },

    { "player_hp", new Text(game, fonts["main_20"], color_white, "Health: 0/0", 0, 6) },
    { "player_lvl", new Text(game, fonts["main_20"], color_white, "Level: 0", 0, 7) },
    { "player_xp", new Text(game, fonts["main_20"], color_white, "XP: 0", 0, 8) },
    { "player_money", new Text(game, fonts["main_20"], color_white, "Money: 0", 0, 9) },
    { "player_xy", new Text(game, fonts["main_20"], color_white, "X: 0, Y: 0", 0, 10) },
    { "player_pos", new Text(game, fonts["main_20"], color_white, "Position (ROW x COL): 0x0", 0, 11) }
  };

  init_debug_info_position(debug_info);


  while(game_running) {
    while(SDL_PollEvent(&event)) {
      if(event.type == SDL_QUIT) game_running = false;
      else if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
        if(event.type == SDL_KEYDOWN) game.press_key(event.key.keysym.sym);
        else if(event.type == SDL_KEYUP) game.release_key(event.key.keysym.sym);
      } else {
        //if(event.type != 1024 && event.type != 512) cout << ">> Event: " << event.type << endl;
      }
    }



    if(game.key_ready(SDLK_F1, 250)) debug_mode = !debug_mode;

    if(game.key_ready(SDLK_F5)) game.player()->increase_xp(5);
    if(game.key_ready(SDLK_F6)) game.player()->skill("Woodcutting")->increase_xp(5);
    if(game.key_ready(SDLK_F7)) game.player()->skill("Mining")->increase_xp(5);
    if(game.key_ready(SDLK_F8)) game.player()->skill("Smithing")->increase_xp(5);
    if(game.key_ready(SDLK_F9)) game.player()->skill("Fishing")->increase_xp(5);
    if(game.key_ready(SDLK_F10)) game.player()->skill("Cooking")->increase_xp(5);


    if(game.key_ready(keys.at("inv_prev"))) {
      game.player()->prev_inventory_slot();
    }

    if(game.key_ready(keys.at("inv_next"))) {
      game.player()->next_inventory_slot();
    }

    if(game.key_ready(keys.at("drop_key"))) {
      if(game.key_pressed(SDLK_LSHIFT) || game.key_pressed(SDLK_RSHIFT)) {
        game.player()->drop_active_stack();
      } else {
        game.player()->drop_active_item();
      }
    }


    game.fps()->update();
    game.world()->update();


    game.renderer()->clear();
    game.world()->render();



    if(game.player()->has_leveled_up()) {
      level_up.update("Level up! You are now level " + format_number(game.player()->level()));
      level_up.render();
    }


    UI_base.render();
    game.player()->render_inventory();



    hello_text.render();

    if(game.fps()->ticks() >= 2500) {
      if(!debug_test_refresh_done) {
        // used for debugging future features

        debug_test_refresh_done = true;
      }
    }

    // render UI text
    /*for(const auto& value : UI_text) {
      value.second->render();
    }*/


    update_debug_info(debug_info, game);
    if(debug_mode) render_debug_info(debug_info);

    game.renderer()->update(); // update the screen
    // SDL_Delay(1000); // <= sometimes used for debuggning issues
  }


  for(const auto& value : fonts) {
    TTF_CloseFont(value.second);
  }

  TTF_Quit();
  SDL_Quit();
  cout << ">> Bye Bye! <<" << endl << endl;
}
