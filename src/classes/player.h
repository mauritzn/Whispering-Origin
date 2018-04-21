#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include<iostream>
#include <vector>

#include "window.h"
#include "renderer.h"
#include "images.h"
#include "skill.h"

using namespace std;

enum player_direction {
  NORTH = 0,
  SOUTH = 128,
  WEST = 64,
  EAST = 192
};


enum inventory_slots {
  TOOL_1 = 300,
  TOOL_2 = 342,
  TOOL_3 = 384,
  TOOL_4 = 426,
  
  SLOT_1 = 475,
  SLOT_2 = 517,
  SLOT_3 = 559,
  SLOT_4 = 601,
  SLOT_5 = 643,
  SLOT_6 = 685,
  SLOT_7 = 727,
  SLOT_8 = 769,
  SLOT_9 = 811,
  SLOT_10 = 853,
  SLOT_11 = 895,
  SLOT_12 = 937
};


enum skill_anchor {
  PLAYER_SKILL,
  WOODCUTTING_SKILL,
  MINING_SKILL,
  SMITHING_SKILL,
  FISHING_SKILL,
  COOKING_SKILL
};



class Player {
  private:
    Window* _win;
    Renderer* _ren;
    
    PNG* _character;
    
    int _hp;
    uint32_t _money = 0;
    int _acc = 7;   // Player Accuracy
    
    PNG* UI_active_slot;
    
    int _current_inventory_slot = 0;
    vector<inventory_slots> _inv_slots = {
      SLOT_1, SLOT_2, SLOT_3, SLOT_4, SLOT_5, SLOT_6, SLOT_7, SLOT_8, SLOT_9, SLOT_10, SLOT_11, SLOT_12
    };
    
    vector<Skill*> _skills = { NULL, NULL, NULL, NULL, NULL, NULL };


  public:
    Player(Window&, Renderer&);
    
    int get_x();
    int get_y();
    
    void set_x(int);
    void set_y(int);
    
    
    player_direction get_direction();
    void set_direction(player_direction);
    
    int max_health();
    int health();
    uint32_t money();
    int level();
    int xp();
    
    Skill* skill(string);
    
    void heal(int);
    void damage(int);
    bool is_alive();
    
    
    int current_inventory_slot();
    void set_inventory_slot(int);
    void prev_inventory_slot();
    void next_inventory_slot();
    
    
    void increase_money(int);
    void decrease_money(int);
    void set_money(int);
    
    int xp_to_level();
    void increase_xp(int);
    bool has_leveled_up();
    
    void render_inventory();
    void render();
};

#endif