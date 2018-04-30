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

  SDL_Surface* icon = IMG_Load(icon_path);
  SDL_SetWindowIcon(_win->get(), icon);
}


Window* Game::window() { return _win; }
Renderer* Game::renderer() { return _ren; }
FPS* Game::fps() { return _fps; }
Player* Game::player() { return _player; }
World* Game::world() { return _world; }


void Game::window(Window& win) { _win = &win; }
void Game::renderer(Renderer& ren) { _ren = &ren; }
void Game::fps(FPS& fps) { _fps = &fps; }
void Game::player(Player& player) { _player = &player; }
void Game::world(World& world) { _world = &world; }


int Game::display_width() { return _display_width; }
int Game::display_height() { return _display_height; }


void Game::render() {}
