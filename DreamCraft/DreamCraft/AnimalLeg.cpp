#include "AnimalLeg.h"

AnimalLeg::AnimalLeg(glm::vec3 Position, int LocationX, int LocationZ) : CAnimalParts{ Position }, LocationX{ LocationX }, LocationZ{ LocationZ }, rotateValue(0.f), isrotDirec(false)
{
}

AnimalLeg::~AnimalLeg()
{
}

void AnimalLeg::Render()
{
	glBindVertexArray(BlockVAO);

	GLuint selectColorLocation = glGetUniformLocation(shaderID, "selectColor");
	glUniform1i(selectColorLocation, 0);	//--- 색상 사용(텍스쳐 적용할 때 바꿔주기

	GLuint Color = glGetUniformLocation(shaderID, "objectColor");
	glUniform4f(Color, 0, 0, 1, 1);

	GLuint modelLocation = glGetUniformLocation(shaderID, "modelTransform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Change)); //--- modelTransform 변수에 변환 값 적용하기

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void AnimalLeg::Update()
{
	if (isrotDirec) {
		rotateValue += 1.f;
		if (rotateValue > 30.f)
			isrotDirec = false;
	}
	else {
		rotateValue -= 1.f;
		if (rotateValue < -30.f)
			isrotDirec = true;
	}

	glm::mat4 Scale;
	glm::mat4 Rotate;
	glm::mat4 Trans;

	Trans = glm::translate(Unit, glm::vec3(0, 0.5, 0));		// 일단 위로 올려서 계산 시작한다. 마지막에 1 내리는 거 필요.

	Change = Trans;

	Scale = glm::scale(Unit, glm::vec3(0.3, 0.55, 0.3));	// 다리길이 0.55, 너비 0.3

	Change = Scale * Change;

	Trans = glm::translate(Unit, glm::vec3(0, -0.55f, 0));
	Change = Trans * Change;				//흔들기 위해 위쪽을 원점으로 맞춰줌 + 

	Rotate = glm::rotate(Unit, glm::radians(rotateValue), glm::vec3(LocationX * -1.f, 0, 0));
	Change = Rotate * Change;	//다리 흔드는 모션 해줌

	Trans = glm::translate(Unit, glm::vec3(0, 0.55f, 0));
	Change = Trans * Change;				//다시 위로 올림

	Trans = glm::translate(Unit, glm::vec3(LocationX * 0.2f, 0, LocationZ * 0.6f));
	Change = Trans * Change;	// 내가 원하는 위치(왼쪽 오른쪽), 앞 뒤

	Trans = glm::translate(Unit, glm::vec3(0,-1,0));
	Change = Trans * Change;	// 한칸 내려줌: 탑미들이 중앙이기 때문

	Rotate = glm::rotate(Unit, glm::radians(Direction), glm::vec3(0, 1, 0));
	Change = Rotate * Change;	// 진행방향으로 회전

	Trans = glm::translate(Unit, Position);
	Change = Trans * Change;	// 내 위치로 이동


}
