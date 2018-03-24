#ifndef FPS_H
#define FPS_H

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

    void calculate();


  public:
    FPS();
    void update();

    uint32_t ticks();
    uint32_t ticks_prev();

    float delta_time();
    float get();
    float get_prev();
};

#endif