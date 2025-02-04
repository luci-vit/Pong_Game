#include "../include/racket_player2.hpp"

void RacketPlayer2::updateRacketPositions_pl2()
{
    if (IsKeyDown(KEY_W))
    {
        rectangle_position.y -= speed_y;
    }
    if (IsKeyDown(KEY_S))
    {
        rectangle_position.y += speed_y;
    }

    if (getRacketPosition().y <= 0)
    {
        rectangle_position.y = 0;
    }
    
    if (rectangle_position.y + rectangle_dimensions.y >= GetScreenHeight())
    {
        rectangle_position.y = GetScreenHeight() - rectangle_dimensions.y;
    }
}