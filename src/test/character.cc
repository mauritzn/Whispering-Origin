#include <iostream>
#include "math.h"

#include "character.h"
using namespace std;

Character::Character()
{
  // Base Health, Level and Experience.
  health = 10;
  level = 1;
  experience = 10;
  
  posX = -50;
  posY = -50;
  
  // Always updated.
  experienceRequired = this->nextLevel(); 
}


void Character::exp_rate()
{
  // Setting static exp_rate for character.
  for(int i = 1; i <= 50; i++)
  {
    xp_rate[i] = pow((i * 2), 3);
  }
}

int character::nextLevel()
{
  int next = xp_rate[level] - experience;
  
  return next;
}

void Character::setPlayerName()
{
  cout << "Please enter your Name: ";
  cin >> playerName;
  
  cout << "Your name is: " << playerName;
}
