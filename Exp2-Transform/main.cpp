#include "stdafx.h"

#include "Time.h"
#include "../GLITY/Glity-All.h"
#include "SquareDriver.h"
std::vector<MeshRenderer> renderers;
std::vector<GameObject> gameObjects;

SquareDriver square{ 2, 0.8, .333333f };

void init() {
	// Meshes------------------------------------------------------------------------------
	// ������
	auto& triangle = Mesh::GenMesh();
	triangle.indices = { 2, 1, 0 };
	triangle.vertices = {
		{-.25f, -.25f, .0f},
		{.25f, -.25f, .0f},
		{.0f, .25f, .0f} };
	// ������
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
	// λ��
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
	// ���� (��Ļ������? ���ƻ�����? Who knows...)
	glClearColor(.5, .5, .5, 1);
	// ��ô�� Clear ��?
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
/// �����¼�
/// </summary>
/// <param name="key"></param>
/// <param name="x"></param>
/// <param name="y"></param>
void keyfunc(GLboolean key, GLint x, GLint y)
{

}

int main(int argc, char* argv[])
{
	// ��ʼ�� glut	
	glutInit(&argc, argv);
	// ��ʾģʽ
	glutInitDisplayMode(GLUT_RGBA);
	// ���ڴ�С
	glutInitWindowSize(512, 512);
	// ??
	glutInitContextVersion(1, 3);
	// ??
	glutInitContextProfile(GLUT_CORE_PROFILE);
	// ��������, ����û��֪��������ص� int ��ʲô����
	glutCreateWindow("ColorCircle Windows");
	// ��ʼ�� glew
	if (glewInit())
	{
		std::cerr << "Unable to Initialize GLEW" << std::endl;
	}
	// ��ʼ��
	init();
	bindEvents();
	// ������
	glutKeyboardFunc(keyfunc);
	// ��Ⱦ
	glutDisplayFunc(display);

	glutMainLoop();
	return 0;
}