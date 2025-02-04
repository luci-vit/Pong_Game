#ifndef RACKET_PLAYER_HPP
#define RACKET_PLAYER_HPP
#include <raylib.h>

class RacketPlayer
{
// Se criar virtual criar um construtor virtual criar um destrutor virtual
protected:
    Vector2 rectangle_position; 
    Vector2 rectangle_dimensions;
    int speed_y = 5;

public:
    void setRacketPosition(float x, float y);
    Vector2 getRacketPosition();
    void setRacketDimensions(float heigh, float width);
    Vector2 getRacketDimensions();
    void updateRacketPositions();
    void DrawRacket(Color racketColor);
};

#endif