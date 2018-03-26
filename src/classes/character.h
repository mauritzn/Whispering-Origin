/* Character.h as Player class */
#include <string>
#include <iostream>

using namespace std;

class Character 
{
    private:
        int health;
        int char_exp;
        int level;
        int money;
        int posX;
        int posY;
        int experiencerequired;
        bool isAlive; // defining if dead or alive.
        string playerName;
    
    public:
        // Constructor
        Character();
        
        // more functions to come.
        void setPlayerName();
        void alive();
};
