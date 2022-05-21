#include "stdafx.h"

#include "Time.h"
#include "../GLITY/Glity-All.h"
#include "SquareDriver.h"
std::vector<MeshRenderer> renderers;
std::vector<GameObject> gameObjects;

SquareDriver square{ 2, 0.8, .333333f };

void init() {
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
	gameObjects = { GameObject{}, GameObject{} };
	// 位置
	auto& tran1 = gameObjects[0].GetTransform();
	tran1.SetPosition({ 0, -0.5, 0 });
	tran1.SetRotation({ 0, 0, 90 });
	auto& tran2 = gameObjects[1].GetTransform();
	tran2.SetPosition({ 0, 0.5, 0 });
	tran2.SetScale({ .5, .5, 1 });
	// MeshRenderers-----------------------------------------------------------------------
	renderers.emplace_back(&triangle, "Shaders/ColorCircle");
	renderers.emplace_back(&square, "Shaders/ChessBoard");
	renderers[0].BindGameObject(gameObjects[0]);
	renderers[1].BindGameObject(gameObjects[1]);
}

void bindEvents()
{
	gameObjects[1].AddUpdateListener([&](GameObject& o) { square.Update(o); });
}

void display() {
	// 清屏 (屏幕缓冲区? 绘制缓冲区? Who knows...)
	glClearColor(.5, .5, .5, 1);
	// 怎么又 Clear 了?
	glClear(GL_COLOR_BUFFER_BIT);
	Time::UpdateTime();
	for(auto& gameObject:gameObjects)
	{
		gameObject.Update();
	}
	for (const auto& renderer : renderers)
	{
		renderer.Display();
	}
	glFlush();
	glutPostRedisplay();
	// std::cout << "display" << std::endl;
}

/// <summary>
/// 键盘事件
/// </summary>
/// <param name="key"></param>
/// <param name="x"></param>
/// <param name="y"></param>
void keyfunc(GLboolean key, GLint x, GLint y)
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
	// 绑定输入
	glutKeyboardFunc(keyfunc);
	// 渲染
	glutDisplayFunc(display);

	glutMainLoop();
	return 0;
}