#include "../include/racket_computer.hpp"

void RacketComputer::updateRacketCompPositions(Vector2 ball_position)
{
    if(ball_position.y > getRacketPosition().y + this->getRacketDimensions().y/2){
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
