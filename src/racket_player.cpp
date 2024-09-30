#include "../include/racket_player.hpp"

void RacketPlayer::setRacketPosition(int x, int y){
    this->rectangle_position.x = x;
    this->rectangle_position.y = y;
}

Vector2 RacketPlayer::getRacketPosition(){
    return this->rectangle_position;
}

void RacketPlayer::setRacketDimensions(int heigh, int width){
    this->rectangle_dimensions.y = width; 
    this->rectangle_dimensions.x = heigh;
}

Vector2 RacketPlayer::getRacketDimensions(){
    return this->rectangle_dimensions;
}

void RacketPlayer::updateRacketPositions(){

    if (IsKeyDown(KEY_W))
    {
        rectangle_position.y -= speed_y;
    }
    if (IsKeyDown(KEY_S))
    {
        rectangle_position.y += speed_y;
    }

    if(rectangle_position.y <=0){ //Impede que a raquete ultrapasse a borda superior;
        rectangle_position.y = 0;
    }
    if(rectangle_position.y + rectangle_dimensions.y >= GetScreenHeight()){ //Impede que a raquete ultrapasse a borda inferior;
        rectangle_position.y = GetScreenHeight()-rectangle_dimensions.y;
    }
}

void RacketPlayer::DrawRacket(){
    DrawRectangleV(getRacketPosition(), getRacketDimensions(), WHITE);
}