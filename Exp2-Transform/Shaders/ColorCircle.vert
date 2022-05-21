#version 430 core
layout(location = 0) in vec3 vPosition;
out vec4 color;
out vec2 screenPosition;
uniform float ModeColor;
uniform mat4 modelMat;

void main()
{ 
	gl_Position = modelMat * vec4(vPosition, 1);
	screenPosition = vPosition.xy;
	color = vec4(1,0,0,1);
}