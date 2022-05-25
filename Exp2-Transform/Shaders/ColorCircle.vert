#version 430 core
layout(location = 0) in vec3 vPosition;
out vec4 color;
out vec2 screenPosition;

layout(location = 0) uniform mat4 projectMat;
layout(location = 1) uniform mat4 modelMat;
uniform float time;
uniform float speed;
uniform vec2 center;
uniform vec3 sinTime;

// rotate around 'center' at speed of 'speed' using 'time'
mat4 rotateAround = 

/*移回原本的位置*/
mat4(
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	center.x, center.y, 0, 1
)
* /*旋转*/
mat4(
	cos(speed * time), sin(speed * time), 0.0, 0.0,
	-sin(speed * time), cos(speed * time), 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	0, 0, 0, 1.0
)
* /*缩放*/
mat4
(
	1 + 0.5f * sinTime.y, 0, 0, 0,
	0, 1 + 0.5f * sinTime.y, 0, 0,
	0, 0, 1 + 0.5f * sinTime.y, 0,
	0, 0, 0, 1
)
* /*移动到 center*/
mat4(
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	-center.x, -center.y, 0, 1
);

void main()
{ 
	gl_Position = rotateAround * vec4(vPosition, 1);
    gl_Position = projectMat * gl_Position;
    // gl_Position = gl_Position / gl_Position.w;
	screenPosition = vPosition.xy;
	color = vec4(1,0,0,1);
}
