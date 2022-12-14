#include "CChickenLeg.h"

CChickenLeg::CChickenLeg(glm::vec3 Position, int LocationX)
	: CAnimalParts{ Position, �� }, LocationX{ LocationX }, rotateValue(0.f), isrotDirec(false)
{
}

CChickenLeg::~CChickenLeg()
{
}

void CChickenLeg::Render()
{
	glBindVertexArray(BlockVAO);

	GLuint selectColorLocation = glGetUniformLocation(shaderID, "selectColor");	//--- �ؽ�ó ���
	glUniform1i(selectColorLocation, 0);

	GLuint objectColor = glGetUniformLocation(shaderID, "objectColor");
	glUniform4f(objectColor, 1, 0, 1, 1);

	GLuint model = glGetUniformLocation(shaderID, "modelTransform");
	glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(Change));

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void CChickenLeg::Update()
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

	Scale = glm::scale(Unit, glm::vec3(0.25, 0.35, 0.25));	// �ٸ����� 0.35, �ʺ� 0.25

	Change = Scale * Change;

	Trans = glm::translate(Unit, glm::vec3(0, -0.35f, 0));
	Change = Trans * Change;				//���� ���� ������ �������� ������ + 

	Rotate = glm::rotate(Unit, glm::radians(rotateValue), glm::vec3(LocationX * -1.f, 0, 0));
	Change = Rotate * Change;	//�ٸ� ���� ��� ����

	Trans = glm::translate(Unit, glm::vec3(0, 0.35f, 0));
	Change = Trans * Change;				//�ٽ� ���� �ø�

	Trans = glm::translate(Unit, glm::vec3(LocationX * 0.125f, 0, 0));
	Change = Trans * Change;	// ���� ���ϴ� ��ġ(���� ������), �� ��

	Trans = glm::translate(Unit, glm::vec3(0, -1, 0));
	Change = Trans * Change;	// ��ĭ ������: ž�̵��� �߾��̱� ����

	Rotate = glm::rotate(Unit, glm::radians(Direction), glm::vec3(0, 1, 0));
	Change = Rotate * Change;	// ����������� ȸ��

	Trans = glm::translate(Unit, Position);
	Change = Trans * Change;	// �� ��ġ�� �̵�
}
