#pragma once
#include "vmath.h"
#include <vector>

class Mesh
{
private:
	Mesh() :vertices(), indices(), drawType(GL_TRIANGLES) {}
	static std::vector<Mesh*> Meshes;
public:
	/// <summary>
	/// 顶点
	/// </summary>
	std::vector<vmath::vec3> vertices;
    /// <summary>
    /// 法线
    /// </summary>
    std::vector<vmath::vec3> normals;
    /// <summary>
    /// 纹理坐标
    /// </summary>
    std::vector<vmath::vec3> textcoords;
	/// <summary>
	/// 三角形索引
	/// </summary>
	std::vector<unsigned int> indices;
	
	GLuint vaoId;
	GLenum drawType;
	static Mesh& GenMesh();
    static Mesh& LoadMesh(const std::string& path);
	static void Init();
};

