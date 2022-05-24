// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <cstdlib>
#include <iostream>

/* Use glew.h instead of gl.h to get all the GL prototypes declared */
#include <GL/glew.h>
#include <GL/freeglut.h>
// #include "LoadShaders.h"

#  pragma comment (lib, "glew32.lib")
#  pragma comment (lib, "freeglut.lib")

#define BUFFER_OFFSET(x)  ((const void*) (x))