#include <SDL2/SDL.h>

#include <iostream>
// #include <string>
// #include <vector>

#include "world.h"
#include "functions.h"
#include "images.h"
#include "../config.h"
#include "fps.h"
#include "player.h"

using namespace std;


World::World(Window& win, Renderer& ren, FPS& fps, Player& player) {
  _win = &win;
  _ren = &ren;
  _fps = &fps;
  _player = &player;

  _texture = new PNG(*_win, *_ren, world_texture_path, 0, 0);
  
  
  // min value is 0
  // max value is -640 ((window_width / 2) * -1)
  _texture->set_absolute_x((window_width / 4) * -1); // center
  
  // min value is 0
  // max value is -360 ((window_height / 2) * -1)
  _texture->set_absolute_y((window_height / 4) * -1); // center
  
  _x = (float) _texture->get_x();
  _y = (float) _texture->get_y();
}


int World::get_x() { return _texture->get_x(); }
int World::get_y() { return _texture->get_y(); }

void World::set_x(int new_x) { _texture->set_x(new_x); }
void World::set_y(int new_y) { _texture->set_y(new_y); }


void World::key_pressed(SDL_Keycode key) {
  if(key == SDLK_w) _moving_up = true;
  if(key == SDLK_s) _moving_down = true;
  if(key == SDLK_a) _moving_left = true;
  if(key == SDLK_d) _moving_right = true;
}

void World::key_released(SDL_Keycode key){
  if(key == SDLK_w) _moving_up = false;
  if(key == SDLK_s) _moving_down = false;
  if(key == SDLK_a) _moving_left = false;
  if(key == SDLK_d) _moving_right = false;
}


void World::update() {
  float delta_velocity = (world_velocity * _fps->delta_time());
  
  if(_moving_up) {
    _y += delta_velocity;
    _texture->set_absolute_y((int) _y);
  }
  
  if(_moving_down) {
    _y -= delta_velocity;
    _texture->set_absolute_y((int) _y);
  }

  
  if(_moving_left) {
    _x += delta_velocity;
    _texture->set_absolute_x((int) _x);
  }
  
  if(_moving_right) {
    _x -= delta_velocity;
    _texture->set_absolute_x((int) _x);
  }
}

void World::render() {
  _texture->render();
}