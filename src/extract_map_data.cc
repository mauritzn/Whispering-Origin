/*
 * ## Required dependencies ##
 *  - SDL2
 *
 * ## Installation ##
 *  Use the bundled install file to install the dependencies
 *  > sudo sh ./_install_dependencies.sh
 *
 *  or do it manually using:
 *  > sudo apt-get install libsdl2-dev
 *
 *
 * ## Tested on ##
 *  - Ubuntu 17.10.1
 */
#include <SDL2/SDL.h>

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <map>

#include "config.h"
#include "classes/functions.h"
using namespace std;


enum grid_pixel_type {
  P_PLAYER = 20522055,
  P_COLLIDER = 245245245,
  P_GRASS = 6517050, // unused
  P_WATER = 20105155 // unused
};



int to_grid_row(int y, int grid_size) {
  return floor(y / grid_size);
}

int to_grid_col(int x, int grid_size) {
  return floor(x / grid_size);
}


int to_grid_x(int col, int grid_size) {
  return (col * grid_size);
}

int to_grid_y(int row, int grid_size) {
  return (row * grid_size);
}





int main() {
  const string map_to_use = "images/maps/main_data.bmp";
  const string save_to = "maps/main.map";
  ofstream map_file;

  int current_x = 0;
  int current_y = 0;

  int grid_size = 32; // default grid size (used if none is found in data file)
  bool player_pos_found = false;

  bool parsing = true;


  SDL_Surface* surface = SDL_LoadBMP(map_to_use.c_str());

  if(surface == NULL) {
    cout << "SDL_LoadBMP Error: " << SDL_GetError() << endl;
    SDL_Quit();
  } else {
    cout << "Extracting map data from image..." << endl << endl;

    const int map_width = surface->w;
    const int map_height = surface->h;


    SDL_Color current_color = { 255, 255, 255, 255 };
    int player_pos_x = floor(map_width / 2); // default (if none is found in data file)
    int player_pos_y = floor(map_height / 2); // default (if none is found in data file)

    grid_pixel_type current_grid_type;
    grid_tile_type current_tile_type;

    int coliders_found = 0;
    map<grid_tile_type, int> found_count {
      { TREE, 0 },
      { ORE, 0 },
      { FISH, 0 }
    };

    stringstream* current_stream = NULL;
    stringstream player;
    player << "P:"; // Player

    stringstream NPCs;
    NPCs << "N:"; // NPCs (unused ATM)

    stringstream monsters;
    monsters << "M:"; // Monsters (unused ATM)


    stringstream colliders;
    colliders << "C:"; // Colliders

    stringstream trees;
    trees << "T:"; // Trees

    stringstream ores;
    ores << "O:"; // Ores

    stringstream fish;
    fish << "F:"; // Fish



    while(parsing) {
      if(get_RGB(current_color, surface, current_x, current_y)) {
        current_grid_type = (grid_pixel_type) concat_RGB(current_color);

        if(current_x == 0 && current_y == 0) {
          grid_size = constrain((int) current_color.r, 6, 252);
        }


        if(current_grid_type == P_COLLIDER) {
          if(get_RGB(current_color, surface, (current_x + 1), (current_y + 1))) {
            if(is_valid_tile(concat_RGB(current_color))) {
              grid_tile_data current_tile_data = (grid_tile_data) concat_RGB(current_color);
              current_tile_type = get_tile_type(current_tile_data);

              if(current_tile_type == TREE) {
                current_stream = &trees;
              } else if(current_tile_type == ORE) {
                current_stream = &ores;
              } else if(current_tile_type == FISH) {
                current_stream = &fish;
              }

              if(current_stream != NULL) {
                if(found_count.at(current_tile_type) > 0) {
                  *current_stream << "|";
                }
                found_count.at(current_tile_type)++;

                *current_stream << to_grid_row(current_y, grid_size) << "x" << to_grid_col(current_x, grid_size)
                                << ":" << current_tile_data;
              }

              current_stream = NULL;
            } else {
              if(coliders_found > 0) colliders << "|";
              colliders << to_grid_row(current_y, grid_size) << "x" << to_grid_col(current_x, grid_size);
              coliders_found++;
            }
          }
        } else if(current_grid_type == P_PLAYER && player_pos_found == false) {
          player_pos_x = current_x;
          player_pos_y = current_y;
          player_pos_found = true;
        }


        current_x += grid_size;
        if(current_x >= map_width) {
          if((current_y + grid_size) < map_height) {
            current_x = 0;
            current_y += grid_size;
          } else {
            parsing = false;
          }
        }
      } else {
        parsing = false;
        cout << "Failed to grab RGB!" << endl;
      }
    }



    map_file.open(save_to.c_str());
    map_file << map_width << "x" << map_height
             << ":" << grid_size << endl << endl;

    if(player_pos_found) {
      player << to_grid_row(player_pos_y, grid_size) << "x" << to_grid_col(player_pos_x, grid_size);
    } else {
      // add check to see if the default (center) pos is on ground
    }



    player << endl;
    NPCs << endl;
    monsters << endl << endl;

    colliders << endl;
    trees << endl;
    ores << endl;
    fish << endl;


    map_file << player.str();
    map_file << NPCs.str();
    map_file << monsters.str();

    map_file << colliders.str();
    map_file << trees.str();
    map_file << ores.str();
    map_file << fish.str();



    cout << "Grid size found: " << grid_size << endl
         << "Colliders found: " << coliders_found << endl
         << "Trees found: " << found_count.at(TREE) << endl
         << "Ores found: " << found_count.at(ORE) << endl
         << "Fish found: " << found_count.at(FISH) << endl
         << endl << endl;

    cout << ">> Map width: " << map_width << ", Map height: " << map_height << " <<" << endl << endl;
    SDL_FreeSurface(surface);
    map_file.close();
  }
}
