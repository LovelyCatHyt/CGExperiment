#include "pch.h"
#include "Screen.h"

vmath::vec2 Screen::pixelSize;

void Screen::Init()
{
    glutReshapeFunc(WindowResize);
}

void Screen::WindowResize(int width, int height)
{
    pixelSize[0] = 1.0f / static_cast<float>(width);
    pixelSize[1] = 1.0f / static_cast<float>(height);
    glViewport(0, 0, width, height);
}


