#include "AnimalBody.h"

AnimalBody::AnimalBody(glm::vec3 Position, int animalType) : CAnimalParts{ Position, animalType }
{
}

AnimalBody::~AnimalBody()
{
}

void AnimalBody::Render()
{
	glBindVertexArray(BlockVAO);

	GLuint selectColorLocation = glGetUniformLocation(shaderID, "selectColor");
	glUniform1i(selectColorLocation, 0);	//--- 색상 사용(텍스쳐 적용할 때 바꿔주기

	GLuint Color = glGetUniformLocation(shaderID, "objectColor");
	glUniform4f(Color, 1, 1, 0, 1);

	GLuint modelLocation = glGetUniformLocation(shaderID, "modelTransform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Change)); //--- modelTransform 변수에 변환 값 적용하기

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void AnimalBody::Update()
{
	glm::mat4 Trans;
	glm::mat4 Rotate;
	glm::mat4 Scale;

	Trans = glm::translate(Unit, glm::vec3(0, 0.5, 0));		// 일단 위로 올려서 계산 시작한다. 마지막에 1 내리는 거 필요.

	Change = Trans;

	Scale = glm::scale(Unit, glm::vec3(0.75, 0.75, 1.5));	// 몸통길이 1.5, 너비 0.75로 가자, 높이 0.75

	Change = Scale * Change;

	Trans = glm::translate(Unit, glm::vec3(0, 0.5, 0));
	Change = Trans * Change;		// 다리 위로 올려준다.

	Trans = glm::translate(Unit, glm::vec3(0, -1, 0));
	Change = Trans * Change;		// 탑미들에 맞춰준다.

	Rotate = glm::rotate(Unit, glm::radians(Direction), glm::vec3(0, 1, 0));
	Change = Rotate * Change;	// 진행방향으로 회전

	Trans = glm::translate(Unit, Position);
	Change = Trans * Change;	// 내 위치로 이동

}
