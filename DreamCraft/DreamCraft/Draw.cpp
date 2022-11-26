#include "Draw.h"

float C_RotYAngle;

GLvoid drawScene() //--- 콜백 함수: 그리기 콜백 함수
{
	glEnable(GL_DEPTH_TEST);	//은면제거
	glEnable(GL_DITHER);        // 표면을 매끄럽게
	glEnable(GL_CULL_FACE);     // 컬링
	glEnable(GL_LINE_SMOOTH);   // 안티 앨리어싱
	glEnable(GL_POLYGON_SMOOTH);// 안티 앨리어싱
	glShadeModel(GL_SMOOTH);    // 부드러운 음영을 수행합니다.

	glClearColor(0.f, 0.f, 0.f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//조명 색상과 위치
	GLuint lightColorLocation = glGetUniformLocation(shaderID, "lightColor");	//--- lightColor 값 전달: (1.0, 1.0, 1.0) 백색
	glUniform3f(lightColorLocation, 1.f, 1.f, 1.f);
	GLuint lightPosLocation = glGetUniformLocation(shaderID, "lightPos"); //--- lightPos 값 전달: (0.0, 0.0, 5.0);
	glUniform3f(lightPosLocation, 0.0, 0.0, 5.0);

	// 투영변환 - 원근투영
	glm::mat4 projection = glm::perspective(glm::radians(60.0f), (float)winWidth / (float)winHeight, 0.1f, 200.f);
	GLuint projectionLocation = glGetUniformLocation(shaderID, "projectionTransform"); //--- 투영 변환 값 설정
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

	// 카메라 변환
	glm::vec3 cPos(0, 0.f, 3.f);				//카메라 위치 원본
	glm::mat4 cameraRot = glm::rotate(glm::mat4(1.f), glm::radians(-MouseAngle.first), glm::vec3(0.f, 1.f, 0.f));
	cameraRot = glm::rotate(cameraRot, glm::radians(-MouseAngle.second), glm::vec3(1.f, 0.f, 0.f));
	cPos = cameraRot * glm::vec4(cPos, 1.f);

	glm::vec3 cameraPos = glm::vec3(cPos.x, cPos.y, cPos.z); //--- 카메라 위치 (어디서 볼건지)
	glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f); //--- 카메라 바라보는 방향 (어디볼건지 하면될듯)
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //--- 카메라 위쪽 방향->벡터임(방향만) (음수하면 화면 상하거꾸로보임)

	glm::mat4 view = glm::lookAt(cameraPos, cameraDirection, cameraUp);// *cameraRevolution;

	GLuint viewLocation = glGetUniformLocation(shaderID, "viewTransform"); //--- 뷰잉 변환 설정
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));

	// fragment 쉐이더로 넘어가는 카메라 좌표(조명계산용)
	GLuint viewPosLocation = glGetUniformLocation(shaderID, "viewPos");		//--- viewPos 값 전달: 카메라 위치
	glUniform3f(viewPosLocation, cameraPos.x, cameraPos.y, cameraPos.z);


	//객체 색상
	GLuint objColorLocation = glGetUniformLocation(shaderID, "objectColor"); //--- object Color값 전달: (1.0, 0.5, 0.3)의 색
	glUniform3f(objColorLocation, 1.0, 0.5, 0.3);

	//모델변환
	GLuint modelLocation = glGetUniformLocation(shaderID, "modelTransform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.f))); //--- modelTransform 변수에 변환 값 적용하기

	//드로우
	glBindVertexArray(BlockVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);




















	glutSwapBuffers();							// 화면에 출력하기
}