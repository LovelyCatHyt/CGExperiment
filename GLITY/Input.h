#pragma once
#include "pch.h"
#include "Glity-All.h"
#include <vector>

class GlityEntry;

class Input
{
    friend GlityEntry;
    static void Init();
    static void OnKeyboard(unsigned char key, int x, int y);
    static void OnKeyboardUp(unsigned char key, int x, int y);
    static void OnMouseButton(int button, int state, int x, int y);
    static void OnMouseMove(int x, int y);
    static void Update();

    static bool keyStates[256];
    static bool prevKeyStates[256];
    static std::vector<unsigned char> activeKeys;

    static bool mouseButtons[3];
    static bool prevMouseButtons[3];
    static std::vector<unsigned char> activeMouseButtons;
public:
    static int mousePosition[2];

    // 键盘
    static bool GetKeyDown(const unsigned char& key);
    static bool GetKey(const unsigned char& key);
    static bool GetKeyUp(const unsigned char& key);
    // 鼠标
    static bool GetMouseButtonDown(const int& button);
    static bool GetMouseButton(const int& button);
    static bool GetMouseButtonUp(const int& button);
    
};

