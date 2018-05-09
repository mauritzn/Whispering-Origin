#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

// forward declarations
class Game;
class Image;
class Text;
class Skill;
class Progress;
class Tile;
class UI;

#include <map>
#include "window.h"
#include "renderer.h"
#include "fps.h"
#include "player.h"
#include "world.h"
#include "ui.h"

using namespace std;


class FPS;
class Player;
class World;

class Game {
  private:
    Window* _win = NULL;
    Renderer* _ren = NULL;
    FPS* _fps = NULL;
    Player* _player = NULL;
    World* _world = NULL;
    UI* _ui = NULL;

    int _display_width = 0;
    int _display_height = 0;

    bool _running = false;
    SDL_Event _event;

    map<SDL_Keycode, bool> _pressed_keys;
    map<SDL_Keycode, uint32_t> _key_timeouts;


  public:
    Game();
    ~Game();

    bool running(); // check if the game is running
    void running(bool); // set wether the game is running or not

    SDL_Event* event(); // get the game's SDL event variable
    uint32_t event_type(); // get the current type stored in the event()
    SDL_Keycode event_key(); // get the current key stored in the event()
    void catch_events(); // detect event changes, like: change in type, key press/release, update the game's event variable

    Window* window(); // get the game's Window instance
    Renderer* renderer(); // get the game's Renderer instance
    FPS* fps(); // get the game's FPS instance
    Player* player(); // get the game's Player instance
    World* world(); // get the game's World instance
    UI* ui(); // get the game's UI instance

    void window(Window&); // set the game's Window instance
    void renderer(Renderer&); // set the game's Renderer instance
    void fps(FPS&); // set the game's FPS instance
    void player(Player&); // set the game's Player instance
    void world(World&); // set the game's World instance
    void ui(UI&); // set the game's UI instance

    int display_width(); // get the displays width
    int display_height(); // get the displays height

    void press_key(SDL_Keycode); // mark key as pressed
    void release_key(SDL_Keycode); // unmark key as pressed
    bool key_pressed(SDL_Keycode); // check if a key is marked as pressed
    bool key_ready(SDL_Keycode); // check if a key is marked as pressed and 100ms has passed since last press
    bool key_ready(SDL_Keycode, uint32_t); // check if a key is marked as pressed and a certain amount of time has passed since last press

    void check_keys(); // check if game keys are pressed
    void update(); // updates the game's FPS, World and UI instance
    void render(); // clear the renderer, render the game's World, UI and Player instance
};

#endif