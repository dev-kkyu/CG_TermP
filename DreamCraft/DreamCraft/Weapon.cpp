#include "Weapon.h"
#include "CWorld.h"

extern CWorld World;

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

	if (World.getpersonView() == 3) {
		Trans = glm::translate(Unit, glm::vec3(0, 0.7, -0.5));
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

	}else { // 1��Ī

		////Scale = glm::scale(Unit, glm::vec3(0.35, 0.1, 0.7));
		//Scale = glm::scale(Unit, glm::vec3(1, 1, 0.1));

		//glm::vec3 DirectionPos{ 3.f, -1.5f, -5.f };				//ī�޶� ���� ����
		//glm::mat4 cameraDirRot = glm::rotate(glm::mat4(1.f), glm::radians(-MouseAngle.first), glm::vec3(0.f, 1.f, 0.f));
		////cameraDirRot = glm::rotate(cameraDirRot, glm::radians(-MouseAngle.second), glm::vec3(1.f, 0.f, 0.f));
		//DirectionPos = cameraDirRot * glm::vec4(DirectionPos, 1.f);

		//glm::vec3 cPos = glm::vec3(0, 0, -0.25);
		////cPos = glm::rotate(glm::mat4(1.f), glm::radians(-MouseAngle.first), glm::vec3(0.f, 1.f, 0.f)) * glm::vec4(cPos, 1.f);

		//Trans = glm::translate(Unit, glm::vec3(Position.x + cPos.x-0.5f, Position.y - 0.f, Position.z + cPos.z)+ DirectionPos); //--- ī�޶� ��ġ (��� ������)
		////cameraDirection = PlayerPos + DirectionPos; //--- ī�޶� �ٶ󺸴� ���� (��𺼰��� �ϸ�ɵ�)
		////glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //--- ī�޶� ���� ����->������(���⸸) (�����ϸ� ȭ�� ���ϰŲٷκ���)

		//Change = Trans * Scale;

		Trans = glm::translate(Unit, glm::vec3(0, 0.7, -0.5));
		Scale = glm::scale(Unit, glm::vec3(0.35, 0.1, 0.7));

		Change = Scale * Trans;		// ���� �ø��� ���

		//Rotate = glm::rotate(Unit, glm::radians(90.f), glm::vec3(0, 0, 1));
		//Change = Rotate * Change;	// �÷�

		//Trans = glm::translate(Unit, glm::vec3(0, -0.7, 0));
		//Change = Trans * Change;	//�� ���� ���� ������ �����ְ�

		//Rotate = glm::rotate(Unit, glm::radians(rotate), glm::vec3(i * 1.f, 0, 0));
		//Change = Rotate * Change;	//�� ���� ��� ����

		//Trans = glm::translate(Unit, glm::vec3(0, 0.7, 0));
		//Change = Trans * Change;	//�ٽ� ����ġ �����ְ�

		Trans = glm::translate(Unit, glm::vec3(0, 1, 0));
		Change = Trans * Change;	// ���ϴ� ����

		Trans = glm::translate(Unit, glm::vec3(i * 0.375, 0, 0));
		Change = Trans * Change;	// ���� ���ϴ� ��ġ(���� ������)

		Rotate = glm::rotate(Unit, glm::radians(Direction), glm::vec3(0, 1, 0));
		Change = Rotate * Change;	//ĳ���� �����ֱ�

		

		Trans = glm::translate(Unit, glm::vec3(Position.x, Position.y - 1.5f, Position.z));		// �� �̵���ġ�� ����
		Change = Trans * Change;
	}

}


void Weapon::change(glm::vec3 weaponColor) {

	this->Color = glm::vec3(weaponColor.r, weaponColor.g, weaponColor.b);

}