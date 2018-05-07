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

#include <iostream>
#include <string>
#include <map>

#include "config.h"
#include "classes/functions.h"
#include "classes/image.h"
#include "classes/text.h"
#include "classes/game.h"
using namespace std;


int main() {
  Game game;
  bool debug_test_refresh_done = false;

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


  while(game.running()) {
    while(SDL_PollEvent(game.event())) {
      if(game.event_type()== SDL_QUIT) game.running(false);
      else if(game.event_type() == SDL_KEYDOWN || game.event_type() == SDL_KEYUP) {
        if(game.event_type() == SDL_KEYDOWN) game.press_key(game.event_key());
        else if(game.event_type() == SDL_KEYUP) game.release_key(game.event_key());
      } else {
        //if(game.event_type() != 1024 && game.event_type() != 512) cout << ">> Event: " << game.event_type() << endl;
      }
    }



    game.check_keys();

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
}
