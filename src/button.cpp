#include "../include/button.hpp"

Button::Button(const char *imagePath, Vector2 imagePosition){
    this->texture = LoadTexture(imagePath);
    this->position = imagePosition;
}

Button::~Button(){
    UnloadTexture(texture);
}

void Button::Draw(int width, int height){ 
    Image button_image = LoadImageFromTexture(texture);
    ImageResize(&button_image, width, height);
    texture = LoadTextureFromImage(button_image);
    UnloadImage(button_image);

    DrawTextureV(texture, position, WHITE);
}

bool Button::isPressed(Vector2 mousePos, bool mousePress){
    Rectangle rec = {position.x, position.y, texture.width, texture.height};
    

    if(CheckCollisionPointRec(mousePos, rec) && mousePress){
        return true;
    }
    return false;
}