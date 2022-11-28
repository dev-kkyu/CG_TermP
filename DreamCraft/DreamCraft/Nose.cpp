#include "Nose.h"

Nose::Nose()
{
}

Nose::Nose(glm::vec3 Color)
{
	this->Color = Color;
	Update();
}

Nose::~Nose()
{
}

void Nose::Update()
{
	glm::mat4 Scale;
	glm::mat4 Trans;
	glm::mat4 Rotate;

	Scale = glm::scale(Unit, glm::vec3(0.1, 0.1, 0.05));	//������ �ñ⶧���� �����غ����� y �÷���

	Change = Scale;		// ���

	Trans = glm::translate(Unit, glm::vec3(0, 1.6, -0.25));
	Change = Trans * Change;	//���ϴ� ��ġ�� �̵�

	Rotate = glm::rotate(Unit, glm::radians(Direction), glm::vec3(0, 1, 0));
	Change = Rotate * Change;	//ĳ���� �����ֱ�


	Trans = glm::translate(Unit, glm::vec3(Position.x, Position.y - 2.f, Position.z));
	Change = Trans * Change;	// �� ���������� �̵�
}
