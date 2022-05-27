#version 430 core
layout(location = 0) in vec3 vPosition;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 textCoord;
out vec4 color;
out vec3 modelPosition;
// out vec4 ndcPosition;
out vec3 fTextCoord;
out vec3 fNormal;

layout(location = 0) uniform mat4 projectMat;
layout(location = 1) uniform mat4 modelMat;

mat4 combinedMat = projectMat * modelMat;

void main()
{ 
    gl_Position = combinedMat * vec4(vPosition, 1);
    // gl_Position = gl_Position / gl_Position.w;

    // ndcPosition = gl_Position;
	modelPosition = vPosition;
	color = vec4(1,0,0,1);
    fTextCoord = textCoord;
    fNormal = (vec4(normal, 0) * modelMat).xyz;
}
