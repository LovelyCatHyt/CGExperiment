#include "pch.h"
#include "ShaderUtil.h"

class GameObject;

std::map<std::string, GLuint> MeshRenderer::PathToProgramDict;
std::vector<MeshRenderer> MeshRenderer::renderers;

MeshRenderer::MeshRenderer(GameObject& obj, Mesh* const mesh, GLuint shaderProgram) :Component(obj), _mesh(mesh), shaderProgram(shaderProgram)
{
	obj.RegisterRenderer(*this);
}

MeshRenderer::MeshRenderer(Mesh* mesh, const char* shaderPathNoExtension):Component(nullptr), _mesh(mesh)
{
	if (PathToProgramDict.find(shaderPathNoExtension) == PathToProgramDict.cend())
	{
		PathToProgramDict[shaderPathNoExtension] = ShaderUtil::LoadShaderByName(shaderPathNoExtension);
	}
	shaderProgram = PathToProgramDict[shaderPathNoExtension];
}

MeshRenderer::MeshRenderer(GameObject& obj, Mesh* mesh, const char* shaderPathNoExtension) : MeshRenderer(mesh, shaderPathNoExtension)
{	
	obj.RegisterRenderer(*this);
}

GLint MeshRenderer::GetUniformLoc(const char* uniformName) const
{
    return glGetUniformLocation(shaderProgram, uniformName);
}

void MeshRenderer::BindGameObject(GameObject& obj)
{
	BindGameObject(&obj);
}

void MeshRenderer::BindGameObject(GameObject* objPtr)
{
	_gameObjectPtr = objPtr;
	objPtr->RegisterRenderer(*this);
}

void MeshRenderer::Display() const
{
	glUseProgram(shaderProgram);
	glBindVertexArray(_mesh->vaoId);
	// const auto& vertices = _mesh->vertices;
	const auto& transform = GetTransform();
	const auto modelMatLoc = glGetUniformLocation(shaderProgram, "modelMat");
	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, transform.LocalToWorldMat4X4().raw());
	// glBindBuffer(GL_ARRAY_BUFFER, _mesh->vboId);
	glDrawElements(_mesh->drawType, static_cast<GLsizei>(_mesh->indices.size()), GL_UNSIGNED_INT, 0);
}
