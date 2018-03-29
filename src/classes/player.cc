#include <iostream>
#include <string>

#include "player.h"
#include "images.h"
#include "../config.h"

using namespace std;

Player::Player(Window& win, Renderer& ren)
{
    _win = &win;
    _ren = &ren;

    _character(_win, _ren, character_image_path, -50, -50);

}

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
    if(_hp != 0)
        _hp -= amount;
}

bool Player::is_alive()
{
    if(_hp != 0)
    {
        return true;
    }
    return false;
}

void Player::increase_money(int amount)
{
   if(_money < max_money)
       if((_money += amount) != max_money)
           _money += amount;
}

void Player::decrease_money(int amount)
{
   if(amount > 0)
       if((_money -= amount) != (uint32_t) -1)
           _money -= amount;
}

void Player::set_money(int amount)
{
    _money = amount;
}

void Player::increase_xp(int amount)
{
    if(amount > 0) _player_xp += amount;
}

void Player::increase_level(int amount)
{
    if((_player_level += amount) != max_level)
        _player_level += amount;
}

void Player::render()
{
    _character->render();
}

