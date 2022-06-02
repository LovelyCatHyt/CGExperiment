#include "stdafx.h"

#include "../GLITY/Glity-All.h"
#include "SquareDriver.h"
#include "TriangleDriver.h"

SquareDriver square{ 2, 0.8f, .333333f };
TriangleDriver triangle{};
// GameObject* squareObj;
// GameObject* triangleObj;

void init() {
    // 该实验没有摄像机, 纯2D, 因此关掉深度测试和背面裁剪
    MeshRenderer::depthTest = false;
    MeshRenderer::cullFace = false;
    // Meshes------------------------------------------------------------------------------
    // 三角形
    auto& triangleMesh = Mesh::GenMesh();
    triangleMesh.indices = { 0, 1, 2 };
    triangleMesh.vertices = {
        {-.25f, -.25f, .0f},
        {.25f, -.25f, .0f},
        {.0f, .25f, .0f} };
    // 正方形
    auto& squareMesh = Mesh::GenMesh();
    squareMesh
        .indices = { 3, 2, 1, 2, 1, 0 };
    squareMesh
        .vertices = std::vector<vmath::vec3>{
                {-1, -1, .0f},
                {1, -1, .0f},
                {-1, 1, .0f},
                {1, 1, .0f}
    };
    Mesh::Init();
    // GameObjects-------------------------------------------------------------------------

    // 位置
    auto& tran1 = GameObject::gameObjects.emplace_back().GetTransform();
    tran1.SetPosition({ 0, 0.5, 0 });
    tran1.SetRotation(Quaternion::Euler( 0, 0, 90));
    tran1.AddComponent(triangle);
    auto& tran2 = GameObject::gameObjects.emplace_back().GetTransform();
    tran2.SetPosition({ 0, -0.5, 0 });
    tran2.SetScale({ .5, .5, 1 });
    tran2.AddComponent(square);
    // MeshRenderers-----------------------------------------------------------------------
    // 由于 vector 的扩容, 上面的地址已经失效了
    // std::cerr<<"end-1 = "<< static_cast<GameObject*>(GameObject::gameObjects.end() - 1)<<std::endl;
    MeshRenderer::renderers.emplace_back(GameObject::gameObjects[GameObject::gameObjects.size() - 2], &triangleMesh, "Shaders/ColorCircle");
    MeshRenderer::renderers.emplace_back(GameObject::gameObjects[GameObject::gameObjects.size() - 1], &squareMesh, "Shaders/ChessBoard");
    // Camera------------------------------------------------------------------------------
    //auto& cameraObj = GameObject::gameObjects.emplace_back();
    //// TODO: delete camera...?
    //cameraObj.AddComponent(*new Camera(cameraObj));
    //auto& camTran = cameraObj.GetTransform();
    //camTran.SetPosition(vmath::vec3{ 0, 0, -2 });
    //camTran.SetRotation(vmath::vec3{0, 180, 0});
    //cameraObj.AddComponent(*new CameraDriver(cameraObj));
    // MeshRenderer::renderers[0].BindGameObject(*triangleObj);
    // MeshRenderer::renderers[1].BindGameObject(*squareObj);
}

void bindEvents()
{
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
    glutCreateWindow("Exp2-Transform");
    // 初始化 glew
    if (glewInit())
    {
        std::cerr << "Unable to Initialize GLEW" << std::endl;
    }
    // 初始化
    init();
    bindEvents();
    GlityEntry::Init();
    // glutKeyboardFunc(keyfunc); 输入回调只能有一个
    // glutDisplayFunc(display); 渲染回调显然也只能有一个

    glutMainLoop();
    return 0;
}
