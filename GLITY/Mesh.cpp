#include "pch.h"
#include "Mesh.h"

std::vector<Mesh*> Mesh::Meshes{};

Mesh& Mesh::GenMesh()
{
	Meshes.emplace_back(new Mesh());
	return *Meshes[Meshes.size() - 1];
}

void Mesh::Init()
{
	for (auto& meshPtr : Meshes)
	{
		auto& mesh = *meshPtr;
		// 生成 VAO, VBO, EBO
		glGenVertexArrays(1, &mesh.vaoId);
		GLuint vboId;
		glGenBuffers(1, &vboId);
		GLuint eboId;
		glGenBuffers(1, &eboId);
		// 绑定到顶点数组
		glBindVertexArray(mesh.vaoId);
		// 填充顶点坐标数据
		glBindBuffer(GL_ARRAY_BUFFER, vboId);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vmath::vec3) * mesh.vertices.size(), mesh.vertices.cbegin()._Ptr, GL_STATIC_DRAW);
		// 填充索引数组
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * mesh.indices.size(), mesh.indices.cbegin()._Ptr, GL_STATIC_DRAW);
		// 设置顶点属性指针
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vmath::vec3), 0); // 对应顶点着色器中的 layout (location = 0) in vec3 aPos;
		glEnableVertexAttribArray(0); // 启用索引为 0 的顶点属性, 即坐标
	}
}
