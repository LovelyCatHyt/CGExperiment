#pragma once
#include <map>
#include "pch.h"

class MeshRenderer : public virtual Component
{
private:	
	Mesh* _mesh;
	static std::map<std::string, GLuint> PathToProgramDict;
    
    static int GetShader(const char* shaderPathNoExtension);
    static int GetShader(const char* vertShaderPath, const char* fragShaderPath);
public:
    static std::vector<MeshRenderer> renderers;
    static const GLint projectMatLoc = 0;
    static const GLint modelMatLoc = 1;
    static bool depthTest;
    static bool cullFace;

    GLuint shaderProgram;
	MeshRenderer() = delete;
    MeshRenderer(MeshRenderer&& other) noexcept;
	MeshRenderer(GameObject& obj, Mesh* mesh, GLuint shaderProgram);
    MeshRenderer(GameObject& obj, Mesh* mesh, const char* shaderPathNoExtension);
    MeshRenderer(GameObject& obj, Mesh* mesh, const char* vertShaderPath, const char* fragShaderPath);

    GLint GetUniformLoc(const char* uniformName) const;
	void Display() const;
    std::string Name() override;
};

