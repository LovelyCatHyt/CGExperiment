#include "pch.h"
#include "ShaderUtil.h"

class GameObject;

std::map<std::string, GLuint> MeshRenderer::PathToProgramDict;
std::vector<MeshRenderer> MeshRenderer::renderers;

vmath::vec3 MeshRenderer::lightPos;
bool MeshRenderer::depthTest = true;
bool MeshRenderer::cullFace = true;
MeshRenderer::MeshRenderer(MeshRenderer&& other) noexcept :
    Component(other._gameObject),
    _mesh(other._mesh),
    texture1(other.texture1),
    texture2(other.texture2),
    shaderProgram(other.shaderProgram),
    useProjectMatUniform(other.useProjectMatUniform),
    useModelMatUniform(other.useModelMatUniform),
    useLightPosUniform(other.useLightPosUniform),
    useLightDirUniform(other.useLightDirUniform),
    useViewPosUniform(other.useViewPosUniform)
{
    other._gameObject = nullptr;
    if (_gameObject)
    {
        _gameObject->RegisterRenderer(*this);
    }
}

//MeshRenderer::MeshRenderer(GameObject& obj, Mesh* const mesh, GLuint shaderProgram) :Component(obj), _mesh(mesh), shaderProgram(shaderProgram)
//{
//	obj.RegisterRenderer(*this);
//}

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

void MeshRenderer::SetTextureUniform()
{
    glUseProgram(shaderProgram);
    const auto loc1 = GetUniformLoc("texture1");
    if (loc1 != -1)
    {
        glUniform1i(loc1, 0);
    }
    const auto loc2 = GetUniformLoc("texture2");
    if (loc2 != -1)
    {
        glUniform1i(loc2, 1);
    }
}

//MeshRenderer::MeshRenderer(Mesh* mesh, const char* shaderPathNoExtension):Component(nullptr), _mesh(mesh)
//{
//    shaderProgram = GetShader(shaderPathNoExtension);
//}

void MeshRenderer::ScanUniform()
{
    useProjectMatUniform = GetUniformLoc("projectMat") != -1;
    useModelMatUniform = GetUniformLoc("modelMat") != -1;
    useLightPosUniform = GetUniformLoc("lightPos") != -1;
    useLightDirUniform = GetUniformLoc("lightDir") != -1;
    useViewPosUniform = GetUniformLoc("viewPos") != -1;
}

MeshRenderer::MeshRenderer(GameObject& obj, Mesh* mesh, const char* shaderPathNoExtension, Texture* texture, Texture* normalMap) :
    Component(obj),
    _mesh(mesh),
    texture1(texture),
    texture2(normalMap)
{
    shaderProgram = GetShader(shaderPathNoExtension);
    SetTextureUniform();
    ScanUniform();
    obj.RegisterRenderer(*this);
}

MeshRenderer::MeshRenderer(GameObject& obj, Mesh* mesh, const char* vertShaderPath, const char* fragShaderPath, Texture* texture, Texture* normalMap) :
    Component(obj),
    _mesh(mesh),
    texture1(texture),
    texture2(normalMap)
{
    shaderProgram = GetShader(vertShaderPath, fragShaderPath);
    SetTextureUniform();
    ScanUniform();
    obj.RegisterRenderer(*this);
}

GLint MeshRenderer::GetUniformLoc(const char* uniformName) const
{
    const auto temp = glGetUniformLocation(shaderProgram, uniformName);
#ifdef _DEBUG
    if (temp == -1)
    {
        std::cerr << "Location of \"" << uniformName << "\" in program " << shaderProgram << " not found!" << std::endl;
    }
#endif
    return temp;
}

void MeshRenderer::Display() const
{
    if (!enabled) return;
    glUseProgram(shaderProgram);
    // 纹理
    if (texture1)
    {
        glActiveTexture(GL_TEXTURE0);
        texture1->BindTexture();
    }
    if (texture2)
    {
        glActiveTexture(GL_TEXTURE1);
        texture2->BindTexture();
    }
    glBindVertexArray(_mesh->vaoId);
    // 设置矩阵
    // 模型空间->世界空间
    const auto& transform = GetTransform();
    if(useModelMatUniform) glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, transform.LocalToWorldMat4X4().raw());
    // 世界空间->裁剪空间
    if (Camera::main && useProjectMatUniform)
    {
        glUniformMatrix4fv(projectMatLoc, 1, GL_FALSE, Camera::main->projectMat.raw());
        auto& camTran = Camera::main->GetTransform();
        auto camPos = camTran.GetPosition();
        // 观察位置
        glUniform3f(viewPosLoc, camPos[0], camPos[1], camPos[2]);
    }
    if(useLightPosUniform) glUniform3f(lightPosLoc, lightPos[0], lightPos[1], lightPos[2]);

    glDrawElements(_mesh->drawType, static_cast<GLsizei>(_mesh->indices.size()), GL_UNSIGNED_INT, 0);
}

std::string MeshRenderer::Name()
{
    return "MeshRendererDefaultName";
}
