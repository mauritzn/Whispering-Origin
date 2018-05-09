#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include "game.h"
#include "image.h"
#include "skill.h"
#include "text.h"
#include "../config.h"

using namespace std;


class Player {
  private:
    Game* _game;
    Image* _character;

    int _animation_states = 0;
    int _current_animation_state = 0;
    uint32_t _last_animation = 0;

    int _hp;
    uint32_t _money = 0;

    Image* UI_active_slot;

    int _current_inventory_slot = 0;
    vector<inv_slot*> _inv_slots;
    vector<Text*> _inv_slot_texts;
    vector<Image*> _inv_slot_images;

    vector<Skill*> _skills = { NULL, NULL, NULL, NULL, NULL, NULL };


  public:
    Player(Game&);

    int x(); // get the player's x value on the screen (not in the world)
    int y(); // get the player's y value on the screen (not in the world)
    void x(int); // set the player's x value on the screen (not in the world)
    void y(int); // set the player's y value on the screen (not in the world)


    player_direction direction(); // get the player's direction
    void direction(player_direction); // set the player's direction
    void rest_pose(); // reset player's sprite
    void animate(); // animate the player's sprite

    int max_health(); // get the player's health cap
    int health(); // get the player's health
    int level(); // get the player's level
    int xp(); // get the player's main xp

    Skill* skill(string); // get a player's skill, using the skill's name

    void heal(int); // heal the player (increase health)
    void damage(int); // damage the player (decrease health)
    bool is_alive(); // check if the player is alive (health > 0)


    void add_item(items item_to_add); // add an item to the player's inventory
    void drop_active_item(); // drop a single item from the inventory
    void drop_active_stack(); // drop an item stack from the inventory

    int current_inventory_slot(); // get the current inventory slot
    void inventory_slot(int); // set the current inventory slot
    void prev_inventory_slot(); // move to the prev inventory slot
    void next_inventory_slot(); // move to the next inventory slot


    uint32_t money(); // get the player's money amount
    void money(int); // set the player's money amount (0-2m)
    void increase_money(int); // increase the player's money amount (0-2m)
    void decrease_money(int); // decrease the player's money amount (0-2m)

    int xp_to_level(); // get the required xp to level up the player
    void increase_xp(int); // increase the player's main xp
    bool has_leveled_up(); // check if the player has leveled up, how long is defined using: time_to_display_level_up_message (in config)

    void render_inventory(); // render the inventory active slot, slot images, slot nr's
    void render(); // render the player's image and skills
};

#endif