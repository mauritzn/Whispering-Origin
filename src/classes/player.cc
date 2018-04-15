#include <SDL2/SDL.h>

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "player.h"
#include "images.h"
#include "functions.h"
#include "../config.h"

using namespace std;

Player::Player(Window& win, Renderer& ren) {
  _win = &win;
  _ren = &ren;

  _character = new PNG(*_win, *_ren, character_image_path, 0, 0);
  _character->set_container_width(character_grid_size);
  _character->set_container_height(character_grid_size);
  _character->set_image_width(character_grid_size);
  _character->set_image_height(character_grid_size);
  
  _character->align_center();
  _character->set_image_y(SOUTH);
  
  _hp = _max_hp;
  
  UI_active_slot = new PNG(*_win, *_ren, "images/active_slot.png", 0, 0);
  UI_active_slot->align_bottom();
  UI_active_slot->set_x(_inv_slots[0]);
}


int Player::get_x() { return _character->get_x(); }
int Player::get_y() { return _character->get_y(); }

void Player::set_x(int new_x) { _character->set_x(new_x); }
void Player::set_y(int new_y) { _character->set_y(new_y); }


player_direction Player::get_direction() {
  return (player_direction) _character->get_image_y();
}

void Player::set_direction(player_direction new_direction) {
  _character->set_image_y(new_direction);
}


int Player::max_health() { return _max_hp; }
int Player::health() { return _hp; }
uint32_t Player::money() { return _money; }

int Player::level() { return _player_level; }
int Player::xp() { return _player_xp; }


void Player::heal(int amount) {
  _hp += amount;
  if(_hp > _max_hp) _hp = _max_hp;
}

void Player::damage(int amount) {
  if(amount > 0) {
    if(_hp > 0) {
      if(amount <= _hp) {
        _hp -= amount;
      } else {
        _hp = 0;
      }
    }
  }
}

bool Player::is_alive() {
  if(_hp > 0) return true;
  else return false;
}



int Player::current_inventory_slot() {
  return _current_inventory_slot;
}

void Player::set_inventory_slot(int new_slot) {
  _current_inventory_slot = constrain(new_slot, 0, (_inv_slots.size() - 1));
  UI_active_slot->set_x(_inv_slots[_current_inventory_slot]);
}

void Player::prev_inventory_slot() {
  _current_inventory_slot--;
  if(_current_inventory_slot < 0) _current_inventory_slot = (_inv_slots.size() - 1);
  UI_active_slot->set_x(_inv_slots[_current_inventory_slot]);
}

void Player::next_inventory_slot() {
  _current_inventory_slot++;
  if((unsigned) _current_inventory_slot >= _inv_slots.size()) _current_inventory_slot = 0;
  UI_active_slot->set_x(_inv_slots[_current_inventory_slot]);
}


void Player::increase_money(int amount) {
  if(amount > 0) {
    if(_money < max_money) {
      if((_money + amount) <= max_money) {
        _money += amount;
      } else {
        _money = max_money;
      }
    }
  }
}

void Player::decrease_money(int amount) {
  if(amount > 0) {
    if(_money > 0) {
      if((unsigned) amount <= _money) {
        _money -= amount;
      } else {
        _money = 0;
      }
    }
  }
}

void Player::set_money(int amount) {
  if((unsigned) amount > max_money) amount = max_money;
  _money = amount;
}


int Player::xp_to_level() {
  if(_player_level == max_level) {
    return xp_rates[_player_level - 2];
  } else {
    return xp_rates[_player_level - 1];
  }
}


void Player::increase_xp(int amount) {
  bool check_for_level_up = true;
  
  if(_player_level < max_level) {
    if(amount > 0) _player_xp += amount;
    
    while(check_for_level_up) {
      if(_player_level < max_level) {
        if(_player_xp >= this->xp_to_level()) {
            _player_level++;
            _leveled_up_at = SDL_GetTicks();
            
            if(_player_level == max_level) {
              _player_xp = this->xp_to_level();
            }
            
            _max_hp += 5;
            _hp = _max_hp;
        } else {
          check_for_level_up = false;
        }
      } else {
        check_for_level_up = false;
      }
    }
  }
}


bool Player::has_leveled_up() {
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


void Player::render_inventory() {
  UI_active_slot->render();
}

void Player::render() {
  _character->render();
}