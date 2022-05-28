#pragma once
#include "pch.h"
#include "Glity-All.h"

class Texture
{

public:
    int width;
    int height;
    int channel;
    GLuint textureId;
    GLuint wrapMode;
    GLuint filterMode;
    bool enableAnisotropy;

    explicit Texture(const std::string& path, GLint wrapMode = GL_REPEAT, bool mipMap = true, GLint filterMode = GL_LINEAR_MIPMAP_LINEAR, bool enableAnisotropy = true);

    void BindTexture() const;
    void SetTextureParameters();
};

