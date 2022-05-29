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

vec3 ambient = vec3(0.1, 0.1, 0.1);

// mat4 combinedMat = projectMat * modelMat;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	vec3 color = texture(texture1, fTextCoord.xy * 8).rgb;
    // 仅地面的情况 恰好 不需要任何空间变换
	vec3 normal = normalize(texture(texture2, fTextCoord.xy * 8).rbg * 2 - 1);
	vec3 pos = (modelMat * vec4(modelPosition, 1.0)).xyz;
	vec3 viewToPos  = viewPos - pos;
	float dist = length(viewToPos);
	float attenuation = 1.0 / (1 + .045f * dist + .0075f * dist * dist);
	vec3 lightColor = vec3(attenuation);

	vec3 light = normalize(lightPos - pos);
    
	vec3 diffuse = vec3(max(dot(normal, light), 0)) * lightColor;

	vec3 reflectLight = reflect(-light, normal);
	vec3 viewDir = viewToPos / dist;
	float specAmount = pow(max(dot(reflectLight, viewDir), 0), 32);
	float specStrength = 0.8;
	vec3 specular = vec3(specAmount * specStrength) * lightColor;

	fColor = vec4(color * (ambient + diffuse + specular), 1);
}

