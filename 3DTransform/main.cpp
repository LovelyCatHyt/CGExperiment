// main.cpp : 定义控制台应用程序的入口点。

#include "stdafx.h"
enum VAO_IDs { Triangles, NumVAOs = 2 };
enum Buffer_IDs { ArrayBuffer, NumBuffers = 2 };
enum Attrib_IDs { vPosition = 0 };
GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
GLuint EBOs[1];
const GLuint NumVertices = 4;
GLuint program, program_1;
GLuint tick_time_loc, t_time_loc;
GLuint screen_width = 1024;
GLuint screen_height = 1024;

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	// std::cout << argc << "," << argv << std::endl;
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(1024, 1024);
	glutInitContextVersion(1, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow("Window");
	glewExperimental = GL_FALSE;
	if (glewInit())
	{
		std::cerr << "Unable to Initialize GLEW" << std::endl;
	}
	init();
	glutDisplayFunc(display);
	glutKeyboardUpFunc(keyboard);
	glutMainLoop();
	glUseProgram(0);
	glDeleteProgram(program);
	glDeleteProgram(program_1);
	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, Buffers);
	glDeleteBuffers(1, EBOs);
	return 0;
}

void init(void) {
	float v_p = 0.4 * sqrtf(3.0) / 2.0;
	GLfloat vertices[NumVertices][4] = {
		//NDC,4D
		{ 0.0	,0.0	,-0.4		, 1	},
		{ 0.0	,0.56	,0.0		, 1 },
		{ v_p	,0.0	,0.4 / 2	, 1 },
		{ -v_p	,0.0	,0.4 / 2	, 1 },
	};
	static const GLushort tetrahedron_indices[] =
	{
		0,1,2,2,3,0,2,1,3,0,3,1
	};
	static const GLfloat colors[]
	{
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.8f, 0.3f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.0f, 1.0f,
	};
	static const GLfloat coord_verteces[][4] = {
		{0.0	,0.0	,0.0	,1.0},
		{1.0	,0.0	,0.0	,1.0},
		{0.0	,0.0	,0.0	,1.0},
		{0.0	,1.0	,0.0	,1.0},
		{0.0	,0.0	,0.0	,1.0},
		{0.0	,0.0	,-1.0	,1.0}//因为默认在视口中是从z轴正向看去负向
	};
	static const GLfloat coord_colors[]
	{
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
	};
	

	ShaderInfo shader[] = {
		{ GL_VERTEX_SHADER, "3DTransform.vert" },
		{ GL_FRAGMENT_SHADER, "3DTransform.frag" },
		{ GL_NONE, NULL },
	};
	ShaderInfo shader_1[] = {
		{ GL_VERTEX_SHADER, "3DCoordTrans.vert" },
		{ GL_FRAGMENT_SHADER, "3DCoordTrans.frag" },
		{ GL_NONE, NULL },
	};
	
	//glGetShaderSource()
	program = LoadShaders(shader);
	program_1 = LoadShaders(shader_1);
	glGenBuffers(NumBuffers, Buffers);
	glGenBuffers(1, EBOs);
	glGenVertexArrays(NumVAOs, VAOs);
	glGenBuffers(NumBuffers, Buffers);
	//-----------------------------------------------
	glUseProgram(program);
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(tetrahedron_indices), tetrahedron_indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertices));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	t_time_loc = glGetUniformLocation(program, "tick_angle");
	//-----------------------------------------------
	glUseProgram(program_1);
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(coord_verteces) + sizeof(coord_colors), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(coord_verteces), coord_verteces);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(coord_verteces), sizeof(coord_colors), coord_colors);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(coord_verteces));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	tick_time_loc = glGetUniformLocation(program_1, "tick_angle");
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
		//glutPostRedisplay();
		break;
	case 27:
		glutExit();
		break;
	case 'c':
		break;
	default:
		break;
	}
}
void display() {
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glDisable(GL_DEPTH_TEST);
	float angle = float(GetTickCount() & 0x1FFF) / float(0x1FFF) * 360.0f;
	glClearColor(.0, .0, .0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);


	//program------------------------------------
	glUseProgram(program);
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);
	//glDrawArrays(GL_TRIANGLES, 0, NumVertices - 1);
	glUniform1f(t_time_loc, angle);
	/*glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, NULL);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, (const GLvoid*)(3 * sizeof(GLushort)));
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, (const GLvoid*)(6 * sizeof(GLushort)));
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, (const GLvoid*)(9 * sizeof(GLushort)));*/
	glDrawElements(GL_LINE_LOOP, 3, GL_UNSIGNED_SHORT, NULL);
	glDrawElements(GL_LINE_LOOP, 3, GL_UNSIGNED_SHORT, (const GLvoid*)(3 * sizeof(GLushort)));
	glDrawElements(GL_LINE_LOOP, 3, GL_UNSIGNED_SHORT, (const GLvoid*)(6 * sizeof(GLushort)));
	glDrawElements(GL_LINE_LOOP, 3, GL_UNSIGNED_SHORT, (const GLvoid*)(9 * sizeof(GLushort)));
	//program_1------------------------------------
	glUseProgram(program_1);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[1]);
	glBindVertexArray(VAOs[1]);
	//glUniform1f(tick_time_loc, angle);
	glLineWidth(5);
	glDrawArrays(GL_LINES, 0, 6);
	glFinish();
	glutPostRedisplay();
}