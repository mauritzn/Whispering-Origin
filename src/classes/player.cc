#include <SDL2/SDL.h>

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "player.h"
#include "images.h"
#include "functions.h"
#include "../config.h"
#include "skill.h"

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
  
  UI_active_slot = new PNG(*_win, *_ren, active_slot_image_path, 0, 0);
  UI_active_slot->align_bottom();
  UI_active_slot->set_x(_inv_slots[0]);
  
  
  _skills.at(PLAYER_SKILL) = new Skill(*_win, *_ren, "Player");
  _hp = this->max_health();
  
  _skills.at(WOODCUTTING_SKILL) = new Skill(*_win, *_ren, "Woodcutting");
  _skills.at(MINING_SKILL) = new Skill(*_win, *_ren, "Mining");
  _skills.at(SMITHING_SKILL) = new Skill(*_win, *_ren, "Smithing");
  _skills.at(FISHING_SKILL) = new Skill(*_win, *_ren, "Fishing");
  _skills.at(COOKING_SKILL) = new Skill(*_win, *_ren, "Cooking");
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


int Player::max_health() { return (5 * (this->level() + 1)); }
int Player::health() { return _hp; }
uint32_t Player::money() { return _money; }

int Player::level() { return _skills.at(PLAYER_SKILL)->level(); }
int Player::xp() { return _skills.at(PLAYER_SKILL)->xp(); }


void Player::heal(int amount) {
  _hp += amount;
  if(_hp > this->max_health()) _hp = this->max_health();
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
  return _skills.at(PLAYER_SKILL)->xp_to_level();
}


void Player::increase_xp(int amount) {
  _skills.at(PLAYER_SKILL)->increase_xp(amount);
}


bool Player::has_leveled_up() {
  if(_skills.at(PLAYER_SKILL)->has_leveled_up()) {
    _hp = this->max_health();
    return true;
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