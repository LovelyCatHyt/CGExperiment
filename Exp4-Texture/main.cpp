#include "stdafx.h"

#include "CameraDriver.h"
#include "../GLITY/Glity-All.h"
#include "TextureParaSetter.h"

GameObject* squareObj;
GameObject* triangleObj;

void init() {

    /*if (glutExtensionSupported("GL_EXT_texture_filter_anisotropic"))
        std::cout<<"anisotropy is supported!"<<std::endl;*/

    // Meshes------------------------------------------------------------------------------
    Mesh::Meshes.reserve(2);

    // GameObjects-------------------------------------------------------------------------
    // 第一个物体
    // 注: 物体初始化阶段不能新建新的物体/组件, 否则原指针大概率失效
    // 除非预分配空间
    auto& obj1 = GameObject::gameObjects.emplace_back();
    auto& tran1 = obj1.GetTransform();
    tran1.SetPosition({ -1.95f, 0, 0 });
    tran1.SetScale({.5f, .5f, .5f});
    tran1.SetRotation(Quaternion::Euler(0, -90, 0));
    auto* texture = new Texture("../Resources/Textures/Flag_CN_4096.png");
    tran1.SetScale({static_cast<float>(texture->width) / static_cast<float>(texture->height), 1, 1});

    // 正方形
    auto& quadMesh = Mesh::LoadMesh("../Resources/Models/Quad.obj");
    
    MeshRenderer::renderers.emplace_back(
        obj1,
        &quadMesh,
        "Shaders/Standard.vert", "Shaders/Standard.frag",
        texture);

    // 隧道
    // 墙面
    auto& wall = Mesh::LoadMesh("../Resources/Models/Wall_8x1.obj");
    auto* wallTexture = new Texture("../Resources/Textures/squareMoonMap.jpg", GL_REPEAT, true, GL_NEAREST);
    // 左
    auto& wall1 = GameObject::gameObjects.emplace_back();
    wall1.AddComponent(*new TextureParaSetter(wall1));
    auto& wall1Tran = wall1.GetTransform();
    wall1Tran.SetPosition({ -2, 0, 0 });
    wall1Tran.SetScale({ 16, 2, 1 });
    wall1Tran.SetRotation(Quaternion::Euler(0, -90, 0));
    MeshRenderer::renderers.emplace_back(
        wall1,
        &wall,
        "Shaders/Standard.vert", "Shaders/Standard.frag",
        wallTexture);
    // 右
    auto& wall2 = GameObject::gameObjects.emplace_back();
    
    auto& wall2Tran = wall2.GetTransform();
    wall2Tran.SetPosition({ 2, 0, 0 });
    wall2Tran.SetScale({ 16, 2, 1 });
    wall2Tran.SetRotation(Quaternion::Euler(0, 90, 0));
    MeshRenderer::renderers.emplace_back(
        wall2,
        &wall,
        "Shaders/Standard.vert", "Shaders/Standard.frag",
        wallTexture);
    // 上
    auto& wall3 = GameObject::gameObjects.emplace_back();
    auto& wall3Tran = wall3.GetTransform();
    wall3Tran.SetPosition({ 0, 2, 0 });
    wall3Tran.SetScale({ 16, 2, 1 });
    wall3Tran.SetRotation(Quaternion::Euler(0, 90, 90));
    MeshRenderer::renderers.emplace_back(
        wall3,
        &wall,
        "Shaders/Standard.vert", "Shaders/Standard.frag",
        wallTexture);
    // 下
    auto& wall4 = GameObject::gameObjects.emplace_back();
    auto& wall4Tran = wall4.GetTransform();
    wall4Tran.SetPosition({ 0, -2, 0 });
    wall4Tran.SetScale({ 16, 2, 1 });
    wall4Tran.SetRotation(Quaternion::Euler(0, 90, -90));
    MeshRenderer::renderers.emplace_back(
        wall4,
        &wall,
        "Shaders/Standard.vert", "Shaders/Standard.frag",
        wallTexture);

    // 隧道终点的钻石矿
    auto& diamondBlock = GameObject::gameObjects.emplace_back();
    auto& diamondTran = diamondBlock.GetTransform();
    diamondTran.SetPosition({0, 0, 16});
    diamondTran.SetScale({2, 2, 2});
    MeshRenderer::renderers.emplace_back(
        diamondBlock,
        &quadMesh,
        "Shaders/Standard.vert", "Shaders/Standard.frag",
        new Texture("../Resources/Textures/diamond_ore.png", GL_REPEAT, true, GL_NEAREST));

    Mesh::Init();
    // Camera------------------------------------------------------------------------------
    auto& cameraObj = GameObject::gameObjects.emplace_back();
    // TODO: delete camera...?
    auto& camera = *new Camera(cameraObj);
    camera.size = 8;
    cameraObj.AddComponent(camera);
    auto& camTran = cameraObj.GetTransform();
    camTran.SetPosition(vmath::vec3{ 0, 0, -3 });
    camTran.SetRotation(vmath::vec3{ 0, 0, 0 });
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
