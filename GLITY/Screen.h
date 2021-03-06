#pragma once
#include "pch.h"
#include "Glity-All.h"
#include "vmath.h"

class GlityEntry;

class Screen
{
    friend GlityEntry;
    static void Init();
    static void WindowResize(int width, int height);
public:
    static vmath::vec2 pixelSize;
    static int screenSize[2]; 
    static vmath::vec2 ScreenToNdc(int x, int y);
};

