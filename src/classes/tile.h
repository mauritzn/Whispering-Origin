#ifndef TILE_H
#define TILE_H

#include <SDL2/SDL.h>
#include <string>

#include "window.h"
#include "renderer.h"
#include "images.h"
#include "../config.h"
#include "fps.h"
#include "player.h"
#include "text.h"

using namespace std;


class Tile {
  private:
    Window* _win;
    Renderer* _ren;
    FPS* _fps; // used to get delta time
    //World* _world; // used to get the grid size of the world
    Player* _player; // (will be) used to get the players tool/level/inventory

    PNG* _tile_image;
    Text* _progress_text;
    int _tile_grid_size = 32;

    string _tile_name = "";

    int _x_start = 0;
    int _x_end = 0;
    int _y_start = 0;
    int _y_end = 0;

    int _row = 0;
    int _col = 0;
    string _row_and_col = "0x0";

    tile_type _type;
    int _id = 0;

    int _resources = 0; // how much resources can the player get from this tile (in total)
    int _resources_left = 0;

    uint32_t _depleted_at = 0; // used to see if an tile has depleted all it's resources and when it happend (-1 = not depleted, > 0 = depleted)
    uint32_t _last_action_at = 0; // used to see when an action was last taken (will be used for timing the deplition)


  public:
    Tile(Window&, Renderer&, FPS&, Player&, const tile_type&, const int, int, int);

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


    string get_tile_name();
    tile_type get_type();
    int get_id();


    void action();
    bool action_on_cooldown();
    void show_progress();

    void update();
    void render();
};

#endif
