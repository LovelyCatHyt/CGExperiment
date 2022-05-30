#version 430 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 textCoord;

out vec3 modelPosition;
out vec3 fTextCoord;
out vec3 fNormal;
out vec3 color;

layout(location = 0) uniform mat4 projectMat;
layout(location = 1) uniform mat4 modelMat;
layout(location = 2) uniform vec3 lightPos;
layout(location = 3) uniform vec3 lightDir;
layout(location = 4) uniform vec3 viewPos;

mat4 combinedMat = projectMat * modelMat;

uniform sampler2D texture1;
uniform sampler2D texture2;
vec3 ambient = vec3(0.1, 0.1, 0.1);

void main()
{ 
    gl_Position = combinedMat * vec4(vPosition, 1);
    // gl_Position = gl_Position / gl_Position.w;

    // ndcPosition = gl_Position;
	modelPosition = vPosition;

    fTextCoord = textCoord;

    float uvScale = 4;
	// vec3 objColor = texture(texture1, fTextCoord.xy * uvScale).rgb;
    // 仅地面的情况 恰好 不需要任何空间变换
	vec3 normal = normalize((modelMat * vec4(normal, 0)).xyz);
	vec3 pos = (modelMat * vec4(modelPosition, 1.0)).xyz;
	vec3 viewToPos  = viewPos - pos;
	float dist = length(viewToPos);
	float attenuation = 1.0 / (1 + .045f * dist + .0075f * dist * dist);
	vec3 lightColor = vec3(attenuation);

	vec3 light = normalize(lightPos - pos);
    
	vec3 diffuse = vec3(max(dot(normal, light), 0)) * lightColor;

	vec3 reflectLight = reflect(-light, normal);
	vec3 viewDir = viewToPos / dist;
	float specAmount = pow(max(dot(reflectLight, viewDir), 0), 10);
	float specStrength = 1 - texture(texture2, fTextCoord.xy * uvScale).r;
	vec3 specular = vec3(specAmount * specStrength) * lightColor;

    
	color = (ambient + diffuse + specular);
}
