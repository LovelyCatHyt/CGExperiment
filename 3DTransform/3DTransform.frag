#version 430 core
layout (location = 0) out vec4 color;
in vec4 vs_color;
void main(void)
{
    color = vs_color;
}