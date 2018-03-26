#include <iostream>

#include "character.h"

using namespace std;

Character::Character() 
{
    //Set base health and base level
    health = 10;
    char_exp = 0;
    level = 1;
    isAlive = true;
    money = 0;
    // experiencerequired = exp_rate - experience;
}

void Character::setPlayerName()
{
    // Setting playerName to come at later point.
    
}
void Character::alive()
{
    if(health == 0)
    {
        isAlive = false;
    }
}