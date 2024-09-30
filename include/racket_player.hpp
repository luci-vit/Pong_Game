#ifndef RACKET_PLAYER_HPP
#define RACKET_PLAYER_HPP
#include <raylib.h>

class RacketPlayer{

private:
    Vector2 rectangle_position;
    Vector2 rectangle_dimensions;
    int speed_y=4;

public:
    void setRacketPosition(int x, int y);
    Vector2 getRacketPosition();
    void setRacketDimensions(int heigh, int width);
    Vector2 getRacketDimensions();
    void updateRacketPositions();
    void DrawRacket();
};

#endif