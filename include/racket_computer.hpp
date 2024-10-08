#ifndef RACKET_COMPUTER_HPP
#define RACKET_COMPUTER_HPP
#include "racket_player.hpp"
#include "ball.hpp" 

class RacketComputer : public RacketPlayer{
private:

public:
    void updateRacketCompPositions(Vector2 ball_position);
};
#endif