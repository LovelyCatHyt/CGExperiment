#include "stdafx.h"
#include <filesystem>
#include "ShaderUtil.h"

// main.cpp : �������̨Ӧ�ó������ڵ㡣

enum Buffer_IDs { ArrayBuffer = 0 };
enum Attrib_IDs { vPosition = 0 };
const int BufferCount = 1;
const int VerticesArrayCount = 1;
GLuint VAOs[VerticesArrayCount];
GLuint buffers[BufferCount];
/// <summary>
/// ��һ����������Ķ�����
/// </summary>
const GLuint VerticesCount = 4;
GLint Mode_View_Loc;
GLint PixelSize;
std::vector<GLuint> shaders;

void init() {
	// ���� VerticesArrayCount ����������, �������������Ʊ��浽 VAOs ��
	glGenVertexArrays(VerticesArrayCount, VAOs);
	// �󶨶�������(��һû����ֵ��û�����ָ��, ���˸�ʲô����??)
	glBindVertexArray(VAOs[0]);
	GLfloat vertices[VerticesCount][2] = {
		{-1, -1},
		{1, -1},
		{1, 1},
		{-1, 1}
	};
	// ���� BufferCount ������, ����������(GLuint)���浽 buffers(GLuint[]) ��
	glGenBuffers(BufferCount, buffers);
	// ��Ŀ�껺��(GLenum)����������(GLuint)��
	glBindBuffer(GL_ARRAY_BUFFER, buffers[ArrayBuffer]);
	// ���ڴ洫�仺�����ݵ��Դ�
	// void glBufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage)
	// target: ����Ŀ��; size: �����С(���ֽڼ�); data: ��������; usage: ��;
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	shaders = ShaderUtil::LoadAllShaders();
	// ʹ�øոռ��صĵ�һ�� Shader
	glUseProgram(shaders[0]);
	// void glVertexAttribPointer(GLuint index, GLint size, GLenum type,
	// GLboolean normalized, GLsizei stride, const GLvoid* pointer);
	// void ���嶥������(������������, ÿ��������Ҫ�ķ�����, ������������, �Ƿ��һ���洢, Ԫ�ؼ��ƫ��ֵ(0Ϊ��������), ��ʼλ�õ�ƫ��ֵ)
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	// ��������Ϊ vPosition �Ķ�������(���������???)
	glEnableVertexAttribArray(vPosition);
	//glVertexAttrib2f(vPosition, 0.9, 0.9);
	// Mode_View_Loc ��ɶ����??
	Mode_View_Loc = glGetUniformLocation(shaders[0], "ModeColor");
	PixelSize = glGetUniformLocation(shaders[4], "PixelSize");
	glUniform1f(Mode_View_Loc, 0.5f);
	}
	GLuint i;

	void display() {
		// ���� (��Ļ������? ���ƻ�����? Who knows...)
		glClearColor(1, 1, 1, 1);
		// ��ô�� Clear ��?
		glClear(GL_COLOR_BUFFER_BIT);
		// �󶨶�������
		glBindVertexArray(VAOs[0]);
		// ���� point size ����...? �ǲ����û�����
		glEnable(GL_PROGRAM_POINT_SIZE);
		//glDisable(GL_PROGRAM_POINT_SIZE);
		glUniform2f(PixelSize, 1.0f / glutGet(GLUT_WINDOW_WIDTH), 1.0f / glutGet(GLUT_WINDOW_HEIGHT));
		// ����ָ��, ��ž��Ǵ�˵�е� draw call?
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		// ?
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
		// ��ʼ��: ���û���, ���� shader
		init();
		// ������
		glutKeyboardFunc(keyfunc);
		// ��Ⱦ
		glutDisplayFunc(display);
		// ������ѭ��--ѭ������Ƥ, ȫtm�ֶ�! ʹ����һ������, ֻ����ĳЩ�����¼�ʱ�Ż��ػ�, ����������ڴ�С, ������굥��, �����������ʱ�����Ų������ display
		glutMainLoop();
		return 0;
	}