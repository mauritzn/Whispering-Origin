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

    bool running();
    void running(bool);

    SDL_Event* event();
    uint32_t event_type();
    SDL_Keycode event_key();
    void catch_events();

    Window* window();
    Renderer* renderer();
    FPS* fps();
    Player* player();
    World* world();
    UI* ui();

    void window(Window&);
    void renderer(Renderer&);
    void fps(FPS&);
    void player(Player&);
    void world(World&);
    void ui(UI&);

    int display_width();
    int display_height();

    void press_key(SDL_Keycode);
    void release_key(SDL_Keycode);
    bool key_pressed(SDL_Keycode);
    bool key_ready(SDL_Keycode);
    bool key_ready(SDL_Keycode, uint32_t);

    void check_keys();
    void update();
    void render();
};

#endif
