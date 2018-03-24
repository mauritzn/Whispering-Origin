#include <iostream>

#include "character.h"

using namespace std;

Character::Character() 
{
    //Set base health and base level
    health = 10;
    experience = 0;

    // experiencerequired = exp_rate - experience;
}

void Character::setPlayerName()
{
    // Setting playerName to come at later point.
}
