#ifndef SKILL_H
#define SKILL_H

#include <SDL2/SDL.h>
#include <string>

#include "window.h"
#include "renderer.h"
#include "../config.h"
#include "text.h"

using namespace std;


class Skill {
  private:
    Window* _win;
    Renderer* _ren;
    
    string _name;
    
    uint32_t _leveled_up_at = 0;
    int _level = 1;
    int _xp = 0;


  public:
    Skill(Window&, Renderer&, string);
    
    string name();
    
    
    int level();
    int xp();
    
    int xp_to_level();
    void increase_xp(int);
    bool has_leveled_up();
    
    
    void render();
};

#endif