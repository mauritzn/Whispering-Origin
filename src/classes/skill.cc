#include "skill.h"
#include "functions.h"

using namespace std;


Skill::Skill(Game& game, string skill_name, int progress_width, int progress_height, int progress_x, int progress_y) {
  _game = &game;
  _name = skill_name;

  _progress = new Progress(*_game, xp_bar_color, progress_width, progress_height, 0, 0);
  _progress_x = progress_x;
  _progress_y = progress_y;

  _name_text = new Text(*_game, fonts["main_16"], color_white, _name, (_progress_x + 3), _progress_y);
  _progress->x(_progress_x);
  _progress->y(_progress_y + 20);

  _level_text = new Text(*_game, fonts["main_14"], color_white, "Level 1", 0, (_progress_y + 1));
  _level_text->align_right();
  _level_text->x((_progress->width() + _progress_x) - (_level_text->width() - 1));

  _xp_text = new Text(*_game, fonts["main_12"], color_white, "0/" + format_number(this->xp_to_level()) + " xp", 0, 0);
  _xp_text->x((_progress->width() + _progress_x) + 7);
  _xp_text->y(_progress->y() + ((_progress->height() / 2) - (_xp_text->height() / 2)));
}


string Skill::name() { return _name; }



int Skill::level() { return _level; }
int Skill::xp() { return _xp; }


int Skill::prev_xp_to_level() {
  if(_level > 1) {
    return xp_rates[_level - 2];
  } else {
    return 0;
  }
}

int Skill::xp_to_level() {
  if(_level >= max_level) {
    return xp_rates[max_level - 2];
  } else {
    return xp_rates[_level - 1];
  }
}


void Skill::increase_xp(int amount) {
  bool check_for_level_up = true;

  if(_level < max_level) {
    if(amount > 0) {
      _xp += amount;

      while(check_for_level_up) {
        if(_level < max_level) {
          if(_xp >= this->xp_to_level()) {
              _level++;
              _leveled_up_at = _game->fps()->ticks();
              _level_text->update("Level " + format_number(_level));

              if(_level == max_level) {
                _xp = this->xp_to_level();
              }
          } else {
            check_for_level_up = false;
          }
        } else {
          check_for_level_up = false;
        }
      }


      _xp_text->update(format_number(_xp) + "/" + format_number(this->xp_to_level()) + " xp");
      int relative_xp = (_xp - this->prev_xp_to_level());
      int relative_required_xp = (this->xp_to_level() - this->prev_xp_to_level());
      int progress_to_level = (((float) relative_xp / (float) relative_required_xp) * 100);
      if(_level == max_level) progress_to_level = 100;

      _progress->progress(progress_to_level);
    }
  }
}


bool Skill::has_leveled_up() {
  if(_leveled_up_at > 0) {
    if((_game->fps()->ticks() - _leveled_up_at) <= (unsigned) time_to_display_level_up_message) {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}



void Skill::render() {
  _progress->render();
  _name_text->render();
  _level_text->render();
  _xp_text->render();
}
