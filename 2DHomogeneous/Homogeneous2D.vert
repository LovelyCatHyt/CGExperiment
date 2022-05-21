#version 430 core
uniform mat4 model_matrix;
uniform mat4 projection_matrix;
uniform uint which_polygon;
layout (location = 0) in vec4 t_pos;
layout (location = 1) in vec4 color;
out vec4 vs_fs_color;
//----------------------------------
vec3 trans_points = vec3(vec2(t_pos),t_pos.w);


//float theta_rotate = radians(360*1000000);精度误差

ivec2 rotate_point = ivec2(64,0);
vec2 scale_ratio  = vec2(2,2);
mat2x2 scale_mat = mat2x2(1,0,\
                          0,1); 
ivec2 fixed_point = ivec2(32,0);
//----------------------------------
//vec3 trans_points_homogeneous = vec3(vec2(t_pos),127);
//二维平移矩阵
float tx=-0.3,ty=0.4;
mat3x3 translation_homogeneous = mat3x3(1   ,0  ,0,\
                                        0   ,1  ,0,\
                                        tx  ,ty ,1);
//二维旋转矩阵
float theta_rotate = radians(90);
mat3x3 rotate_homogeneous = mat3x3(cos(theta_rotate)    ,sin(theta_rotate)  ,0,\
                                   -sin(theta_rotate)   ,cos(theta_rotate)  ,0,\
                                   0                    ,0                  ,1);
//二维缩放矩阵
float scale_ratio_x=0.5,scale_ratio_y = 2;
mat3x3 scale_homogeneous = mat3x3(scale_ratio_x ,0              ,0,\
                                  0             ,scale_ratio_y  ,0,\
                                  0             ,0              ,1);

//----------------------------------

void main(void)
{

//齐次坐标表示--目的是解决平移、缩放、旋转能够自由组合的问题
//平移操作
//    trans_points = translation_homogeneous * trans_points;
//旋转操作
//    trans_points = rotate_homogeneous * trans_points;
//缩放操作
//    trans_points = scale_homogeneous * trans_points;
//组合操作
//1. 左平移0.3，上平移0.4，旋转90度，
//    trans_points = translation_homogeneous * rotate_homogeneous * trans_points;
//2. 相对中心点旋转90度
//解：先将图元中心移到坐标原点，然后旋转，然后再移到图元中心原位置
    

//--------------------------------------------------------------------
    gl_Position = vec4(vec2(trans_points),-1,1);
    vs_fs_color = color;
}
