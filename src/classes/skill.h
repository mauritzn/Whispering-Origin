#ifndef SKILL_H
#define SKILL_H

#include <SDL2/SDL.h>
#include <string>

#include "window.h"
#include "renderer.h"
#include "../config.h"
#include "text.h"
#include "progress_bar.h"

using namespace std;


class Skill {
  private:
    Window* _win;
    Renderer* _ren;
    
    string _name;
    SDL_Color _bar_color = { 130, 160, 0 };
    
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
    Skill(Window&, Renderer&, string, int, int, int, int);
    
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