#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <string>

#include "skill.h"
#include "window.h"
#include "renderer.h"
#include "../config.h"
#include "text.h"

using namespace std;


Skill::Skill(Window& win, Renderer& ren, string skill_name) {
  _win = &win;
  _ren = &ren;
  
  _name = skill_name;
}


string Skill::name() { return _name; }



int Skill::level() { return _level; }
int Skill::xp() { return _xp; }


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
    if(amount > 0) _xp += amount;
    
    while(check_for_level_up) {
      if(_level < max_level) {
        if(_xp >= this->xp_to_level()) {
            _level++;
            _leveled_up_at = SDL_GetTicks();
            
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
  }
}


bool Skill::has_leveled_up() {
  if(_leveled_up_at > 0) {
    if((SDL_GetTicks() - _leveled_up_at) <= (unsigned) time_to_display_level_up_message) {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}



void Skill::render() {}