#include <iostream>

#include "character.h"
#include <vector>
#include "images.h"

using namespace std;

Character::Character() 
{
    
    //Set base health and base level
    _health = 10;
    _char_exp = 0;
    _level = 1;
    _money = 0;

    for(int i = 1; i <= 50; i++) {
       _xp_rate.push_back(pow((i * 2), 3));
    }
}

int Character::exp_rate()
{
    return _xp_rate[_level - 1];
}

int Character::levels()
{
    return _xp_rate.size();
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

Character::~Character()
{

}
