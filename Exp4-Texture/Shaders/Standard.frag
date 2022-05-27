#version 430 core
in vec4 color;
in vec3 modelPosition;
in vec3 fTextCoord;
in vec4 ndcPosition;
out vec4 fColor;

layout(location = 0) uniform mat4 projectMat;
layout(location = 1) uniform mat4 modelMat;

mat4 combinedMat = projectMat * modelMat;

uniform sampler2D mainTexture;

void main()
{
	fColor = vec4(texture(mainTexture, fTextCoord.xy).rgb, 1);
}

