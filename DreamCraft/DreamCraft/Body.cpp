#include "Body.h"

Body::Body()
{
}

Body::Body(glm::vec3 Color)
{
	this->Color = Color;
	Update();
}

Body::~Body()
{
}

void Body::Update()
{
	glm::mat4 Scale;
	glm::mat4 Trans;
	glm::mat4 Rotate;

	Trans = glm::translate(Unit, glm::vec3(0, 0.5f, 0));
	Scale = glm::scale(Unit, glm::vec3(0.5, 0.7, 0.25));	//������� 0.7

	Change = Scale * Trans;		//���� �ø��� ���

	Trans = glm::translate(Unit, glm::vec3(0, 0.65, 0));
	Change = Trans * Change;	//�ٸ� ���� �÷���

	Rotate = glm::rotate(Unit, glm::radians(Direction), glm::vec3(0, 1, 0));
	Change = Rotate * Change;	//ĳ���� �����ֱ�


	Trans = glm::translate(Unit, glm::vec3(Position.x, Position.y - 2.f, Position.z));
	Change = Trans * Change;	// �� ���������� �̵�
}
