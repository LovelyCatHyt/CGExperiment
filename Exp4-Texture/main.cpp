#include "stdafx.h"


#include "CameraDriver.h"
#include "../GLITY/Glity-All.h"
#include "CubeDriver.h"
#include "TriangleDriver.h"

CubeDriver square{ 2, 0.8f, .333333f };
TriangleDriver triangle{};
GameObject* squareObj;
GameObject* triangleObj;

void init() {

    // Meshes------------------------------------------------------------------------------
    // 异形体
    auto& impossibleTriangle = Mesh::LoadMesh("Models/ImpossibleCube.obj");
    // 正方形
    auto& quadMesh = Mesh::LoadMesh("Models/Quad.obj");
    
    Mesh::Init();

    // GameObjects-------------------------------------------------------------------------
    // 第一个物体
    // 注: 物体初始化阶段不能新建新的物体/组件, 否则原指针大概率失效
    // 除非预分配空间
    auto& obj1 = GameObject::gameObjects.emplace_back();
    auto& tran1 = obj1.GetTransform();
    tran1.SetPosition({ 0, 2, 0 });
    auto* texture = new Texture("Textures/Flag_CN_4096.png");
    tran1.SetScale({static_cast<float>(texture->width) / static_cast<float>(texture->height), 1, 1});
    MeshRenderer::renderers.emplace_back(
        obj1,
        &quadMesh,
        "Shaders/Standard.vert", "Shaders/Standard.frag",
        texture);
    // 第二个物体
    auto& obj2 = GameObject::gameObjects.emplace_back();
    auto& tran2 = obj2.GetTransform();
    tran2.SetPosition({ -1, 0, 0 });
    tran2.SetScale({ .5f, .5f, .5f });
    MeshRenderer::renderers.emplace_back(
        obj2,
        &impossibleTriangle,
        "Shaders/Standard.vert", "Shaders/ColorCircle.frag");    
    
    // Camera------------------------------------------------------------------------------
    auto& cameraObj = GameObject::gameObjects.emplace_back();
    // TODO: delete camera...?
    auto& camera = *new Camera(cameraObj);
    camera.size = 8;
    cameraObj.AddComponent(camera);
    auto& camTran = cameraObj.GetTransform();
    camTran.SetPosition(vmath::vec3{ 0, 0.5f, -1 });
    camTran.SetRotation(vmath::vec3{ 45, 0, 0 });
    cameraObj.AddComponent(*new CameraDriver(cameraObj));
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
    glutInitWindowSize(800, 600);
    // ??
    glutInitContextVersion(1, 3);
    // ??
    glutInitContextProfile(GLUT_CORE_PROFILE);
    // 创建窗口, 但是没人知道这个返回的 int 是什么东西
    glutCreateWindow("Exp4-Texture");
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
