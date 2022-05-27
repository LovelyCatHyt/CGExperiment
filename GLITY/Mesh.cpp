#include "pch.h"
#include "Mesh.h"
#include "OBJ_Loader.h"

std::vector<Mesh*> Mesh::Meshes{};

Mesh& Mesh::GenMesh()
{
    Meshes.emplace_back(new Mesh());
    return *Meshes[Meshes.size() - 1];
}

Mesh& Mesh::LoadMesh(const std::string& path)
{
    objl::Loader loader{};
    auto success = loader.LoadFile(path);
    Mesh& m = GenMesh();

    if (!success)
    {
#ifdef _DEBUG
        std::cerr << "Obj file \"" << path << "\" load failed!";
#endif
        return m;
    }
    // 仅加载第一个网格
    auto& loadedMesh = loader.LoadedMeshes[0];
    for (objl::Vertex v : loadedMesh.Vertices)
    {
        const auto& pos = v.Position;
        const auto& normal = v.Normal;
        const auto& textcoord = v.TextureCoordinate;
        // 坐标系貌似反了, 修正
        m.vertices.emplace_back(pos.X, pos.Y, -pos.Z);
        m.normals.emplace_back(normal.X, normal.Y, -normal.Z);
        m.textcoords.emplace_back(1 - textcoord.X, textcoord.Y, 0);
    }

    m.indices = loadedMesh.Indices;

    return m;
}

void Mesh::Init()
{
    for (auto& meshPtr : Meshes)
    {
        auto& mesh = *meshPtr;
        // 生成 VAO, VBO, EBO
        glGenVertexArrays(1, &mesh.vaoId);
        GLuint vboId;
        glGenBuffers(1, &vboId);
        GLuint eboId;
        glGenBuffers(1, &eboId);
        // 绑定到顶点数组
        glBindVertexArray(mesh.vaoId);
        // 绑定顶点缓存
        glBindBuffer(GL_ARRAY_BUFFER, vboId);
        //填充数据
        const GLsizeiptr verticesSize = sizeof(vmath::vec3) * mesh.vertices.size();
        const GLsizeiptr normalsSize = sizeof(vmath::vec3) * mesh.normals.size();
        const GLsizeiptr textcoordsSize = sizeof(vmath::vec3) * mesh.textcoords.size();
        glBufferData(GL_ARRAY_BUFFER, verticesSize + normalsSize + textcoordsSize, nullptr, GL_STATIC_DRAW);
        // 顶点坐标数
        glBufferSubData(GL_ARRAY_BUFFER, 0, verticesSize, mesh.vertices.cbegin()._Ptr);
        // 法线
        glBufferSubData(GL_ARRAY_BUFFER, verticesSize, normalsSize, mesh.normals.cbegin()._Ptr);
        // 纹理坐标
        glBufferSubData(GL_ARRAY_BUFFER, verticesSize + normalsSize, textcoordsSize, mesh.textcoords.cbegin()._Ptr);
        // 填充索引数组
        const GLsizeiptr indicesSize = sizeof(int) * mesh.indices.size();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, mesh.indices.cbegin()._Ptr, GL_STATIC_DRAW);
        // 设置顶点属性指针
        // layout (location = 0) in vec3 vPosition;
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vmath::vec3), 0);
        // layout (location = 1) in vec3 normal;
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vmath::vec3), reinterpret_cast<const void*>(verticesSize));
        // layout (location = 2) in vec3 textCoord;
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vmath::vec3), reinterpret_cast<const void*>(verticesSize + normalsSize));
        // 启用顶点属性
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
    }
}
