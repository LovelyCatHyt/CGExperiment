#include "stdafx.h"

#include "CameraDriver.h"
#include "../GLITY/Glity-All.h"
#include "CubeRotate.h"


void init() {

    /*if (glutExtensionSupported("GL_EXT_texture_filter_anisotropic"))
        std::cout<<"anisotropy is supported!"<<std::endl;*/

        // Meshes------------------------------------------------------------------------------
    Mesh::Meshes.reserve(2);

    // GameObjects-------------------------------------------------------------------------
    // 第一个物体
    // 注: 物体初始化阶段不能新建新的物体/组件, 否则原指针大概率失效
    // 除非预分配空间
    // 正方形
    auto& quadMesh = Mesh::LoadMesh("../Resources/Models/Quad.obj");
    auto& obj1 = GameObject::gameObjects.emplace_back();
    auto& tran1 = obj1.GetTransform();
    tran1.SetPosition({ 0, -1, 0 });
    tran1.SetScale({ 8, 8, 1 });
    tran1.SetRotation(Quaternion::Euler(90, 0, 0));
    auto* texture = new Texture("../Resources/Textures/squareMoonMap.jpg");
    auto* normalMap = new Texture("../Resources/Textures/squareMoonNormal.jpg");
    MeshRenderer::renderers.emplace_back(
        obj1,
        &quadMesh,
        "../Resources/Shaders/Standard.vert", "Shaders/Phong_Ground.frag",
        texture, normalMap);

    // 旋转的立方体
    auto& cubeMesh = Mesh::LoadMesh("../Resources/Models/cube.obj");
    auto& cube = GameObject::gameObjects.emplace_back();
    cube.AddComponent(*new CubeRotate(cube));
    auto& cubeTran = cube.GetTransform();
    cubeTran.SetPosition({0, 2, 0});
    MeshRenderer::renderers.emplace_back(
        cube,
        &cubeMesh,
        // "../Resources/Shaders/Standard.vert", "Shaders/Phong_NoNormal.frag",
        "Shaders/Gouraud",
        new Texture("../Resources/Textures/metal_plate_diff_2k.jpg"), new Texture("../Resources/Textures/metal_plate_rough_2k.jpg")
    );

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
