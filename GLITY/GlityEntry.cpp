#include "pch.h"
#include "Glity-All.h"

void GlityEntry::Init()
{
    Input::Init();
    Screen::Init();
    for (auto& gameObject : GameObject::gameObjects)
    {
        gameObject.Awake();
    }
    glutDisplayFunc(DisplayLoop);
}

void GlityEntry::LateUpdate()
{
    
}

void GlityEntry::DisplayLoop()
{
    // 清屏 (屏幕缓冲区? 绘制缓冲区?)
    glClearColor(.5, .5, .5, 1);
    // Clear again
    glClear(GL_COLOR_BUFFER_BIT);

    for (auto& gameObject : GameObject::gameObjects)
    {
        gameObject.Update();
    }
    for (const auto& renderer : MeshRenderer::renderers)
    {
        renderer.Display();
    }
    
    glFlush();
    glutPostRedisplay();
    Input::Update();
    Time::UpdateTime();
}
