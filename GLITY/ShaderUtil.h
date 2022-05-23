#pragma once

#include "pch.h"
#include <vector>

class ShaderUtil
{
private:
	/// <summary>
	/// 默认 Shader 文件夹
	/// </summary>
	static const std::string DefaultShaderDir;
	static std::vector<std::string> ScanShaderNames(const std::string& path);
public:
	static GLuint LoadShaderByName(const std::string& shaderPathNoExtension);
    static GLuint LoadShaderByName(const std::string& vertShaderPath, const std::string& fragShaderPath);
	static std::vector<GLuint> LoadAllShaders();
};
