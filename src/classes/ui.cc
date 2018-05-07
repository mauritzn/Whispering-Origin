#include <iostream>

#include "ui.h"
#include "functions.h"

using namespace std;


UI::UI(Game& game) {
  _game = &game;
  _base = new Image(*_game, base_ui_image_path, 0, 0);


  _text = {
    { "level_up", new Text(*_game, fonts["main_32"], color_white, "Level up! You are now level ", 0, 0) },
    { "greeting", new Text(*_game, fonts["main_20"], color_white, "Use WASD to move, F1 to toggle debug menu, F5-10 to give 5 xp, Q / E to switch inventory slots, G to drop", 0, 0) }
  };

  _text.at("level_up")->align_center();
  _text.at("level_up")->y((_text.at("level_up")->y() - 55));

  _text.at("greeting")->align_center_x();
  _text.at("greeting")->align_bottom();
  _text.at("greeting")->y((_text.at("greeting")->y() - 60));


  _debug_info = {
    { "ticks", new Text(*_game, fonts["main_20"], color_white, "Ticks: 0", 0, 1) },
    { "frames", new Text(*_game, fonts["main_20"], color_white, "Frames: 0", 0, 2) },
    { "fps", new Text(*_game, fonts["main_20"], color_white, "FPS: 0", 0, 3) },
    { "delta_time", new Text(*_game, fonts["main_20"], color_white, "Delta Time: 0", 0, 4) },

    { "player_hp", new Text(*_game, fonts["main_20"], color_white, "Health: 0/0", 0, 6) },
    { "player_lvl", new Text(*_game, fonts["main_20"], color_white, "Level: 0", 0, 7) },
    { "player_xp", new Text(*_game, fonts["main_20"], color_white, "XP: 0", 0, 8) },
    { "player_money", new Text(*_game, fonts["main_20"], color_white, "Money: 0", 0, 9) },
    { "player_xy", new Text(*_game, fonts["main_20"], color_white, "X: 0, Y: 0", 0, 10) },
    { "player_pos", new Text(*_game, fonts["main_20"], color_white, "Position (ROW x COL): 0x0", 0, 11) }
  };
  init_debug_info_position(_debug_info);
}



void UI::update() {
  update_debug_info(_debug_info, *_game);
}


void UI::render() {
  _base->render();

  if(_game->player()->has_leveled_up()) {
    _text.at("level_up")->update("Level up! You are now level " + format_number(_game->player()->level()));
    _text.at("level_up")->render();
  }

  for(const auto& value : _text) {
    if(value.first != "level_up") value.second->render();
  }

  if(debug_mode) render_debug_info(_debug_info);
}
