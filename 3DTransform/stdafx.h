// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <cstdlib>
#include <iostream>
// using namespace std;

/* Use glew.h instead of gl.h to get all the GL prototypes declared */
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "LoadShaders.h"

#pragma comment (lib, "glew32.lib")
#pragma comment (lib, "freeglut.lib")

#define BUFFER_OFFSET(x)  ((const GLvoid*) sizeof(x))

void keyboard(unsigned char key, int x, int y);
void init();
void display();