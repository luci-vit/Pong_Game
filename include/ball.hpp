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
        Color green_ball = {210, 255, 79, 255};

    public:
        void setCirclePosition(float x, float y);
        Vector2 getCirclePosition();
        void setCircleRadius(float x);
        int getCircleRadius();
        void drawnCircle();
        int updatePosition();
        void setSpeedCollisionX();
        void setSpeedCollisionY();
};

#endif