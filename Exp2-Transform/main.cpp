#include "stdafx.h"

#include "../GLITY/Glity-All.h"
#include "SquareDriver.h"

SquareDriver square{ 2, 0.8f, .333333f };

void init() {
    GlityEntry::Init();
    // Meshes------------------------------------------------------------------------------
    // 三角形
    auto& triangle = Mesh::GenMesh();
    triangle.indices = { 2, 1, 0 };
    triangle.vertices = {
        {-.25f, -.25f, .0f},
        {.25f, -.25f, .0f},
        {.0f, .25f, .0f} };
    // 正方形
    auto& square = Mesh::GenMesh();
    square.indices = { 3, 2, 1, 2, 1, 0 };
    square.vertices = std::vector<vmath::vec3>{
        {-1, -1, .0f},
        {1, -1, .0f},
        {-1, 1, .0f},
        {1, 1, .0f}
    };
    Mesh::Init();
    // GameObjects-------------------------------------------------------------------------
    GameObject::gameObjects = { GameObject{}, GameObject{} };
    // 位置
    auto& tran1 = GameObject::gameObjects[0].GetTransform();
    tran1.SetPosition({ 0, -0.5, 0 });
    tran1.SetRotation({ 0, 0, 90 });
    auto& tran2 = GameObject::gameObjects[1].GetTransform();
    tran2.SetPosition({ 0, 0.5, 0 });
    tran2.SetScale({ .5, .5, 1 });
    // MeshRenderers-----------------------------------------------------------------------
    MeshRenderer::renderers.emplace_back(&triangle, "Shaders/ColorCircle");
    MeshRenderer::renderers.emplace_back(&square, "Shaders/ChessBoard");
    MeshRenderer::renderers[0].BindGameObject(GameObject::gameObjects[0]);
    MeshRenderer::renderers[1].BindGameObject(GameObject::gameObjects[1]);
}

void bindEvents()
{
    // GameObject::gameObjects[1].AddUpdateListener([&](GameObject& o) { square.Update(o); });
    GameObject::gameObjects[1].AddComponent(square);
    // std::cout<<GameObject::gameObjects[1].GetComponent<SquareDriver>().Name();
    square.Awake(GameObject::gameObjects[1]);
}

int main(int argc, char* argv[])
{
    // 初始化 glut	
    glutInit(&argc, argv);
    // 显示模式
    glutInitDisplayMode(GLUT_RGBA);
    // 窗口大小
    glutInitWindowSize(512, 512);
    // ??
    glutInitContextVersion(1, 3);
    // ??
    glutInitContextProfile(GLUT_CORE_PROFILE);
    // 创建窗口, 但是没人知道这个返回的 int 是什么东西
    glutCreateWindow("ColorCircle Windows");
    // 初始化 glew
    if (glewInit())
    {
        std::cerr << "Unable to Initialize GLEW" << std::endl;
    }
    // 初始化
    init();
    bindEvents();
    // glutKeyboardFunc(keyfunc); 输入回调只能有一个
    // glutDisplayFunc(display); 渲染回调显然也只能有一个

    glutMainLoop();
    return 0;
}
