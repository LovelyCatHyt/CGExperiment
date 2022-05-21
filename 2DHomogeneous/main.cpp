// main.cpp : 定义控制台应用程序的入口点。

#include "stdafx.h"
enum VAO_IDs { Triangles, NumVAOs = 2 };
enum Buffer_IDs { ArrayBuffer, NumBuffers = 2 };
enum Attrib_IDs { vPosition = 0 };
GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
const GLuint NumVertices = 3;
GLuint program, program_1;

void init() {



	GLfloat vertices[NumVertices][4] = {
		//NDC,4D
		{ 0.0	,0		,1	, 1 },
		{ 0.5	,0.0	,1	, 1 },
		{ 0.0	,0.5	,1	, 1 }
	};
	static const GLfloat colors[]
	{
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
	};
	static const GLfloat coord_verteces[4][4] = {
		{-1.0	,0.0	,1.0	,1.0},
		{1.0	,0.0	,1.0	,1.0},
		{0.0	,-1.0	,1.0	,1.0},
		{0.0	,1.0	,1.0	,1.0}
	};
	glGenVertexArrays(NumVAOs, VAOs);
	glGenBuffers(NumBuffers, Buffers);

	ShaderInfo shader[] = {
		{ GL_VERTEX_SHADER, "Homogeneous2D.vert" },
		{ GL_FRAGMENT_SHADER, "Triangle.frag" },
		{ GL_NONE, NULL },
	};
	ShaderInfo shader_1[] = {
		{ GL_VERTEX_SHADER, "Coord.vert" },
		{ GL_FRAGMENT_SHADER, "Coord.frag" },
		{ GL_NONE, NULL },
	};
	//glGetShaderSource()
	program = LoadShaders(shader);
	program_1 = LoadShaders(shader_1);
	glUseProgram(program);
	glGenBuffers(NumBuffers, Buffers);
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertices));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glUseProgram(program_1);
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(coord_verteces), coord_verteces, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
}

//keyboard 函数定义
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'd':
		//glutFullScreen();
		break;
	case 'e':
		glutReshapeWindow(1024, 1024);
		glutPositionWindow(240, 240);
		break;
	case 27:
		glutExit();
		break;
	case 'c':
		break;
	default:
		break;
	}
	//glutPostRedisplay();
}

//display函数定义
void display() {
	glClearColor(.0, .0, .0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(program);
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);
	glUseProgram(program_1);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[1]);
	glBindVertexArray(VAOs[1]);
	glDrawArrays(GL_LINES, 0, 4);
	glutSwapBuffers();
	glFinish();
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	// std::cout << argc << "," << argv << std::endl;
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(1024, 1024);
	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow("Main-Window");
	glewExperimental = GL_FALSE;
	if (glewInit())
	{
		std::cerr << "Unable to Initialize GLEW" << std::endl;
	}
	init();
	glutDisplayFunc(display);
	glutKeyboardUpFunc(keyboard);
	glutMainLoop();
	return 0;
}