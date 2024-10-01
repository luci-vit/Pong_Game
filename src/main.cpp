#include <raylib.h>
#include <iostream>
#include <unistd.h>
#include "../include/ball.hpp"
#include "../include/racket_player.hpp"
#include "../include/racket_computer.hpp"

using namespace std;
Ball ball;
RacketPlayer racketPlayer;
RacketComputer racketComputer;
void reinit_game();

int main(){
    //Construindo as dimensões da tela. 
    const int screen_width = 1280;
    const int screen_heigh = 800;
    int score_player1=0, score_player2=0;
    Color green = {20, 160, 133, 255};
    
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

        // Updating positions:
        racketPlayer.updateRacketPositions();
        racketComputer.updateRacketPositions(ball_position);
        int check_score = ball.updatePosition();
       
        // Check collisions:
        if(CheckCollisionCircleRec(ball.getCirclePosition(), ball.getCircleRadius(), 
        Rectangle{racketPlayer.getRacketPosition().x, racketPlayer.getRacketPosition().y, racketPlayer.getRacketDimensions().x, racketPlayer.getRacketDimensions().y})){
            ball.setSpeedCollisionX();
        }
        if(CheckCollisionCircleRec(ball.getCirclePosition(), ball.getCircleRadius(), 
        Rectangle{racketComputer.getRacketPosition().x, racketComputer.getRacketPosition().y, racketComputer.getRacketDimensions().x, racketComputer.getRacketDimensions().y})){
            ball.setSpeedCollisionX();
        }

        //Check for scored:
        if(check_score==1){
            std::cout << ball.updatePosition() << std::endl;
            score_player1++;
            reinit_game();
        }
        if(check_score==2){
            std::cout << ball.updatePosition() << std::endl;
            score_player2++;
            reinit_game();
        }

        // Drawing objects:
        BeginDrawing();
            ClearBackground(green);
            DrawLine(screen_width/2, 0, screen_width/2, screen_heigh, WHITE);
            ball.drawnCircle();
            racketPlayer.DrawRacket();
            racketComputer.DrawRacket();
            DrawText(TextFormat("%d", score_player1), 740, 30, 80, WHITE);
            DrawText(TextFormat("%d", score_player2), 500, 30, 80, WHITE);
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}

void reinit_game()
{
    ball.setCirclePosition(640, 400);
    racketPlayer.setRacketPosition(1250,340);
    racketComputer.setRacketPosition(10, 340);
    sleep(3);
}
