#pragma once

#include "stdafx.h"
#include <vector>

class ShaderUtil
{
private:
	/// <summary>
	/// Ĭ�� Shader �ļ���
	/// </summary>
	static const std::string DefaultShaderDir;
	static std::vector<std::string> ScanShaderNames(const std::string& path);
	static GLuint LoadShaderByName(const std::string& shaderPathNoExtension);
public:
	static std::vector<GLuint> LoadAllShaders();
};