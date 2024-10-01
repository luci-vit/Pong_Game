//Implementa os métodos declarados na criação da classe.
#include "../include/ball.hpp"

void Ball::setCirclePosition(float x, float y) //Determina a posição inicial da bola.
{
    this->circle_position.x = x;
    this->circle_position.y = y;
}

Vector2 Ball::getCirclePosition()
{
    return this->circle_position;
}

void Ball::setCircleRadius(float x)
{
    this->circle_radius = x;
}

int Ball::getCircleRadius()
{
    return this->circle_radius;
}

void Ball::drawnCircle()
{
    DrawCircleV(getCirclePosition(), getCircleRadius(), this->green_ball);
}

void Ball::setSpeedCollisionX(){
    this->speed_x *=-1;
}

void Ball::setSpeedCollisionY(){
    this->speed_y *=-1; 
}

int Ball::updatePosition() //Método responsável por atualizar a posição da bola e checar suas colisões.
{

    circle_position.x += speed_x;
    circle_position.y += speed_y;

    if(circle_position.y+circle_radius>=GetScreenHeight()||circle_position.y-circle_radius<=0){ //Verifica se ocorreu alguma colisão com as bordas da tela no eixo y, fazendo com que ela seja "rebatida" caso isso ocorra.
       speed_y*=-1;
    }
    if (circle_position.x+circle_radius>=GetScreenWidth()||circle_position.x-circle_radius<=0){ //Verifica se ocorreu alguma colisão com as bordas da tela no eixo x, fazendo com que ela seja "rebatida" caso isso ocorra.
       return (circle_position.x - circle_radius <=0) ?  1 : 2;
    }

    return 0;
}
