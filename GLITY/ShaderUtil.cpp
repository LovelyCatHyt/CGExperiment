#include "pch.h"
#include "LoadShaders.h"
#include "ShaderUtil.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <cctype>

const std::string ShaderUtil::DefaultShaderDir = "Shaders/";

/// <summary>
/// string 转小写
/// <para>居然还要让我手动遍历, 这是否有些离谱</para>
/// </summary>
/// <param name="s"></param>
/// <returns></returns>
std::string str_tolower(std::string s) {
	std::transform(s.begin(), s.end(), s.begin(),
		[](unsigned char c) { return std::tolower(c); } // correct
	);
	return s;
}

std::vector<std::string> ShaderUtil::ScanShaderNames(const std::string& path)
{
	std::vector<std::string> result;
	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		if (str_tolower(entry.path().extension().string()) == ".vert")
		{
			auto fullPath = entry.path().string();
			result.emplace_back(fullPath.substr(0, fullPath.length() - 5));
			// std::cout << fullPath.substr(0, fullPath.length() - 5) << '\n';
		}
	}
	return result;
}

GLuint ShaderUtil::LoadShaderByName(const std::string& shaderPathNoExtension)
{
	std::vector<ShaderInfo> infos;
	const auto vertPath = shaderPathNoExtension + ".vert";
	infos.emplace_back(ShaderInfo{ GL_VERTEX_SHADER, vertPath.c_str(), 0 });

	// 检测是否存在片元着色器, 存在则加进去
	const auto fragPath = shaderPathNoExtension + ".frag";
	const std::ifstream temp(fragPath);
	if (temp.good())
	{
		infos.emplace_back(ShaderInfo{ GL_FRAGMENT_SHADER, fragPath.c_str(), 0 });
	}
	infos.emplace_back(ShaderInfo{ GL_NONE, NULL, 0 });
	// 加载 Shader
	return LoadShaders(infos.cbegin()._Ptr);
}

GLuint ShaderUtil::LoadShaderByName(const std::string& vertShaderPath, const std::string& fragShaderPath)
{
    ShaderInfo infos[] = 
    {
        { GL_VERTEX_SHADER, vertShaderPath.c_str(), 0 },
        { GL_FRAGMENT_SHADER, fragShaderPath.c_str(), 0 },
        { GL_NONE, NULL, 0 }
    };
    // 加载 Shader
    return LoadShaders(infos);
}

std::vector<GLuint> ShaderUtil::LoadAllShaders()
{
	auto allShaders = ScanShaderNames(DefaultShaderDir);
	std::vector<GLuint> shaders;
	for (const auto& shader : allShaders)
	{
		shaders.emplace_back(LoadShaderByName(shader));
	}
	return shaders;
}
