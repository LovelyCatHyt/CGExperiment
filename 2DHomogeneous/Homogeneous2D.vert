#version 430 core
uniform mat4 model_matrix;
uniform mat4 projection_matrix;
uniform uint which_polygon;
layout (location = 0) in vec4 t_pos;
layout (location = 1) in vec4 color;
out vec4 vs_fs_color;
//----------------------------------
vec3 trans_points = vec3(vec2(t_pos),t_pos.w);


//float theta_rotate = radians(360*1000000);�������

ivec2 rotate_point = ivec2(64,0);
vec2 scale_ratio  = vec2(2,2);
mat2x2 scale_mat = mat2x2(1,0,\
                          0,1); 
ivec2 fixed_point = ivec2(32,0);
//----------------------------------
//vec3 trans_points_homogeneous = vec3(vec2(t_pos),127);
//��άƽ�ƾ���
float tx=-0.3,ty=0.4;
mat3x3 translation_homogeneous = mat3x3(1   ,0  ,0,\
                                        0   ,1  ,0,\
                                        tx  ,ty ,1);
//��ά��ת����
float theta_rotate = radians(90);
mat3x3 rotate_homogeneous = mat3x3(cos(theta_rotate)    ,sin(theta_rotate)  ,0,\
                                   -sin(theta_rotate)   ,cos(theta_rotate)  ,0,\
                                   0                    ,0                  ,1);
//��ά���ž���
float scale_ratio_x=0.5,scale_ratio_y = 2;
mat3x3 scale_homogeneous = mat3x3(scale_ratio_x ,0              ,0,\
                                  0             ,scale_ratio_y  ,0,\
                                  0             ,0              ,1);

//----------------------------------

void main(void)
{

//��������ʾ--Ŀ���ǽ��ƽ�ơ����š���ת�ܹ�������ϵ�����
//ƽ�Ʋ���
//    trans_points = translation_homogeneous * trans_points;
//��ת����
//    trans_points = rotate_homogeneous * trans_points;
//���Ų���
//    trans_points = scale_homogeneous * trans_points;
//��ϲ���
//1. ��ƽ��0.3����ƽ��0.4����ת90�ȣ�
//    trans_points = translation_homogeneous * rotate_homogeneous * trans_points;
//2. ������ĵ���ת90��
//�⣺�Ƚ�ͼԪ�����Ƶ�����ԭ�㣬Ȼ����ת��Ȼ�����Ƶ�ͼԪ����ԭλ��
    

//--------------------------------------------------------------------
    gl_Position = vec4(vec2(trans_points),-1,1);
    vs_fs_color = color;
}
