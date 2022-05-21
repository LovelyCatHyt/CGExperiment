#pragma once

#include "pch.h"
#include <vector>

class ShaderUtil
{
private:
	/// <summary>
	/// д╛хо Shader нд╪Ч╪п
	/// </summary>
	static const std::string DefaultShaderDir;
	static std::vector<std::string> ScanShaderNames(const std::string& path);
public:
	static GLuint LoadShaderByName(const std::string& shaderPathNoExtension);
	static std::vector<GLuint> LoadAllShaders();
};