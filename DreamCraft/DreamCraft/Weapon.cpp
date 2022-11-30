#include "Weapon.h"

Weapon::Weapon()
{
}

Weapon::Weapon(int i) : i(i), rotate(0.f), isrotDirec(false)
{
	this->Color = glm::vec3(0, 0, 0);
	Update();
}

Weapon::~Weapon()
{
}

void Weapon::Update()
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

	Trans = glm::translate(Unit, glm::vec3(0, 0.2, -0.5));
	Scale = glm::scale(Unit, glm::vec3(0.35, 0.1, 0.7));

	Change = Scale * Trans;		// ���� �ø��� ���

	Trans = glm::translate(Unit, glm::vec3(0, -0.7, 0));
	Change = Trans * Change;	//�� ���� ���� ������ �����ְ�

	Rotate = glm::rotate(Unit, glm::radians(rotate), glm::vec3(i * 1.f, 0, 0));
	Change = Rotate * Change;	//�� ���� ��� ����

	Trans = glm::translate(Unit, glm::vec3(0, 0.7, 0));
	Change = Trans * Change;	//�ٽ� ����ġ �����ְ�

	Trans = glm::translate(Unit, glm::vec3(0, 0.65, 0));
	Change = Trans * Change;	// ���ϴ� ����

	Trans = glm::translate(Unit, glm::vec3(i * 0.375, 0, 0));
	Change = Trans * Change;	// ���� ���ϴ� ��ġ(���� ������)

	Rotate = glm::rotate(Unit, glm::radians(Direction), glm::vec3(0, 1, 0));
	Change = Rotate * Change;	//ĳ���� �����ֱ�


	Trans = glm::translate(Unit, glm::vec3(Position.x, Position.y - 2.f, Position.z));		// �� �̵���ġ�� ����
	Change = Trans * Change;
}


void Weapon::change(glm::vec3 weaponColor) {

	this->Color = glm::vec3(weaponColor.r, weaponColor.g, weaponColor.b);

}