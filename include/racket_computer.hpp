#ifndef RACKET_COMPUTER_HPP
#define RACKET_COMPUTER_HPP

#include "racket_player.hpp"
#include "ball.hpp" 

class RacketComputer: public RacketPlayer {
private:
    Vector2 rectangle_position;
    Vector2 rectangle_dimensions;
    int speed_y=5;
    Ball ball;
public:
    void setRacketPosition(float x, float y);
    Vector2 getRacketPosition();
    void setRacketDimensions(float heigh, float width);
    Vector2 getRacketDimensions();
    void updateRacketPositions(Vector2 ball_position);
    void DrawRacket();
};
#endif