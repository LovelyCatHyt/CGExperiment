#include "stdafx.h"
#include "TextureParaSetter.h"

TextureParaSetter::TextureParaSetter(GameObject& obj) : Component(&obj), IUpdate()
{
}

std::string TextureParaSetter::Name()
{
    return "TextureParaSetter";
}

void TextureParaSetter::Update(GameObject& obj)
{
    auto& renderer = obj.Renderer();
    auto* texture = renderer.texture;
    bool changed = false;
    if (Input::GetKeyDown('1'))
    {
        texture->wrapMode = texture->wrapMode == GL_REPEAT ? GL_CLAMP_TO_EDGE : GL_REPEAT;
        std::cout << "wrapMode: " << texture->wrapMode << std::endl;
        changed = true;
    }
    if (Input::GetKeyDown('2'))
    {
        switch (texture->filterMode)
        {
        case GL_LINEAR:
            texture->filterMode = GL_NEAREST_MIPMAP_NEAREST;
            std::cout << "filter mode: GL_NEAREST_MIPMAP_NEAREST" << std::endl;
            break;
        case GL_NEAREST_MIPMAP_NEAREST:
            texture->filterMode = GL_NEAREST_MIPMAP_LINEAR;
            std::cout << "filter mode: GL_NEAREST_MIPMAP_LINEAR" << std::endl;
            break;
        case GL_NEAREST_MIPMAP_LINEAR:
            texture->filterMode = GL_LINEAR_MIPMAP_NEAREST;
            std::cout << "filter mode: GL_LINEAR_MIPMAP_NEAREST" << std::endl;
            break;
        case GL_LINEAR_MIPMAP_NEAREST:
            texture->filterMode = GL_LINEAR_MIPMAP_LINEAR;
            std::cout << "filter mode: GL_LINEAR_MIPMAP_LINEAR" << std::endl;
            break;
        case GL_LINEAR_MIPMAP_LINEAR:
            texture->filterMode = GL_NEAREST;
            std::cout << "filter mode: GL_NEAREST" << std::endl;
            break;
        case GL_NEAREST:
            texture->filterMode = GL_LINEAR;
            std::cout << "filter mode: GL_LINEAR" << std::endl;
            break;
        }
        changed = true;
    }
    if (Input::GetKeyDown('3'))
    {
        texture->enableAnisotropy = !texture->enableAnisotropy;
        std::cout << "enableAnisotropy: " << (texture->enableAnisotropy ? "true" : "false") << std::endl;
        changed = true;
    }
    if (changed)
    {
        texture->SetTextureParameters();
    }
}
