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
#include <gl/glew.h>											//--- �ʿ��� ������� include
#include <gl/freeglut.h>
//#include <gl/freeglut_ext.h>
//#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
//#include <gl/glm/gtc/matrix_transform.hpp>

using namespace std;

extern GLint winWidth, winHeight;
extern GLuint BlockVAO, edgeVAO;
extern GLuint shaderID; //--- ���̴� ���α׷� �̸�

extern pair<float, float> MouseAngle;

#define �Ǽ�		100
#define Į			101
#define ����		102
#define ���		103
#define �ְ�����	109

#define �⺻��	200
#define ��			201
#define ��			202
#define ����		203

#define ����		211
#define ��			212
#define ��			213
#define ��			214
#define ���ʾ�		215