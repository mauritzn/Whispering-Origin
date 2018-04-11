#include <SDL2/SDL.h>
#include "fps.h"
using namespace std;


FPS::FPS() {
  this->calculate();
}


void FPS::calculate() {
  _ticks_last = _ticks;
  _ticks = SDL_GetTicks();
  _delta = (_ticks - _ticks_last);
  _delta_time = _delta / 1000.0;

  _frame_time = (_alpha * _delta) + ((1.0 - _alpha) * _frame_time);
  _fps_last = _fps_current;
  _fps_current = (1000.0 / _frame_time);

  if(_fps_current < 0) _fps_current = 0;
}

void FPS::update() {
  this->calculate();
  _frame_count++;
}


uint32_t FPS::frame_count() {
  return _frame_count;
}

uint32_t FPS::ticks() {
  return _ticks;
}

uint32_t FPS::ticks_prev() {
  return _ticks_last;
}

float FPS::delta_time() {
  return _delta_time;
}

float FPS::get() {
  return _fps_current;
}

float FPS::get_prev() {
  return _fps_last;
}
