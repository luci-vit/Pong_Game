#ifndef EXIT_BUTTON_HPP
#define EXIT_BUTTON_HPP
#include "button.hpp"

class ExitButton : public Button{
    private:

    public:
    ExitButton(const char* imagePath, Vector2 imagePosition);
    void DrawExitButton();
};

#endif