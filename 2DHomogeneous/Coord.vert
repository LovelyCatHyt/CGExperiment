#version 430 core
uniform mat4 model_matrix;
uniform mat4 projection_matrix;
uniform uint which_polygon;
layout (location = 0) in vec4 t_pos;
//----------------------------------

void main(void)
{
    gl_Position = t_pos;
}
