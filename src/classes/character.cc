#include <iostream>

#include "character.h"
#include "images.h"

using namespace std;

Character::Character(Window& win, Renderer& ren) 
{
    // Win & Ren for future sprite
    _win = &win;
    _ren = &ren;
    
    //Set base health and base level
    _health = 10;
    _char_exp = 0;
    _level = 1;
    _money = 0;

}

int Character::health()
{
    return _health;
}

int Character::char_exp()
{
    return _char_exp;
}

int Character::level()
{
    return _level;
}

int Character::money()
{
    return _money;
}

