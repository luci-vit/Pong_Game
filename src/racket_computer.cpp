#include "../include/racket_computer.hpp"

void RacketComputer::setRacketPosition(float x, float y){
    this->rectangle_position.x = x;
    this->rectangle_position.y = y;
}

Vector2 RacketComputer::getRacketPosition(){
    return this->rectangle_position;
}

void RacketComputer::setRacketDimensions(float heigh, float width){
    this->rectangle_dimensions.x = heigh;
    this->rectangle_dimensions.y = width; 
}

Vector2 RacketComputer::getRacketDimensions(){
    return this->rectangle_dimensions;
}

void RacketComputer::updateRacketPositions(Vector2 ball_position)
{
    // int ball_position = ball.getCirclePosition().y;

    if(ball_position.y > this->getRacketPosition().y + this->getRacketDimensions().y/2){
        rectangle_position.y += speed_y;
    }

    if(ball_position.y <= this->getRacketPosition().y + this->getRacketDimensions().y/2){
        rectangle_position.y -= speed_y;
    }

    if(rectangle_position.y <=0){ //Impede que a raquete ultrapasse a borda superior;
        rectangle_position.y = 0;
    }
    if(rectangle_position.y + rectangle_dimensions.y >= GetScreenHeight()){ //Impede que a raquete ultrapasse a borda inferior;
        rectangle_position.y = GetScreenHeight()-rectangle_dimensions.y;
    }
}

void RacketComputer::DrawRacket(){
    DrawRectangleV(getRacketPosition(), getRacketDimensions(), WHITE);
}