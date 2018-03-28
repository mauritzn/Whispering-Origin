#include <iostream>
#include "math.h"
#include <string>
using namespace std;

class Character
{
    private:
        int health;
        int experience;
        int xp_rate[51];
        int level;
        int posX;
        int posY;
        int experienceRequired;
        string playerName;
    
    public:
        void setPlayerName();
        void increaseExperience();
        void setHealth();
        void usePotion();
        void exp_rate();
        int nextLevel();
        int getHealth();
        string getPlayerName();
};
