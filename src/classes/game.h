#ifndef GAME_H
#define GAME_H

// forward declarations
class Game;
class Image;
class Text;
class Skill;
class Progress;
class Tile;

#include "window.h"
#include "renderer.h"
#include "fps.h"
#include "player.h"
#include "world.h"

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

    int _display_width = 0;
    int _display_height = 0;


  public:
    Game();

    Window* window();
    Renderer* renderer();
    FPS* fps();
    Player* player();
    World* world();

    void window(Window&);
    void renderer(Renderer&);
    void fps(FPS&);
    void player(Player&);
    void world(World&);

    int display_width();
    int display_height();

    void render();
};

#endif
