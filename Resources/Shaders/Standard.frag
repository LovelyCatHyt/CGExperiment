#version 430 core

in vec3 modelPosition;
in vec3 fTextCoord;
in vec3 fNormal;

out vec4 fColor;

layout(location = 0) uniform mat4 projectMat;
layout(location = 1) uniform mat4 modelMat;
layout(location = 2) uniform vec3 lightPos;
layout(location = 3) uniform vec3 lightDir;
layout(location = 4) uniform vec3 viewPos;

mat4 combinedMat = projectMat * modelMat;

uniform sampler2D mainTexture;

void main()
{
	fColor = vec4(texture(mainTexture, fTextCoord.xy).rgb, 1);
}

