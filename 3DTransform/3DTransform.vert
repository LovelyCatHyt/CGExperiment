#version 430 core
layout (location = 0) in vec4 t_pos;
layout (location = 1) in vec4 in_color;
out vec4 vs_color;
uniform float tick_angle;
//----------------------------------
//3DÆë´Î×ø±ê
//Æ½ÒÆ¾ØÕó

float tx=0,ty=0,tz=0;
mat4 translation_3D = transpose(mat4(1,0,0,tx,
                                     0,1,0,ty,
                                     0,0,1,tz,
                                     0,0,0,1));
//Ðý×ª¾ØÕó
float rx=radians(tick_angle),ry=radians(tick_angle),rz=radians(tick_angle);
mat4 rotation_x = transpose(mat4(	1	,0		,0			,0,
									0	,cos(rx),-sin(rx)	,0,
									0	,sin(rx),cos(rx)	,0,
									0	,0		,0			,1));
mat4 rotation_y = transpose(mat4(	cos(ry)	,0	,-sin(ry)	,0,
									0		,1.0,0			,0,
									sin(ry)	,0	,cos(ry)	,0,
									0		,0	,0			,1.0));

mat4 rotation_z = transpose(mat4(	cos(rz)	,-sin(rz)	,0	,0,
									sin(rz)	,cos(rz)	,0	,0,
									0		,0			,1	,0,
									0		,0			,0	,1));
mat4 init_rotation =  transpose(mat4(cos(radians(130)),0,-sin(radians(130)),0,0,1,0,0,sin(radians(130)),0,cos(radians(130)),0,0,0,0,1))*\
					transpose(mat4(cos(radians(-10)),-sin(radians(-10)),0,0,sin(radians(-10)),cos(radians(-10)),0,0,0,0,1,0,0,0,0,1))*\
					transpose(mat4(1,0,0,0,0,cos(radians(-10)),-sin(radians(-10)),0,0,sin(radians(-10)),cos(radians(-10)),0,0,0,0,1));
//mat4 init_rotation = rotation_y * rotation_z * rotation_x;
//Ëõ·Å¾ØÕó
float sx=0.0,sy=0.0,sz=0.0;
mat4 scale_3D	= mat4( sx,	0,	0,	0,
						0,	sy,	0,	0,
						0,	0,	sz,	0,
						0,	0,	0,	1);

//---------------------------------------
void main(void)
{
    gl_Position = rotation_y*rotation_z*rotation_x*translation_3D*init_rotation*t_pos;
    vs_color = in_color;
}