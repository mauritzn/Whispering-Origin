#ifndef ITEM_H
#define ITEM_H

#include <SDL2/SDL.h>
#include <string>

#include "window.h"
#include "renderer.h"
#include "images.h"
#include "../config.h"
#include "player.h"

using namespace std;


class Item {
  private:
    Window* _win;
    Renderer* _ren;
    //World* _world; // used to get the grid size of the world
    Player* _player; // (will be) used to get the players tool/level/inventory

    PNG* _item_image;
    
    string _item_name;
    
    int _x_start = 0;
    int _x_end = 0;
    int _y_start = 0;
    int _y_end = 0;
    
    int _row;
    int _col;
    string _row_and_col;
    
    tile_type _type;
    int _id;
    
    int _resources; // how much resources can the player get from this item (in total)
    int _resources_left;
    
    int _depleted_at; // used to see if an item has depleted all it's resources and when it happend (-1 = not depleted, > 0 = depleted)
    int _last_action_at; // used to see when an action was last taken (will be used for timing the deplition)


  public:
    Item(Window&, Renderer&, Player&, const tile_type&, const int, int, int);
    
    int width();
    int height();
    
    int get_x_start();
    int get_x_end();
    
    int get_y_start();
    int get_y_end();
    
    
    int get_original_x();
    int get_original_y();
    
    void set_x(int);
    void set_y(int);
    
    
    void set_row(int);
    void set_col(int);
    
    int get_row();
    int get_col();
    string get_row_and_col();
    
    
    string get_item_name();
    tile_type get_type();
    int get_id();
    
    
    void action();
    void show_progress();
    
    void update();
    void render();
};

#endif