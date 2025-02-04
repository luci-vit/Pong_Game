#ifndef GAMING_HPP
#define GAMING_HPP

#include <raylib.h>
#include <iostream>
#include <thread> //Responsável pela função que pausa a thread.
#include <chrono> //Responsável pela função que passa a quantidade de segundos que a thread deve esperar.
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <map>
#include <vector>
#include "../include/ball.hpp"
#include "../include/racket_player.hpp"
#include "../include/racket_player2.hpp"
#include "../include/racket_computer.hpp"
#include "../include/button.hpp"

using namespace std;

class Gaming{

    private:
        Ball ball;
        RacketPlayer racketPlayer;
        RacketComputer racketComputer;
        RacketPlayer2 racketPlayer2;
        Color green = {20, 160, 133, 255};
        const int screen_width = 1280;
        const int screen_heigh = 800;

        typedef struct { //Dados de cada jogador do torneio.
            std::string name="";
            Color racketColor = WHITE;
            bool victory = false;
            int pontPartida = 0;
        }Dados;
        
        bool pontoMarcado = false;

    

    public:
        void reinitGame();
        void drawingObjects(int screen_width, int screen_heigh, int score_player1, int score_player2, int game_mod);
        int initialScreen(Button player1, Button player2, Button exit, Button torneio,Texture2D texture);
        void checkScore(int check_score, int *score_player1, int *score_player2);
        void gameLogic();
        void tournamentModeScreen();
        void setPlayerInformationScreen(Dados *dadosJogador, int numJogadores);
        void gamingLogicTournament(Dados *dadosJogador, int numJogadores);
        void vencedorMensagem (Dados *dadosJogador, int idJogador);
        void escreveNaTela (string Texto, int posicaoX, int posicaoY, int fontSize);
        Texture2D geraTextura(string imagem);
        void avancarFaseScreen(Dados *dadosJogador, int numJogadores);
};  

#endif