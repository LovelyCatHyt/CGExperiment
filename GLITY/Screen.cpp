#include "pch.h"
#include "Screen.h"

vmath::vec2 Screen::pixelSize;
int Screen::screenSize[2]{};
void Screen::Init()
{
    glutReshapeFunc(WindowResize);
}

void Screen::WindowResize(int width, int height)
{
    pixelSize[0] = 1.0f / static_cast<float>(width);
    pixelSize[1] = 1.0f / static_cast<float>(height);
    screenSize[0] = width;
    screenSize[1] = height;
    glViewport(0, 0, width, height);
}

vmath::vec2 Screen::ScreenToNdc(int x, int y)
{
    return vmath::vec2
    {
        static_cast<float>(x - screenSize[0] / 2) * pixelSize[0] * 2,
        static_cast<float>(screenSize[1] / 2 - y) * pixelSize[1] * 2
    };
}


