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

    string name(); // get the skill's name
    int level(); // get the current level
    int xp(); // get the current xp

    int prev_xp_to_level(); // get the xp that was required to level up last time
    int xp_to_level(); // get the current xp that is required to level up
    void increase_xp(int); // increase the skill's xp, this also check if the cap is reached and increases level
    bool has_leveled_up(); // check if the skill has leveled up, how long is defined using: time_to_display_level_up_message (in config)

    void render(); // render the skill's progress bar and UI text connected to it
};

#endif