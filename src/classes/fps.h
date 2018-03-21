#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <string>
using namespace std;


class FPS {
  private:
    float _alpha = 0.2;
    
    uint32_t _ticks = 0;
    uint32_t _ticks_last = 0;
    int _delta = 0;
    
    float _frame_time = 0.0;
    float _fps_current = 0.0;
    float _fps_last = 0.0;
    float _delta_time = 0.0;
    
    
    void calculate() {
      _ticks_last = _ticks;
      _ticks = SDL_GetTicks();
      _delta = (_ticks - _ticks_last);
      _delta_time = _delta / 1000.0;

      _frame_time = (_alpha * _delta) + ((1.0 - _alpha) * _frame_time);
      _fps_last = _fps_current;
      _fps_current = (1000.0 / _frame_time);
      
      if(_fps_current < 0) _fps_current = 0;
    }

    
  public:
    FPS() {
      this->calculate();
    }
    
    
    void update() {
      this->calculate();
    }
    
    uint32_t ticks() {
      return _ticks;
    }
    
    uint32_t ticks_prev() {
      return _ticks_last;
    }
    
    float delta_time() {
      return _delta_time;
    }
    
    float get() {
      return _fps_current;
    }
    
    float get_prev() {
      return _fps_last;
    }
};