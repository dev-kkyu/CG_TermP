#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <random>
#include <utility>		// pair����

#include "OpenGL/glew.h"
#include "OpenGL/freeglut.h"
#include "OpenGL/glm/ext.hpp"

#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "freeglut.lib")

using namespace std;

extern GLint winWidth, winHeight;
extern GLuint BlockVAO, InvenVAO;
extern GLuint shaderID; //--- ���̴� ���α׷� �̸�

extern pair<float, float> MouseAngle;
extern GLuint Texture[50];
extern GLuint ItemTexture[6][6];
extern GLuint GameEndTexture[2];


#define �Ǽ�		100
#define Į			101
#define ����		102
#define ���		103
#define �ְ�����	109

//#define �⺻����	200
#define �⺻��		201
#define �ܵ���		202
#define ��			203
#define ����		204

#define ����		220
#define ����2		221
#define �����ٱ�	222
#define �����ٱ�2	223
#define ������		224

#define ����		211
#define ��			212
#define ��			213
#define ��			214
#define ���ʾ�		215
#define ���о�����	216