#include "pch.h"
#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const std::string& path, GLint wrapMode, bool mipMap, GLint filterMode, bool enableAnisotropy):
    wrapMode(wrapMode), filterMode(filterMode), enableAnisotropy(enableAnisotropy)
{
    // 生成纹理, 设置参数
    glGenTextures(1, &textureId);
    BindTexture();
    SetTextureParameters();
    // 加载图像
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channel, 0);
#ifdef _DEBUG
    std::cerr << "Loaded texture: \"" << path << "\"(" << width << ", " << height << "), channel: " << channel << std::endl;
#endif

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, channel == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, data);
    if (mipMap)
    {
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    stbi_image_free(data);
}

void Texture::BindTexture() const
{
    glBindTexture(GL_TEXTURE_2D, textureId);

}

void Texture::SetTextureParameters()
{
    glBindTexture(GL_TEXTURE_2D, textureId);
    // 环绕模式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
    // 过滤模式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // 各向异性过滤
    if(enableAnisotropy)
    {
        GLfloat maxAnisotropy;
        glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropy);
    }
    else
    {
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 0);
    }
}
