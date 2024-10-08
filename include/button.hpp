#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <raylib.h>

class Button{
    protected:
        Texture2D texture;
        Vector2 position;
    public:
        Button(const char* imagePath, Vector2 imagePostion);
        ~Button();
        bool isPressed(Vector2 mousePos, bool mousePress);
        void Draw();
};
#endif