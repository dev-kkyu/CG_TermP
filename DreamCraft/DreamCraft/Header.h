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
extern GLuint BlockVAO, edgeVAO;
extern GLuint shaderID; //--- 세이더 프로그램 이름

extern pair<float, float> MouseAngle;
