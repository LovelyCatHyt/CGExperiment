#pragma once
#include <map>
#include "pch.h"

class MeshRenderer : public virtual Component
{
private:	
	Mesh* _mesh;
	static std::map<std::string, GLuint> PathToProgramDict;
    
    static int GetShader(const char* shaderPathNoExtension);
public:
    static std::vector<MeshRenderer> renderers;
    static const GLint projectMatLoc = 0;
    static const GLint modelMatLoc = 1;

    GLuint shaderProgram;
	MeshRenderer() = delete;
    MeshRenderer(MeshRenderer&& other) noexcept;
	MeshRenderer(GameObject& obj, Mesh* mesh, GLuint shaderProgram);
    
    MeshRenderer(Mesh* mesh, const char* shaderPathNoExtension);
	MeshRenderer(GameObject& obj, Mesh* mesh, const char* shaderPathNoExtension);

    GLint GetUniformLoc(const char* uniformName) const;
	void Display() const;
    std::string Name() override;
};

