#include "pch.h"
#include "Glity-All.h"

bool Input::keyStates[256]{};
bool Input::prevKeyStates[256]{};
std::vector<unsigned char> Input::activeKeys{};

bool Input::mouseButtons[3]{};
bool Input::prevMouseButtons[3]{};
std::vector<unsigned char> Input::activeMouseButtons{};
int Input::mousePosition[2]{};

void Input::Init()
{
    // 键盘
    glutKeyboardFunc(OnKeyboard);
    glutKeyboardUpFunc(OnKeyboardUp);
    // 鼠标
    glutMotionFunc(OnMouseMove);
    glutPassiveMotionFunc(OnMouseMove);
    glutMouseFunc(OnMouseButton);
}

void Input::OnKeyboard(unsigned char key, int x, int y)
{
    keyStates[key] = true;
    activeKeys.emplace_back(key);
}

void Input::OnKeyboardUp(unsigned char key, int x, int y)
{
    keyStates[key] = false;
    activeKeys.emplace_back(key);
}

void Input::OnMouseButton(int button, int state, int x, int y)
{
    mouseButtons[button] = state == GLUT_DOWN;
    activeMouseButtons.emplace_back(static_cast<unsigned char>(button));
    OnMouseMove(x, y);
}

void Input::OnMouseMove(int x, int y)
{
    mousePosition[0] = x;
    mousePosition[1] = y;
}

void Input::Update()
{
    for(const auto& activeKey:activeKeys)
        prevKeyStates[activeKey] = keyStates[activeKey];
    activeKeys.clear();
    for(const auto& activeMouseButton: activeMouseButtons)
        prevMouseButtons[activeMouseButton] = mouseButtons[activeMouseButton];
    activeMouseButtons.clear();
}

bool Input::GetKeyDown(const unsigned char& key)
{
    return keyStates[key] && !prevKeyStates[key];
}

bool Input::GetKey(const unsigned char& key)
{
    return keyStates[key];
}

bool Input::GetKeyUp(const unsigned char& key)
{
    return !keyStates[key] && prevKeyStates[key];
}

bool Input::GetMouseButtonDown(const int& button)
{
    return mouseButtons[button] && !prevMouseButtons[button];
}

bool Input::GetMouseButton(const int& button)
{
    return mouseButtons[button];
}

bool Input::GetMouseButtonUp(const int& button)
{
    return !mouseButtons[button] && prevMouseButtons[button];
}
