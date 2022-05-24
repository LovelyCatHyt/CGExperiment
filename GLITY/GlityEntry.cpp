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
    // 清除颜色缓冲, 深度缓冲
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // 清屏
    glClearColor(0, 0, 0, 1);

    for (auto& gameObject : GameObject::gameObjects)
    {
        gameObject.Update();
    }
    for (auto& gameObject : GameObject::gameObjects)
    {
        gameObject.LateUpdate();
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
