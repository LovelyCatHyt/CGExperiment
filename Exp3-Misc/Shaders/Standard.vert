#version 430 core
layout(location = 0) in vec3 vPosition;
out vec4 color;
out vec3 modelPosition;

layout(location = 0) uniform mat4 projectMat;
layout(location = 1) uniform mat4 modelMat;

void main()
{ 
    gl_Position = projectMat * modelMat * vec4(vPosition, 1);
    gl_Position = gl_Position / gl_Position.w;
	modelPosition = vPosition;
	color = vec4(1,0,0,1);
}
