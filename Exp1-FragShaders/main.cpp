#include "stdafx.h"
#include <filesystem>
#include "ShaderUtil.h"

// main.cpp : 定义控制台应用程序的入口点。

enum Buffer_IDs { ArrayBuffer = 0 };
enum Attrib_IDs { vPosition = 0 };
const int BufferCount = 1;
const int VerticesArrayCount = 1;
GLuint VAOs[VerticesArrayCount];
GLuint buffers[BufferCount];
/// <summary>
/// 第一个顶点数组的顶点数
/// </summary>
const GLuint VerticesCount = 4;
GLint Mode_View_Loc;
GLint PixelSize;
std::vector<GLuint> shaders;

void init() {
	// 生成 VerticesArrayCount 个顶点数组, 将顶点数组名称保存到 VAOs 中
	glGenVertexArrays(VerticesArrayCount, VAOs);
	// 绑定顶点数组(这一没返回值二没额外的指针, 绑定了个什么玩意??)
	glBindVertexArray(VAOs[0]);
	GLfloat vertices[VerticesCount][2] = {
		{-1, -1},
		{1, -1},
		{1, 1},
		{-1, 1}
	};
	// 生成 BufferCount 个缓存, 将缓存名称(GLuint)保存到 buffers(GLuint[]) 中
	glGenBuffers(BufferCount, buffers);
	// 绑定目标缓存(GLenum)到缓存名称(GLuint)中
	glBindBuffer(GL_ARRAY_BUFFER, buffers[ArrayBuffer]);
	// 从内存传输缓存数据到显存
	// void glBufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage)
	// target: 缓存目标; size: 缓存大小(以字节计); data: 缓存数组; usage: 用途
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	shaders = ShaderUtil::LoadAllShaders();
	// 使用刚刚加载的第一个 Shader
	glUseProgram(shaders[0]);
	// void glVertexAttribPointer(GLuint index, GLint size, GLenum type,
	// GLboolean normalized, GLsizei stride, const GLvoid* pointer);
	// void 定义顶点属性(顶点属性索引, 每个顶点需要的分量数, 属性数据类型, 是否归一化存储, 元素间的偏移值(0为紧密排列), 起始位置的偏移值)
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	// 启用索引为 vPosition 的顶点数据(哪里的数据???)
	glEnableVertexAttribArray(vPosition);
	//glVertexAttrib2f(vPosition, 0.9, 0.9);
	// Mode_View_Loc 是啥玩意??
	Mode_View_Loc = glGetUniformLocation(shaders[0], "ModeColor");
	PixelSize = glGetUniformLocation(shaders[4], "PixelSize");
	glUniform1f(Mode_View_Loc, 0.5f);
	}
	GLuint i;

	void display() {
		// 清屏 (屏幕缓冲区? 绘制缓冲区? Who knows...)
		glClearColor(1, 1, 1, 1);
		// 怎么又 Clear 了?
		glClear(GL_COLOR_BUFFER_BIT);
		// 绑定顶点数组
		glBindVertexArray(VAOs[0]);
		// 启用 point size 设置...? 那不启用会怎样
		glEnable(GL_PROGRAM_POINT_SIZE);
		//glDisable(GL_PROGRAM_POINT_SIZE);
		glUniform2f(PixelSize, 1.0f / glutGet(GLUT_WINDOW_WIDTH), 1.0f / glutGet(GLUT_WINDOW_HEIGHT));
		// 绘制指令, 大概就是传说中的 draw call?
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		// ?
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
	void keyfunc(GLboolean key, GLint x, GLint y) {
		// std::cout << "Get keycode: " << static_cast<unsigned>(key) << std::endl;
		//switch (key)
		//{
		//case 'd':
		//	glutFullScreen();
		//	break;
		//case 'e':
		//	glutReshapeWindow(500, 500);
		//	glutPositionWindow(240, 240);
		//	break;
		//case 27: // esc
		//	glutExit();
		//	break;
		//default:
		//	break;
		//}
		if (key >= '0' && ((key - '0') < shaders.size()))
		{
			glUseProgram(shaders[key - '0']);
			// display();
		}
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
		// 初始化: 设置缓存, 导入 shader
		init();
		// 绑定输入
		glutKeyboardFunc(keyfunc);
		// 渲染
		glutDisplayFunc(display);
		// 启动主循环--循环个蛇皮, 全tm手动! 使用这一个方法, 只有在某些操作事件时才会重绘, 比如调整窗口大小, 比如鼠标单击, 而键盘输入和时间流逝不会调用 display
		glutMainLoop();
		return 0;
	}