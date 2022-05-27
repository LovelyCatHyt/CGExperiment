#include "pch.h"
#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const std::string& path, GLint wrapMode, bool mipMap, GLint filterMode)
{
    // 生成纹理, 设置参数
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMode);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMode);
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
