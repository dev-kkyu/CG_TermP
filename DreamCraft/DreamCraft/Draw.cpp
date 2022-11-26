#include "Draw.h"

float C_RotYAngle;

GLvoid drawScene() //--- �ݹ� �Լ�: �׸��� �ݹ� �Լ�
{
	glEnable(GL_DEPTH_TEST);	//��������
	glEnable(GL_DITHER);        // ǥ���� �Ų�����
	glEnable(GL_CULL_FACE);     // �ø�
	glEnable(GL_LINE_SMOOTH);   // ��Ƽ �ٸ����
	glEnable(GL_POLYGON_SMOOTH);// ��Ƽ �ٸ����
	glShadeModel(GL_SMOOTH);    // �ε巯�� ������ �����մϴ�.

	glClearColor(0.f, 0.f, 0.f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//���� ����� ��ġ
	GLuint lightColorLocation = glGetUniformLocation(shaderID, "lightColor");	//--- lightColor �� ����: (1.0, 1.0, 1.0) ���
	glUniform3f(lightColorLocation, 1.f, 1.f, 1.f);
	GLuint lightPosLocation = glGetUniformLocation(shaderID, "lightPos"); //--- lightPos �� ����: (0.0, 0.0, 5.0);
	glUniform3f(lightPosLocation, 0.0, 0.0, 5.0);

	// ������ȯ - ��������
	glm::mat4 projection = glm::perspective(glm::radians(60.0f), (float)winWidth / (float)winHeight, 0.1f, 200.f);
	GLuint projectionLocation = glGetUniformLocation(shaderID, "projectionTransform"); //--- ���� ��ȯ �� ����
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

	// ī�޶� ��ȯ
	glm::vec3 cPos(0, 0.f, 3.f);				//ī�޶� ��ġ ����
	glm::mat4 cameraRot = glm::rotate(glm::mat4(1.f), glm::radians(-MouseAngle.first), glm::vec3(0.f, 1.f, 0.f));
	cameraRot = glm::rotate(cameraRot, glm::radians(-MouseAngle.second), glm::vec3(1.f, 0.f, 0.f));
	cPos = cameraRot * glm::vec4(cPos, 1.f);

	glm::vec3 cameraPos = glm::vec3(cPos.x, cPos.y, cPos.z); //--- ī�޶� ��ġ (��� ������)
	glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f); //--- ī�޶� �ٶ󺸴� ���� (��𺼰��� �ϸ�ɵ�)
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //--- ī�޶� ���� ����->������(���⸸) (�����ϸ� ȭ�� ���ϰŲٷκ���)

	glm::mat4 view = glm::lookAt(cameraPos, cameraDirection, cameraUp);// *cameraRevolution;

	GLuint viewLocation = glGetUniformLocation(shaderID, "viewTransform"); //--- ���� ��ȯ ����
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));

	// fragment ���̴��� �Ѿ�� ī�޶� ��ǥ(�������)
	GLuint viewPosLocation = glGetUniformLocation(shaderID, "viewPos");		//--- viewPos �� ����: ī�޶� ��ġ
	glUniform3f(viewPosLocation, cameraPos.x, cameraPos.y, cameraPos.z);


	//��ü ����
	GLuint objColorLocation = glGetUniformLocation(shaderID, "objectColor"); //--- object Color�� ����: (1.0, 0.5, 0.3)�� ��
	glUniform3f(objColorLocation, 1.0, 0.5, 0.3);

	//�𵨺�ȯ
	GLuint modelLocation = glGetUniformLocation(shaderID, "modelTransform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.f))); //--- modelTransform ������ ��ȯ �� �����ϱ�

	//��ο�
	glBindVertexArray(BlockVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);




















	glutSwapBuffers();							// ȭ�鿡 ����ϱ�
}