#ifndef SKILL_H
#define SKILL_H

#include <string>

#include "game.h"
#include "text.h"
#include "progress_bar.h"
#include "../config.h"

using namespace std;


class Skill {
  private:
    Game* _game;
    string _name;

    uint32_t _leveled_up_at = 0;
    int _level = 1;
    int _xp = 0;

    Progress* _progress;
    int _progress_x = 0;
    int _progress_y = 0;

    Text* _name_text;
    Text* _level_text;
    Text* _xp_text;


  public:
    Skill(Game&, string, int, int, int, int);

    string name();


    int level();
    int xp();

    int prev_xp_to_level();
    int xp_to_level();
    void increase_xp(int);
    bool has_leveled_up();


    void render();
};

#endif
