#pragma once
#include <map>
#include "pch.h"

class MeshRenderer : public virtual Component
{
private:	
	Mesh* const _mesh;
	static std::map<std::string, GLuint> PathToProgramDict;
public:
    static std::vector<MeshRenderer> renderers;

    GLuint shaderProgram;

	MeshRenderer() = delete;
	MeshRenderer(GameObject& obj, Mesh* mesh, GLuint shaderProgram);
	MeshRenderer(Mesh* mesh, const char* shaderPathNoExtension);
	MeshRenderer(GameObject& obj, Mesh* mesh, const char* shaderPathNoExtension);

    GLint GetUniformLoc(const char* uniformName) const;
	void BindGameObject(GameObject& obj);
	void BindGameObject(GameObject* objPtr);
	void Display() const;
    std::string Name() override;
};

