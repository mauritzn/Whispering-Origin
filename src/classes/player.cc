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
#include "text.h"

using namespace std;

Player::Player(Window& win, Renderer& ren) {
  _win = &win;
  _ren = &ren;

  _character = new PNG(*_win, *_ren, character_image_path, 0, 0);
  _character->container_width(character_grid_size);
  _character->container_height(character_grid_size);
  _character->image_width(character_grid_size);
  _character->image_height(character_grid_size);

  _character->align_center();
  _character->image_y(SOUTH);

  UI_active_slot = new PNG(*_win, *_ren, active_slot_image_path, 0, 0);
  UI_active_slot->align_bottom();
  UI_active_slot->x(inv_slot_pos[0]);


  _skills.at(PLAYER_SKILL) = new Skill(*_win, *_ren, "Player", 127, 12, 25, 22);
  _hp = this->max_health();

  _skills.at(WOODCUTTING_SKILL) = new Skill(*_win, *_ren, "Woodcutting", 142, 8, 64, 512);
  _skills.at(MINING_SKILL) = new Skill(*_win, *_ren, "Mining", 142, 8, 64, 549);
  _skills.at(SMITHING_SKILL) = new Skill(*_win, *_ren, "Smithing", 142, 8, 64, 586);
  _skills.at(FISHING_SKILL) = new Skill(*_win, *_ren, "Fishing", 142, 8, 64, 623);
  _skills.at(COOKING_SKILL) = new Skill(*_win, *_ren, "Cooking", 142, 8, 64, 660);


  for(const inventory_slot_positions& value: inv_slot_pos) {
    _inv_slots.push_back(NULL);
    //_debug_neighbor.push_back(new Text(*_win, *_ren, fonts["main_16"], color_white, dir_text[i], 0, 0));

    _inv_slot_texts.push_back(new Text(*_win, *_ren, fonts["main_16"], color_white, "0", 0, 700));
    _inv_slot_texts.back()->align_right();
    _inv_slot_texts.back()->x(value + (item_grid_size - _inv_slot_texts.back()->width()) - 1);

    _inv_slot_images.push_back(new PNG(*_win, *_ren, items_image_path, (value + 2), 678));
    _inv_slot_images.back()->container_width(item_grid_size);
    _inv_slot_images.back()->container_height(item_grid_size);
    _inv_slot_images.back()->image_width(item_grid_size);
    _inv_slot_images.back()->image_height(item_grid_size);
    _inv_slot_images.back()->image_y(0);
  }
}


int Player::x() { return _character->x(); }
int Player::y() { return _character->y(); }

void Player::x(int new_x) { _character->x(new_x); }
void Player::y(int new_y) { _character->y(new_y); }


player_direction Player::direction() {
  return (player_direction) _character->image_y();
}

void Player::direction(player_direction new_direction) {
  _character->image_y(new_direction);
}


int Player::max_health() { return (5 * (this->level() + 1)); }
int Player::health() { return _hp; }

int Player::level() { return _skills.at(PLAYER_SKILL)->level(); }
int Player::xp() { return _skills.at(PLAYER_SKILL)->xp(); }


Skill* Player::skill(string skill_name) {
  if(skill_name != "Player") {
    for(Skill* value: _skills) {
      if(skill_name == value->name()) {
        return value;
      }
    }
  }

  return NULL;
}


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



void Player::add_item(items item_to_add) {
  inv_slot* add_to = NULL;

  for(inv_slot*& value: _inv_slots) {
    if(value != NULL) {
      if(value->item == item_to_add) {
        if(value->quantity < max_item_stack) {
          add_to = value;
        }
      }
    }
  }

  if(add_to == NULL) {
    for(inv_slot*& value: _inv_slots) {
      if(value == NULL) {
        if(add_to == NULL) {
          value = new inv_slot();
          value->item = item_to_add;
          value->quantity = 0;
          add_to = value;
        }
      }
    }
  }

  if(add_to != NULL) {
    add_to->quantity++;
    //cout << "Added item to inventory || " << item_names.at(item_to_add) << endl;

    int slot_nr = 0;
    for(inv_slot*& value: _inv_slots) {
      if(value != NULL) {
        //cout << "Slot #" << (slot_nr + 1) << " => " << item_names.at(value->item) << " || " << value->quantity << "/10" << endl;
        _inv_slot_texts[slot_nr]->update(format_number(value->quantity));
        _inv_slot_images[slot_nr]->image_y(item_pos.at(value->item).y);
      } else {
        //cout << "Slot #" << (slot_nr + 1) << " => " << "EMPTY" << endl;
        _inv_slot_texts[slot_nr]->update("0");
      }

      slot_nr++;
    }

    //cout << endl;
  }
}

void Player::drop_active_item() {
  if(_inv_slots[_current_inventory_slot] != NULL) {
    _inv_slots[_current_inventory_slot]->quantity--;

    if(_inv_slots[_current_inventory_slot]->quantity <= 0) {
      _inv_slot_texts[_current_inventory_slot]->update("0");
      _inv_slots[_current_inventory_slot] = NULL;
    } else {
      _inv_slot_texts[_current_inventory_slot]->update(format_number(_inv_slots[_current_inventory_slot]->quantity));
    }
  }
}

void Player::drop_active_stack() {
  if(_inv_slots[_current_inventory_slot] != NULL) {
    _inv_slots[_current_inventory_slot]->quantity = 0;
    _inv_slots[_current_inventory_slot] = NULL;
    _inv_slot_texts[_current_inventory_slot]->update("0");
  }
}


int Player::current_inventory_slot() {
  return _current_inventory_slot;
}

void Player::inventory_slot(int new_slot) {
  _current_inventory_slot = constrain(new_slot, 0, (inv_slot_pos.size() - 1));
  UI_active_slot->x(inv_slot_pos[_current_inventory_slot]);
}

void Player::prev_inventory_slot() {
  _current_inventory_slot--;
  if(_current_inventory_slot < 0) _current_inventory_slot = (inv_slot_pos.size() - 1);
  UI_active_slot->x(inv_slot_pos[_current_inventory_slot]);
}

void Player::next_inventory_slot() {
  _current_inventory_slot++;
  if((unsigned) _current_inventory_slot >= inv_slot_pos.size()) _current_inventory_slot = 0;
  UI_active_slot->x(inv_slot_pos[_current_inventory_slot]);
}



uint32_t Player::money() { return _money; }

void Player::money(int amount) {
  if((unsigned) amount > max_money) amount = max_money;
  _money = amount;
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

  int slot_nr = 0;
  for(inv_slot*& value: _inv_slots) {
    if(value != NULL) {
      _inv_slot_images[slot_nr]->render();
      _inv_slot_texts[slot_nr]->render();
    }

    slot_nr++;
  }
}

void Player::render() {
  _character->render();

  for(Skill* value: _skills) {
    value->render();
  }
}
