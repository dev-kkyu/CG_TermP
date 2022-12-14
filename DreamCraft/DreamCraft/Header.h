#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <random>
#include <utility>		// pair땜에
#include <gl/glew.h>											//--- 필요한 헤더파일 include
#include <gl/freeglut.h>
//#include <gl/freeglut_ext.h>
//#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
//#include <gl/glm/gtc/matrix_transform.hpp>

using namespace std;

extern GLint winWidth, winHeight;
extern GLuint BlockVAO, InvenVAO;
extern GLuint shaderID; //--- 세이더 프로그램 이름

extern pair<float, float> MouseAngle;
extern GLuint Texture[50];
extern GLuint ItemTexture[6][6];


#define 맨손		100
#define 칼			101
#define 가위		102
#define 곡괭이		103
#define 최강무기	109

//#define 기본블럭	200
#define 기본흙		201
#define 잔디흙		202
#define 벼			203
#define 양털		204

#define 나무		220
#define 나무2		221
#define 나무줄기	222
#define 나무줄기2	223
#define 나뭇잎		224

#define 돼지		211
#define 소			212
#define 닭			213
#define 양			214
#define 무너양		215
#define 양털아이템	216