#include "Head.h"

Head::Head()
{
}

Head::Head(glm::vec3 Color)
{
	this->Color = Color;
	Update();
}

Head::~Head()
{
}

void Head::Update()
{
	glm::mat4 Scale;
	glm::mat4 Trans;
	glm::mat4 Rotate;

	Trans = glm::translate(Unit, glm::vec3(0, 0.5f, 0));
	Scale = glm::scale(Unit, glm::vec3(0.5));	//�Ӹ������� 0.5

	Change = Scale * Trans;		//���� �ø��� ���

	Trans = glm::translate(Unit, glm::vec3(0, 1.35, 0));
	Change = Trans * Change;	//�ٵ� ���� �÷���

	Rotate = glm::rotate(Unit, glm::radians(Direction), glm::vec3(0, 1, 0));
	Change = Rotate * Change;	//ĳ���� �����ֱ�


	Trans = glm::translate(Unit, glm::vec3(Position.x, Position.y - 2.f, Position.z));
	Change = Trans * Change;	// �� ���������� �̵�
}
