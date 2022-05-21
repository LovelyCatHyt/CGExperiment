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
		// ���� VAO, VBO, EBO
		glGenVertexArrays(1, &mesh.vaoId);
		GLuint vboId;
		glGenBuffers(1, &vboId);
		GLuint eboId;
		glGenBuffers(1, &eboId);
		// �󶨵���������
		glBindVertexArray(mesh.vaoId);
		// ��䶥����������
		glBindBuffer(GL_ARRAY_BUFFER, vboId);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vmath::vec3) * mesh.vertices.size(), mesh.vertices.cbegin()._Ptr, GL_STATIC_DRAW);
		// �����������
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * mesh.indices.size(), mesh.indices.cbegin()._Ptr, GL_STATIC_DRAW);
		// ���ö�������ָ��
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vmath::vec3), 0); // ��Ӧ������ɫ���е� layout (location = 0) in vec3 aPos;
		glEnableVertexAttribArray(0); // ��������Ϊ 0 �Ķ�������, ������
	}
}
