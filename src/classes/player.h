#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include<iostream>
#include <vector>

#include "window.h"
#include "renderer.h"
#include "image.h"
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

    Image* _character;

    int _hp;
    uint32_t _money = 0;

    Image* UI_active_slot;

    int _current_inventory_slot = 0;
    vector<inv_slot*> _inv_slots;
    vector<Text*> _inv_slot_texts;
    vector<Image*> _inv_slot_images;

    vector<Skill*> _skills = { NULL, NULL, NULL, NULL, NULL, NULL };


  public:
    Player(Window&, Renderer&);

    int x();
    int y();

    void x(int);
    void y(int);


    player_direction direction();
    void direction(player_direction);

    int max_health();
    int health();
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
    void inventory_slot(int);
    void prev_inventory_slot();
    void next_inventory_slot();


    uint32_t money();
    void money(int);
    void increase_money(int);
    void decrease_money(int);

    int xp_to_level();
    void increase_xp(int);
    bool has_leveled_up();

    void render_inventory();
    void render();
};

#endif
