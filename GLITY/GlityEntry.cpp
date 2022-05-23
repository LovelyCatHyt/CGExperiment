#include "pch.h"
#include "Glity-All.h"

void GlityEntry::Init()
{
    Input::Init();
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

    if (Input::GetMouseButtonDown(GLUT_LEFT_BUTTON))
    {
        std::cout << "mouse down at " << Input::mousePosition[0] << ", " << Input::mousePosition[1] << std::endl;
    }
    glFlush();
    glutPostRedisplay();
    Input::Update();
    Time::UpdateTime();
}
