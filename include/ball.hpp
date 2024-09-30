//Essa lib é responsável pela manipulação das variáveis que correspondem a bola e a sua construção.

#ifndef BALL_HPP
#define BALL_HPP

#include <raylib.h>
#include <iostream>
#include "racket_player.hpp"

using namespace std;

class Ball {
    private:
        Vector2 circle_position;
        int circle_radius;
        int speed_x=6, speed_y=6;
        RacketPlayer racketPlayer;

    public:
        void setCirclePosition(int x, int y);
        Vector2 getCirclePosition();
        void setCircleRadius(int x);
        int getCircleRadius();
        void drawnCircle();
        void updatePosition();
};

#endif