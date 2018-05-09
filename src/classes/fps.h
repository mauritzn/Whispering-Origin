#ifndef FPS_H
#define FPS_H

class FPS {
  private:
    float _alpha = 0.2;

    uint32_t _frame_count = 0;
    uint32_t _ticks_last = 0;
    int _delta = 0;

    float _frame_time = 0.0;
    float _fps_current = 0.0;
    float _fps_last = 0.0;
    float _delta_time = 0.0;

    void calculate(); // unnecessary (remove in the future?, would be moved to update())


  public:
    FPS();
    void update(); // recalculate values (eg. FPS, delta time)

    uint32_t frame_count(); // get the frame count
    uint32_t ticks(); // get the current SDL Tick count

    float delta_time(); // get current delta time
    float current(); // get the current FPS count
    float prev(); // get the previous FPS count
};

#endif