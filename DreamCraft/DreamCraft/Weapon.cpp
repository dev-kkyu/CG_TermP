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

	Change = Scale * Trans;		// 위로 올리고 축소

	Trans = glm::translate(Unit, glm::vec3(0, -0.7, 0));
	Change = Trans * Change;	//팔 흔들기 위해 원점에 맞춰주고

	Rotate = glm::rotate(Unit, glm::radians(rotate), glm::vec3(i * 1.f, 0, 0));
	Change = Rotate * Change;	//팔 흔드는 모션 해줌

	Trans = glm::translate(Unit, glm::vec3(0, 0.7, 0));
	Change = Trans * Change;	//다시 원위치 시켜주고

	Trans = glm::translate(Unit, glm::vec3(0, 0.65, 0));
	Change = Trans * Change;	// 원하는 높이

	Trans = glm::translate(Unit, glm::vec3(i * 0.375, 0, 0));
	Change = Trans * Change;	// 내가 원하는 위치(왼쪽 오른쪽)

	Rotate = glm::rotate(Unit, glm::radians(Direction), glm::vec3(0, 1, 0));
	Change = Rotate * Change;	//캐릭터 돌려주기


	Trans = glm::translate(Unit, glm::vec3(Position.x, Position.y - 2.f, Position.z));		// 내 이동위치로 무브
	Change = Trans * Change;
}


void Weapon::change(glm::vec3 weaponColor) {

	this->Color = glm::vec3(weaponColor.r, weaponColor.g, weaponColor.b);

}