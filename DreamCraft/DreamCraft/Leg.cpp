#include "Leg.h"

Leg::Leg() : i(i)
{
}

Leg::Leg(glm::vec3 Color, int i) : i(i), rotate(0.f), isrotDirec(false)
{
	this->Color = Color;
	Update();
}

Leg::~Leg()
{
}

void Leg::Update()
{
	if (isrotDirec) {
		rotate += 2.5f;
		if (rotate > 30.f)
			isrotDirec = false;
	}
	else {
		rotate -= 2.5f;
		if (rotate < -30.f)
			isrotDirec = true;
	}


	glm::mat4 Scale;
	glm::mat4 Trans;
	glm::mat4 Rotate;

	Trans = glm::translate(Unit, glm::vec3(0, 0.5f, 0));
	Scale = glm::scale(Unit, glm::vec3(0.25, 0.7, 0.25));	//�ٸ����� 0.7
	
	Change = Scale * Trans;		// ���� �ø��� ���

	Trans = glm::translate(Unit, glm::vec3(0, -0.7f, 0));
	Change = Trans * Change;				//���� ���� ������ �������� ������

	Rotate = glm::rotate(Unit, glm::radians(rotate), glm::vec3(i * -1.f, 0, 0));
	Change = Rotate * Change;	//�ٸ� ���� ��� ����

	Trans = glm::translate(Unit, glm::vec3(0, 0.7f, 0));
	Change = Trans * Change;				//�ٽ� ���� �ø�

	Trans = glm::translate(Unit, glm::vec3(i * 0.125, 0, 0));	
	Change = Trans * Change;	// ���� ���ϴ� ��ġ(���� ������)

	Rotate = glm::rotate(Unit, glm::radians(Direction), glm::vec3(0, 1, 0));
	Change = Rotate * Change;	//ĳ���� �����ֱ�


	Trans = glm::translate(Unit, glm::vec3(Position.x, Position.y - 2.f, Position.z));		// �� �̵���ġ�� ����
	Change = Trans * Change;


}
