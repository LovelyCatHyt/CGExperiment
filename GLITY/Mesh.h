#pragma once
#include "vmath.h"
#include <vector>

class Mesh
{
private:
	Mesh() :vertices(), indices(), drawType(GL_TRIANGLES) {}
	static std::vector<Mesh*> Meshes;
public:
	std::vector<vmath::vec3> vertices;
	std::vector<int> indices;
	// GLuint vboId;
	GLuint vaoId;
	GLenum drawType;
	static Mesh& GenMesh();
	static void Init();
};

