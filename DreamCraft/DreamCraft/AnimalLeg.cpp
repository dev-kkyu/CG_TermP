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
	glUniform1i(selectColorLocation, 0);	//--- ���� ���(�ؽ��� ������ �� �ٲ��ֱ�

	GLuint Color = glGetUniformLocation(shaderID, "objectColor");
	glUniform4f(Color, 0, 0, 1, 1);

	GLuint modelLocation = glGetUniformLocation(shaderID, "modelTransform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Change)); //--- modelTransform ������ ��ȯ �� �����ϱ�

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

	Trans = glm::translate(Unit, glm::vec3(0, 0.5, 0));		// �ϴ� ���� �÷��� ��� �����Ѵ�. �������� 1 ������ �� �ʿ�.

	Change = Trans;

	Scale = glm::scale(Unit, glm::vec3(0.3, 0.55, 0.3));	// �ٸ����� 0.55, �ʺ� 0.3

	Change = Scale * Change;

	Trans = glm::translate(Unit, glm::vec3(0, -0.55f, 0));
	Change = Trans * Change;				//���� ���� ������ �������� ������ + 

	Rotate = glm::rotate(Unit, glm::radians(rotateValue), glm::vec3(LocationX * -1.f, 0, 0));
	Change = Rotate * Change;	//�ٸ� ���� ��� ����

	Trans = glm::translate(Unit, glm::vec3(0, 0.55f, 0));
	Change = Trans * Change;				//�ٽ� ���� �ø�

	Trans = glm::translate(Unit, glm::vec3(LocationX * 0.2f, 0, LocationZ * 0.6f));
	Change = Trans * Change;	// ���� ���ϴ� ��ġ(���� ������), �� ��

	Trans = glm::translate(Unit, glm::vec3(0,-1,0));
	Change = Trans * Change;	// ��ĭ ������: ž�̵��� �߾��̱� ����

	Rotate = glm::rotate(Unit, glm::radians(Direction), glm::vec3(0, 1, 0));
	Change = Rotate * Change;	// ����������� ȸ��

	Trans = glm::translate(Unit, Position);
	Change = Trans * Change;	// �� ��ġ�� �̵�


}
