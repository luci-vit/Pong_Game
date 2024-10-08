#include "../include/exit_button.hpp"

ExitButton::ExitButton(const char *imagePath, Vector2 imagePosition):Button(imagePath, imagePosition)
{
} 

void ExitButton::DrawExitButton()
{
    Image exit_image = LoadImageFromTexture(texture);
    ImageResize(&exit_image, 230, 150);
    
    DrawTextureV(LoadTextureFromImage(exit_image), position, WHITE);
}