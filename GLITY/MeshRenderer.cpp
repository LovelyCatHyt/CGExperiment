#include "pch.h"
#include "ShaderUtil.h"

class GameObject;

std::map<std::string, GLuint> MeshRenderer::PathToProgramDict;
std::vector<MeshRenderer> MeshRenderer::renderers;
bool MeshRenderer::depthTest = true;
bool MeshRenderer::cullFace = true;
MeshRenderer::MeshRenderer(MeshRenderer&& other) noexcept :
    Component(other._gameObject),
    _mesh(other._mesh),
    shaderProgram(other.shaderProgram)
{
    other._gameObject = nullptr;
    if(_gameObject)
    {
        _gameObject->RegisterRenderer(*this);
    }
}

MeshRenderer::MeshRenderer(GameObject& obj, Mesh* const mesh, GLuint shaderProgram) :Component(obj), _mesh(mesh), shaderProgram(shaderProgram)
{
	obj.RegisterRenderer(*this);
}

int MeshRenderer::GetShader(const char* shaderPathNoExtension)
{
    if (PathToProgramDict.find(shaderPathNoExtension) == PathToProgramDict.cend())
    {
        PathToProgramDict[shaderPathNoExtension] = ShaderUtil::LoadShaderByName(shaderPathNoExtension);
    }
    return PathToProgramDict[shaderPathNoExtension];
}

int MeshRenderer::GetShader(const char* vertShaderPath, const char* fragShaderPath)
{
    return ShaderUtil::LoadShaderByName(vertShaderPath, fragShaderPath);
}

//MeshRenderer::MeshRenderer(Mesh* mesh, const char* shaderPathNoExtension):Component(nullptr), _mesh(mesh)
//{
//    shaderProgram = GetShader(shaderPathNoExtension);
//}

MeshRenderer::MeshRenderer(GameObject& obj, Mesh* mesh, const char* shaderPathNoExtension) :
    Component(obj),
    _mesh(mesh)
{
    shaderProgram = GetShader(shaderPathNoExtension);
	obj.RegisterRenderer(*this);
}

MeshRenderer::MeshRenderer(GameObject& obj, Mesh* mesh, const char* vertShaderPath, const char* fragShaderPath) :
    Component(obj),
    _mesh(mesh)
{
    shaderProgram = GetShader(vertShaderPath, fragShaderPath);
    obj.RegisterRenderer(*this);
}

GLint MeshRenderer::GetUniformLoc(const char* uniformName) const
{
    auto temp = glGetUniformLocation(shaderProgram, uniformName);
#ifdef _DEBUG
    if(temp == -1)
    {
        std::cerr<<"Location of \""<<uniformName<<"\" in program "<< shaderProgram<<" not found!"<<std::endl;
    }
#endif
    return temp;
}

void MeshRenderer::Display() const
{
    if(!enabled) return;
	glUseProgram(shaderProgram);
	glBindVertexArray(_mesh->vaoId);
	// 模型空间->世界空间
	const auto& transform = GetTransform();
	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, transform.LocalToWorldMat4X4().raw());
    // 世界空间->NDC
    glUniformMatrix4fv(projectMatLoc, 1, GL_FALSE, Camera::main->projectMat.raw());

	glDrawElements(_mesh->drawType, static_cast<GLsizei>(_mesh->indices.size()), GL_UNSIGNED_INT, 0);
}

std::string MeshRenderer::Name()
{
    return "MeshRendererDefaultName";
}
