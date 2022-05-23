#version 430 core
layout(location = 0) in vec3 vPosition;
out vec4 color;
out vec2 screenPosition;
layout(location = 0) uniform mat4 projectMat;
layout(location = 1) uniform mat4 modelMat;
uniform vec3 sinTime;

mat2 shearMat = mat2(
            1, sinTime.y,
            sinTime.z * 0.25f, 1);

void main()
{ 
	gl_Position = modelMat * vec4(vPosition, 1);
    gl_Position = vec4(shearMat * gl_Position.xy, gl_Position.zw);
    gl_Position = projectMat * gl_Position;
    gl_Position = gl_Position / gl_Position.w;
	screenPosition = vPosition.xy;
	color = vec4(1,0,0,1);
}
