#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "player.h"
#include "images.h"
#include "../config.h"

using namespace std;

Player::Player(Window& win, Renderer& ren)
{
    _win = &win;
    _ren = &ren;

    _character = new PNG(*_win, *_ren, character_image_path, 0, 300);

    
    for(int i = 1; i <= max_level; i++) {
       _xp_rates.push_back(pow((i * 2), 3));
    }
}


int Player::get_x() { return _character->get_x(); }
int Player::get_y() { return _character->get_y(); }

void Player::set_x(int new_x) { _character->set_x(new_x); }
void Player::set_y(int new_y) { _character->set_y(new_y); }


int Player::health()
{
    return _hp;
}

uint32_t Player::money()
{
    return _money;
}

int Player::level()
{
    return _player_level;
}

int Player::xp()
{
    return _player_xp;
}

void Player::heal(int amount)
{
    _hp += amount;
}

void Player::damage(int amount)
{
  if(amount > 0) {
    if(_hp > 0) {
      if((_hp - amount >= 0)) {
        _hp -= amount;
      } else {
        _hp = 0;
      }
    }
  }
}

bool Player::is_alive()
{
    if(_hp > 0) return true;
    else return false;
}

void Player::increase_money(int amount)
{
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

void Player::decrease_money(int amount)
{
  if(amount > 0) {
    if(_money > 0) {
      if((_money - amount >= 0)) {
        _money -= amount;
      } else {
        _money = 0;
      }
    }
  }
}

void Player::set_money(int amount)
{
    if((unsigned) amount > max_money) amount = max_money;
    _money = amount;
}


int Player::xp_to_level() {
  return _xp_rates[_player_level - 1];
}

void Player::increase_xp(int amount)
{
    if(amount > 0) _player_xp += amount;
}

// Should be removed, should be inside increase_xp (with checks to see if the XP is now above the new level threshold)
void Player::increase_level(int amount)
{
  if(amount > 0) {
    if(_player_level < max_level) {
      if((_player_level + amount) <= max_level) {
          _player_level += amount;
      } else {
        _player_level = max_level;
      }
    }
  }
}

void Player::render()
{
    _character->render();
}

