#include <SDL2/SDL.h>

#include <iostream>
#include <string>
#include <ctime>

#include "monster.h"
#include "images.h"


Monster::Monster(Window& win, Renderer& ren)
{
    _win = &win;
    _ren = &ren;

    _acc = 7;
    
    srand(time(NULL)); // For damage-dealing
}

bool Monster::is_alive()
{
    if(_hp > 0) return true;
    else return false;
}

// Monster uses the same type of taking damage in a fight as the player.
void Monster::take_damage(int amount)
{
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

int Monster::deal_damage()
{
    int chance = rand() % 10;
    if(chance < this->get_accuracy()) {
        return rand() % _max_dmg + _min_dmg;
    } else {
        return 0;
    }
}

int Monster::give_reward()
{
   return reward_money; 
}

void Monster::set_damage(int max_dmg, int min_dmg)
{
    _max_dmg = this->get_level() + max_dmg;
    _min_dmg = this->get_level() + min_dmg;
}

void Monster::set_level(int level)
{
    _level = level;
}

int Monster::get_level()
{
    return _level;
}

void Monster::set_accuracy(int accuracy)
{
    _acc = accuracy;
}

int Monster::get_accuracy()
{
    return _acc;
}

void Monster::render()
{
    _monster->render();
}
