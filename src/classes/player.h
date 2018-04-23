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
#include "../config.h"

using namespace std;

struct inv_slot {
  items item;
  int quantity = 0;
};


class Player {
  private:
    Window* _win;
    Renderer* _ren;

    PNG* _character;

    int _hp;
    uint32_t _money = 0;

    PNG* UI_active_slot;

    int _current_inventory_slot = 0;
    vector<inv_slot*> _inv_slots;
    vector<Text*> _inv_slot_texts;
    vector<PNG*> _inv_slot_images;

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


    void add_item(items item_to_add);
    void drop_active_item();
    void drop_active_stack();

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
