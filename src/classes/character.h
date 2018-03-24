/* Character.h as Player class */
#include <string>
#include <iostream>

using namespace std;

class Character 
{
    public:
        // Constructor
        Character();

        int health;
        int experience;
        int level;
        int posX;
        int posY;
        int experiencerequired;
        bool isAlive(); // defining if dead or alive.
        string playerName;
        
        // more functions to come.
        void setPlayerName();
};
