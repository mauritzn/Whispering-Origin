#include <SDL2/SDL.h>
#include <iostream>

#include "game.h"
#include "../config.h"
#include "functions.h"

using namespace std;

Game::Game() {
  if(init_SDL() != true) {
    cout << "Failed to init SDL!" << endl;
    SDL_Quit();
  }

  init_game();


  SDL_DisplayMode DM;
  SDL_GetCurrentDisplayMode(0, &DM);
  _display_width = DM.w;
  _display_height = DM.h;

  cout << "Display Size: " << _display_width << "x" << _display_height << endl;
  cout << "Window Size: " << window_width << "x" << window_height << endl << endl;


  _fps = new FPS();
  _win = new Window(game_name, ((_display_width / 2) - (window_width / 2)), ((_display_height / 2) - (window_height / 2)), window_width, window_height);
  _ren = new Renderer(*_win, color_game_background);

  _player = new Player(*this);
  _world = new World(*this);
  _ui = new UI(*this);

  SDL_Surface* icon = IMG_Load(icon_path);
  SDL_SetWindowIcon(_win->get(), icon);

  _running = true;
}

Game::~Game() {
  for(const auto& value : fonts) {
    TTF_CloseFont(value.second);
  }

  TTF_Quit();
  SDL_Quit();
  cout << ">> Bye Bye! <<" << endl << endl;
}


bool Game::running() { return _running; }
void Game::running(bool new_state) { _running = new_state; }

SDL_Event* Game::event() { return &_event; }
uint32_t Game::event_type() { return _event.type; }
SDL_Keycode Game::event_key() { return _event.key.keysym.sym; }

void Game::catch_events() {
  while(SDL_PollEvent(this->event())) {
    if(this->event_type()== SDL_QUIT) this->running(false);
    else if(this->event_type() == SDL_KEYDOWN || this->event_type() == SDL_KEYUP) {
      if(this->event_type() == SDL_KEYDOWN) this->press_key(this->event_key());
      else if(this->event_type() == SDL_KEYUP) this->release_key(this->event_key());
    } else {
      //if(this->event_type() != 1024 && this->event_type() != 512) cout << ">> Event: " << this->event_type() << endl;
    }
  }
}


Window* Game::window() { return _win; }
Renderer* Game::renderer() { return _ren; }
FPS* Game::fps() { return _fps; }
Player* Game::player() { return _player; }
World* Game::world() { return _world; }
UI* Game::ui() { return _ui; }


void Game::window(Window& win) { _win = &win; }
void Game::renderer(Renderer& ren) { _ren = &ren; }
void Game::fps(FPS& fps) { _fps = &fps; }
void Game::player(Player& player) { _player = &player; }
void Game::world(World& world) { _world = &world; }
void Game::ui(UI& ui) { _ui = &ui; }


int Game::display_width() { return _display_width; }
int Game::display_height() { return _display_height; }


void Game::press_key(SDL_Keycode key) {
  _pressed_keys[key] = true;
}

void Game::release_key(SDL_Keycode key) {
  _pressed_keys[key] = false;
  _key_timeouts[key] = 0;
}

bool Game::key_pressed(SDL_Keycode key) {
  auto search = _pressed_keys.find(key);

  if(search != _pressed_keys.end()) {
    return _pressed_keys.at(key);
  } else {
    return false;
  }
}

bool Game::key_ready(SDL_Keycode key) {
  return key_ready(key, 100);
}

bool Game::key_ready(SDL_Keycode key, uint32_t timeout) {
  if(this->key_pressed(key)) {
    while(SDL_TICKS_PASSED(_fps->ticks(), _key_timeouts[key])) {
      _key_timeouts[key] = (_fps->ticks() + timeout);
      return true;
    }

    return false;
  } else {
    return false;
  }
}


void Game::check_keys() {
  if(this->key_ready(SDLK_F1, 250)) debug_mode = !debug_mode;

  if(this->key_ready(SDLK_F5)) _player->increase_xp(5);
  if(this->key_ready(SDLK_F6)) _player->skill("Woodcutting")->increase_xp(5);
  if(this->key_ready(SDLK_F7)) _player->skill("Mining")->increase_xp(5);
  if(this->key_ready(SDLK_F8)) _player->skill("Smithing")->increase_xp(5);
  if(this->key_ready(SDLK_F9)) _player->skill("Fishing")->increase_xp(5);
  if(this->key_ready(SDLK_F10)) _player->skill("Cooking")->increase_xp(5);


  if(this->key_ready(keys.at("inv_prev"))) {
    _player->prev_inventory_slot();
  }

  if(this->key_ready(keys.at("inv_next"))) {
    _player->next_inventory_slot();
  }

  if(this->key_ready(keys.at("drop_key"))) {
    if(this->key_pressed(SDLK_LSHIFT) || this->key_pressed(SDLK_RSHIFT)) {
      _player->drop_active_stack();
    } else {
      _player->drop_active_item();
    }
  }
}


void Game::update() {
  this->check_keys();

  this->fps()->update();
  this->world()->update();
  this->ui()->update();
}


void Game::render() {
  this->renderer()->clear();

  this->world()->render();
  this->ui()->render();
  this->player()->render_inventory();

  this->renderer()->update(); // update the screen
}
