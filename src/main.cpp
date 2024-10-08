#include <raylib.h>
#include <iostream>
#include <thread> //Responsável pela função que pausa a thread.
#include <chrono> //Responsável pela função que passa a quantidade de segundos que a thread deve esperar.
#include "../include/ball.hpp"
#include "../include/racket_player.hpp"
#include "../include/racket_player2.hpp"
#include "../include/racket_computer.hpp"
#include "../include/button.hpp"
#include "../include/exit_button.hpp"

using namespace std;
Ball ball;
RacketPlayer racketPlayer;
RacketComputer racketComputer;
RacketPlayer2 racketPlayer2;

Color green = {20, 160, 133, 255};

void reinitGame();
int initialScreen(Button player1, Button player2, ExitButton exit, Texture2D texture);
void drawingObjects(int screen_width, int screen_heigh, int score_player1, int score_player2, int game_mod);
void checkScore(int check_score, int * score_player1, int * score_player2);

int main(){
    //Construindo as dimensões da tela. 
    const int screen_width = 1280;
    const int screen_heigh = 800;
    int score_player1=0, score_player2=0;
    int game_mod=-1;
    
    //Construindo a dimensão do círculo e sua posição.
    ball.setCircleRadius(20);
    ball.setCirclePosition(640, 400);
    Vector2 ball_position;

    //Construindo as dimensões das "raquetes" e suas respectivas posições.
    racketPlayer.setRacketDimensions(20,120);
    racketPlayer.setRacketPosition(1250,340);

    racketPlayer2.setRacketDimensions(20, 120);
    racketPlayer2.setRacketPosition(10, 340);

    racketComputer.setRacketDimensions(20, 120);
    racketComputer.setRacketPosition(10, 340);

    InitWindow(screen_width, screen_heigh, "Ping-Pong Game");
    SetTargetFPS(60);

    //Construindo as imagem dos butões. 
    Button player1{"graphics/1_jogador.png", {450, 500}};
    Button player2{"graphics/2_jogadores.png", {660, 500}};
    ExitButton exit{"graphics/exit_button.png", {540, 600}};

    //Construindo a imagem da tela inicial.
    Image init_screen = LoadImage("graphics/init_screen.png"); //Converte o arquivo para o tipo imagem para que seja possível realizar a redimensão.
    ImageResize(&init_screen, 1280, 800); //Redimensiona a imagem;
    Texture2D texture_init_screen = LoadTextureFromImage(init_screen); //Converte a imagem para o tipo texture, já que esse tipo otimiza o processamento da imagem
    UnloadImage(init_screen); //Libera o espaço de memória ocupado pela imagem.

    while (WindowShouldClose()==false && game_mod!=0)
    {
        ball_position = ball.getCirclePosition();

        if(game_mod==-1){
            game_mod=initialScreen(player1, player2, exit, texture_init_screen);
            if (game_mod!=0)
            {
                for(int i = 3; i>0; i--){
                    DrawText(TextFormat("A partida começa em: %d", i), 200, 300, 80, WHITE);
                    drawingObjects(screen_width, screen_heigh, score_player1, score_player2, game_mod);
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }          
            }
        }

        // Updating positions:
        racketPlayer.updateRacketPositions();
        //Ambos os ifs checam qual foi modo selecionado para que seja atualizada apenas a posição da raquete correspondente a ele. 
        if(game_mod==1){racketComputer.updateRacketCompPositions(ball_position);}
        if(game_mod==2){racketPlayer2.updateRacketPositions_pl2();}
        int check_score = ball.updatePosition();
       
        // Check collisions:
        if(CheckCollisionCircleRec(ball.getCirclePosition(), ball.getCircleRadius(), 
        Rectangle{racketPlayer.getRacketPosition().x, racketPlayer.getRacketPosition().y, racketPlayer.getRacketDimensions().x, racketPlayer.getRacketDimensions().y})){
            ball.setSpeedCollisionX();
        }

        if (game_mod==1) //Checa se o modo de jogo selecionado foi o de 1 jogador para que seja verifica a colisão com a raquete controlada pelo computador
        {
            if(CheckCollisionCircleRec(ball.getCirclePosition(), ball.getCircleRadius(), 
            Rectangle{racketComputer.getRacketPosition().x, racketComputer.getRacketPosition().y, racketComputer.getRacketDimensions().x, racketComputer.getRacketDimensions().y})){
                ball.setSpeedCollisionX();
            }        
        }

        if (game_mod==2) //Checa se o modo de jogo selecionado foi o de 2 jogadores para que seja verifica a colisão com a raquete controlada pelo outro jogador
        {
            if(CheckCollisionCircleRec(ball.getCirclePosition(), ball.getCircleRadius(), 
            Rectangle{racketPlayer2.getRacketPosition().x, racketPlayer2.getRacketPosition().y, racketPlayer2.getRacketDimensions().x, racketPlayer2.getRacketDimensions().y})){
                ball.setSpeedCollisionX();
            }        
        }

        //Check for scored:
        checkScore(check_score, &score_player1, &score_player2);

        // Drawing objects:
        drawingObjects(screen_width, screen_heigh, score_player1, score_player2, game_mod);
    }
    
    CloseWindow();
    return 0;
}

//Função responsável por reinicializar o jogo após a realização de um ponto.
void reinitGame()
{
    ball.setCirclePosition(640, 400);
    racketPlayer.setRacketPosition(1250,340);
    racketComputer.setRacketPosition(10, 340);
    std::this_thread::sleep_for(std::chrono::seconds(3)); //Pausa a thread durante um intervalo de 3 segundos.
}

//Função responsável por construir e ficar reconstruindo a tela do jogo para dar a sensação de movimento.
void drawingObjects(int screen_width, int screen_heigh, int score_player1, int score_player2, int game_mod){
    BeginDrawing();
        ClearBackground(green);
        DrawLine(screen_width/2, 0, screen_width/2, screen_heigh, WHITE);
        ball.drawnCircle();
        racketPlayer.DrawRacket();
        if(game_mod==1){racketComputer.DrawRacket();}
        if(game_mod==2){racketPlayer2.DrawRacket();}
        DrawText(TextFormat("%d", score_player1), 740, 30, 80, WHITE);
        DrawText(TextFormat("%d", score_player2), 500, 30, 80, WHITE);
    EndDrawing();
}

//Função responsável por construir a tela inicial e verificar qual foi o modo de jogo selecionado.
int initialScreen(Button player1, Button player2, ExitButton exit, Texture2D texture){
    //Roda enquanto for true porque não existe uma necessidade de saída do while por condição, já que o return por si só já realiza isso. 
    while(true)
    {
        Vector2 mousePosition = GetMousePosition();
        bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        //Check for events:
        if(player1.isPressed(mousePosition, mousePressed)){ //Verifica se o botão para o modo 1 jogador foi pressionado.
            return 1;
        }

        if(player2.isPressed(mousePosition, mousePressed)){ //Verifica se o botão para o modo 2 jogadores foi pressionado.
            return 2;
        }

        if(exit.isPressed(mousePosition, mousePressed)){ //Verifica se o botão para sair do jogo foi pressionado.
            return 0;
        }

        //Drawing objects:
        BeginDrawing();
        ClearBackground(green);
        DrawTexture(texture, 0, 0, WHITE); //Desenha o background com base na textura.
        player1.Draw();
        player2.Draw();
        exit.DrawExitButton();
        EndDrawing();
    }
}

void checkScore(int check_score, int * score_player1, int * score_player2){
        if(check_score==1){
            std::cout << ball.updatePosition() << std::endl;
            *score_player1+=1;
            reinitGame();
        }

        if(check_score==2){
            std::cout << ball.updatePosition() << std::endl;
            *score_player2+=1;
            reinitGame();
        }
}