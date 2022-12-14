#include "CChickenBody.h"

CChickenBody::CChickenBody(glm::vec3 Position) : CAnimalParts{ Position, 닭 }
{
}

CChickenBody::~CChickenBody()
{
}

void CChickenBody::Render()
{
	glBindVertexArray(BlockVAO);

	GLuint selectColorLocation = glGetUniformLocation(shaderID, "selectColor");	//--- 텍스처 사용
	glUniform1i(selectColorLocation, 0);

	GLuint objectColor = glGetUniformLocation(shaderID, "objectColor");
	glUniform4f(objectColor, 0.5, 1, 1, 1);

	GLuint model = glGetUniformLocation(shaderID, "modelTransform");
	glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(Change));

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void CChickenBody::Update()
{
	glm::mat4 Trans;
	glm::mat4 Rotate;
	glm::mat4 Scale;

	Trans = glm::translate(Unit, glm::vec3(0, 0.5, 0));		// 일단 위로 올려서 계산 시작한다. 마지막에 1 내리는 거 필요.

	Change = Trans;

	Scale = glm::scale(Unit, glm::vec3(0.5));	// 몸통길이 1.5, 너비 0.75로 가자, 높이 0.75

	Change = Scale * Change;

	Trans = glm::translate(Unit, glm::vec3(0, 0.3, 0));
	Change = Trans * Change;		// 다리 위로 올려준다.

	Trans = glm::translate(Unit, glm::vec3(0, -1, 0));
	Change = Trans * Change;		// 탑미들에 맞춰준다.

	Rotate = glm::rotate(Unit, glm::radians(Direction), glm::vec3(0, 1, 0));
	Change = Rotate * Change;	// 진행방향으로 회전

	Trans = glm::translate(Unit, Position);
	Change = Trans * Change;	// 내 위치로 이동
}
