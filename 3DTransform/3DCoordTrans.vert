#version 430 core
layout (location = 0) in vec4 t_pos;
layout (location = 1) in vec4 in_color;
out vec4 vs_color;
//----------------------------------
//3DÆë´Î×ø±ê
//Æ½ÒÆ¾ØÕó
float tx=0,ty=-0.3,tz=0;
mat4 translation_3D = transpose(mat4(1,0,0,tx,
                                     0,1,0,ty,
                                     0,0,1,tz,
                                     0,0,0,1));
//Ðý×ª¾ØÕó
float rx=radians(-10),ry=radians(130),rz=radians(-10);
mat4 rotation_x = transpose(mat4(	1	,0		,0			,0,
						0	,cos(rx),-sin(rx)	,0,
						0	,sin(rx),cos(rx)	,0,
						0	,0		,0			,1));
mat4 rotation_y = transpose(mat4(	cos(ry)	,0.0	,-sin(ry)	,0.0,
						0.0		,1.0	,0.0		,0.0,
						sin(ry)	,0.0	,cos(ry)	,0.0,
						0.0		,0.0	,0.0		,1.0));

mat4 rotation_z = transpose(mat4(	cos(rz)	,-sin(rz)	,0	,0,
						sin(rz)	,cos(rz)	,0	,0,
						0		,0			,1	,0,
						0		,0			,0	,1));
//Ëõ·Å¾ØÕó
float sx=0.0f,sy=0.0f,sz=0.0f;
mat4 scale_3D	= mat4( sx,	0,	0,	0,
						0,	sy,	0,	0,
						0,	0,	sz,	0,
						0,	0,	0,	1);
//---------------------------------------
void main(void)
{
    gl_Position = translation_3D*rotation_y*(rotation_z*(rotation_x*t_pos));
    vs_color = in_color;
}