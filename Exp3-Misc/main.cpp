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
    // 四面体
    auto& triangleMesh = Mesh::GenMesh();
    triangleMesh.indices = { 0, 3, 1, 2, 0, 3};
    triangleMesh.vertices = {
        {.0f,       .0f,        -1.0f},
        {-.866f,    .0f,        .5f},
        {.866f,     .0f,        .5f},
        {.0f,       1.4142f,    .0f },
    };
    triangleMesh.drawType = GL_TRIANGLE_STRIP;
    // 正方体
    auto& cubeMesh = Mesh::GenMesh();
    glEnable(GL_PRIMITIVE_RESTART);
    glPrimitiveRestartIndex(0xFFFF);
    cubeMesh
        .indices = { 0, 1, 5, 4, 7, 3, 2, 1, 0xFFFF, 6, 7, 4, 5, 1, 2, 3, 7};
    cubeMesh
        .vertices = std::vector<vmath::vec3>{
                {-.5f,  -.5f,   -.5f },
                {.5f,   -.5f,   -.5  },
                {.5f,   -.5f,   .5f  },
                {-.5f,  -.5f,   .5f  },
                {-.5f,  .5f,    -.5f },
                {.5f,   .5f,    -.5  },
                {.5f,   .5f,    .5f  },
                {-.5f,  .5f,    .5f  }
    };
    cubeMesh.drawType = GL_TRIANGLE_FAN;
    Mesh::Init();
    // GameObjects-------------------------------------------------------------------------

    // 位置
    auto& tran1 = GameObject::gameObjects.emplace_back().GetTransform();
    tran1.SetPosition({ -1, 0, 0 });
    tran1.SetRotation({ 0, 0, 0 });
    tran1.SetScale({0.5, 0.5, 0.5f});
    tran1.AddComponent(triangle);
    auto& tran2 = GameObject::gameObjects.emplace_back().GetTransform();
    tran2.SetPosition({ 1, 0, 0 });
    tran2.SetScale({ .5f, .5f, .5f });
    tran2.AddComponent(square);
    // MeshRenderers-----------------------------------------------------------------------
    // 由于 vector 的扩容, 上面的地址已经失效了
    // std::cerr<<"end-1 = "<< static_cast<GameObject*>(GameObject::gameObjects.end() - 1)<<std::endl;
    MeshRenderer::renderers.emplace_back(
        GameObject::gameObjects[GameObject::gameObjects.size() - 2],
        &triangleMesh,
        "Shaders/Standard.vert", "Shaders/ColorCircle.frag");
    MeshRenderer::renderers.emplace_back(
        GameObject::gameObjects[GameObject::gameObjects.size() - 1],
        &cubeMesh,
        "Shaders/Standard.vert", "Shaders/ChessBoard.frag");
    // Camera------------------------------------------------------------------------------
    auto& cameraObj = GameObject::gameObjects.emplace_back();
    // TODO: delete camera...?
    cameraObj.AddComponent(*new Camera(cameraObj));
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
    GlityEntry::Init();
    // glutKeyboardFunc(keyfunc); 输入回调只能有一个
    // glutDisplayFunc(display); 渲染回调显然也只能有一个

    glutMainLoop();
    return 0;
}
