#pragma once
#include <map>
#include "pch.h"

class MeshRenderer :
	public Component
{
private:	
	Mesh* const _mesh;
	GLuint _shaderProgram;
	static std::map<std::string, GLuint> PathToProgramDict;
public:
	MeshRenderer() = delete;
	MeshRenderer(GameObject& obj, Mesh* mesh, GLuint shaderProgram);
	MeshRenderer(Mesh* mesh, const char* shaderPathNoExtension);
	MeshRenderer(GameObject& obj, Mesh* mesh, const char* shaderPathNoExtension);
	void BindGameObject(GameObject& obj);
	void BindGameObject(GameObject* objPtr);
	void Display() const;
};

