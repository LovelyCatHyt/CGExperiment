#include "pch.h"
#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const std::string& path, GLint wrapMode, bool mipMap, GLint filterMode, bool enableAnisotropy) :
    wrapMode(wrapMode), filterMode(filterMode), enableAnisotropy(enableAnisotropy)
{
    // 生成纹理, 设置参数
    glGenTextures(1, &textureId);
    BindTexture();
    SetTextureParameters();
    // 加载图像
    if(stbi_is_16_bit(path.c_str()))
    {
        unsigned short* data = stbi_load_16(path.c_str(), &width, &height, &channel, 0);
#ifdef _DEBUG
        std::cerr << "Loaded 16 bits texture: \"" << path << "\"(" << width << ", " << height << "), channel: " << channel << std::endl;
#endif

        GLenum fileFormat;
        switch (channel)
        {
        case 1:
            fileFormat = GL_LUMINANCE;
            break;
        case 2:
            fileFormat = GL_RG;
            break;
        case 3:
            fileFormat = GL_RGB;
            break;
        case 4:
            fileFormat = GL_RGBA;
            break;
        default:
            fileFormat = GL_RGBA;
#ifdef _DEBUG
            std::cerr << "texture channel invalid!" << std::endl;
#endif
            break;
        }
        glTexImage2D(GL_TEXTURE_2D, 0, fileFormat, width, height, 0, fileFormat, GL_UNSIGNED_SHORT, data);
        // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16, width, height, 0, fileFormat, GL_UNSIGNED_SHORT, data);
        if (mipMap)
        {
            glGenerateMipmap(GL_TEXTURE_2D);
        }

        stbi_image_free(data);
    }
    else
    {
        unsigned char* data = stbi_load(path.c_str(), &width, &height, &channel, 0);
#ifdef _DEBUG
        std::cerr << "Loaded 8 bits texture: \"" << path << "\"(" << width << ", " << height << "), channel: " << channel << std::endl;
#endif

        GLenum fileFormat;
        switch (channel)
        {
        case 1:
            fileFormat = GL_R;
            break;
        case 2:
            fileFormat = GL_RG;
            break;
        case 3:
            fileFormat = GL_RGB;
            break;
        case 4:
            fileFormat = GL_RGBA;
            break;
        default:
            fileFormat = GL_RGBA;
#ifdef _DEBUG
            std::cerr << "texture channel invalid!" << std::endl;
#endif
            break;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, fileFormat, GL_UNSIGNED_BYTE, data);
        if (mipMap)
        {
            glGenerateMipmap(GL_TEXTURE_2D);
        }

        stbi_image_free(data);
    }

    
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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMode);
    // 各向异性过滤
    if (enableAnisotropy)
    {
        GLfloat maxAnisotropy;
        glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropy);
    }
    else
    {
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1);
    }
}
