//Implementa os métodos declarados na criação da classe.
#include "../include/ball.hpp"

void Ball::setCirclePosition(int x, int y) //Determina a posição inicial da bola.
{
    this->circle_position.x = x;
    this->circle_position.y = y;
}

Vector2 Ball::getCirclePosition()
{
    return this->circle_position;
}

void Ball::setCircleRadius(int x)
{
    this->circle_radius = x;
}

int Ball::getCircleRadius()
{
    return this->circle_radius;
}

void Ball::drawnCircle()
{
    DrawCircleV(getCirclePosition(), getCircleRadius(), WHITE);
}

void Ball::updatePosition() //Método responsável por atualizar a posição da bola e checar suas colisões.
{
    circle_position.x += speed_x;
    circle_position.y += speed_y;

    if(circle_position.y+circle_radius>=GetScreenHeight()||circle_position.y-circle_radius<=0){ //Verifica se ocorreu alguma colisão com as bordas da tela no eixo y, fazendo com que ela seja "rebatida" caso isso ocorra.
       speed_y*=-1;
    }
    if (circle_position.x+circle_radius>=GetScreenWidth()||circle_position.x-circle_radius<=0){ //Verifica se ocorreu alguma colisão com as bordas da tela no eixo x, fazendo com que ela seja "rebatida" caso isso ocorra.
       speed_x*=-1;
    }

    // if(circle_position.x+circle_radius==racketPlayer.getRacketPosition().x && circle_position.y>=racketPlayer.getRacketPosition().y || circle_position.y<=racketPlayer.getRacketPosition().y+120){
    //     speed_y*=-1;
    //     speed_x*=-1;
    // }
    
}
