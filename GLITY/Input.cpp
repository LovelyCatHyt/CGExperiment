#include "pch.h"
#include "Glity-All.h"

bool Input::keyStates[256]{};
bool Input::prevKeyStates[256]{};
unsigned char Input::activeKey = 0;

bool Input::mouseButtons[3]{};
bool Input::prevMouseButtons[3]{};
unsigned char Input::activeMouseButton = 0;
int Input::mousePosition[2]{};

void Input::Init()
{
    // МќХЬ
    glutKeyboardFunc(OnKeyboard);
    glutKeyboardUpFunc(OnKeyboardUp);
    // ЪѓБъ
    glutMotionFunc(OnMouseMove);
    glutPassiveMotionFunc(OnMouseMove);
    glutMouseFunc(OnMouseButton);
}

void Input::OnKeyboard(unsigned char key, int x, int y)
{
    keyStates[key] = true;
    activeKey = key;
}

void Input::OnKeyboardUp(unsigned char key, int x, int y)
{
    keyStates[key] = false;
    activeKey = key;
}

void Input::OnMouseButton(int button, int state, int x, int y)
{
    mouseButtons[button] = state == GLUT_DOWN;
    activeMouseButton = static_cast<unsigned char>(button);
    OnMouseMove(x, y);
}

void Input::OnMouseMove(int x, int y)
{
    mousePosition[0] = x;
    mousePosition[1] = y;
}

void Input::Update()
{
    prevKeyStates[activeKey] = keyStates[activeKey];
    prevMouseButtons[activeMouseButton] = mouseButtons[activeMouseButton];
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
