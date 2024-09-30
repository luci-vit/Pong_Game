#include <raylib.h>
#include <iostream>
#include "../include/ball.hpp"
#include "../include/racket_player.hpp"
#include "../include/racket_computer.hpp"

using namespace std;
Ball ball;
RacketPlayer racketPlayer;
RacketComputer racketComputer;

int main(){
    //Construindo as dimensões da tela. 
    const int screen_width = 1280;
    const int screen_heigh = 800;
    
    //Construindo a dimensão do círculo e sua posição.
    ball.setCircleRadius(20);
    ball.setCirclePosition(640, 400);
    Vector2 ball_position;


    //Construindo as dimensões das "raquetes" e suas respectivas posições.
    racketPlayer.setRacketDimensions(20,120);
    racketComputer.setRacketDimensions(20, 120);
    racketPlayer.setRacketPosition(1250,340);
    racketComputer.setRacketPosition(10, 340);

    InitWindow(screen_width, screen_heigh, "Ping-Pong Game");
    SetTargetFPS(60);
    
    while (WindowShouldClose()==false)
    {
        ball_position = ball.getCirclePosition();
        // 1 - Event handling:
        racketPlayer.updateRacketPositions();
        racketComputer.updateRacketPositions(ball_position);
        // 2 - Updating positions:
        ball.updatePosition();
        // 3 - Drawing objects:
        BeginDrawing();
            ClearBackground(BLACK);
            DrawLine(screen_width/2, 0, screen_width/2, screen_heigh, WHITE);
            ball.drawnCircle();
            racketPlayer.DrawRacket();
            racketComputer.DrawRacket();
            // DrawRectangleV(rectangle2_position, rectangle_dimensions, WHITE);
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}