#version 430 core

in vec3 modelPosition;
in vec3 fTextCoord;
in vec3 fNormal;
in vec3 color;

out vec4 fColor;

layout(location = 0) uniform mat4 projectMat;
layout(location = 1) uniform mat4 modelMat;
layout(location = 2) uniform vec3 lightPos;
layout(location = 3) uniform vec3 lightDir;
layout(location = 4) uniform vec3 viewPos;

vec3 ambient = vec3(0.1, 0.1, 0.1);

// mat4 combinedMat = projectMat * modelMat;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    fColor = vec4((color) * texture(texture1, fTextCoord.xy).rgb, 1);
}

