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

	}else { // 1인칭

		////Scale = glm::scale(Unit, glm::vec3(0.35, 0.1, 0.7));
		//Scale = glm::scale(Unit, glm::vec3(1, 1, 0.1));

		//glm::vec3 DirectionPos{ 3.f, -1.5f, -5.f };				//카메라 방향 원본
		//glm::mat4 cameraDirRot = glm::rotate(glm::mat4(1.f), glm::radians(-MouseAngle.first), glm::vec3(0.f, 1.f, 0.f));
		////cameraDirRot = glm::rotate(cameraDirRot, glm::radians(-MouseAngle.second), glm::vec3(1.f, 0.f, 0.f));
		//DirectionPos = cameraDirRot * glm::vec4(DirectionPos, 1.f);

		//glm::vec3 cPos = glm::vec3(0, 0, -0.25);
		////cPos = glm::rotate(glm::mat4(1.f), glm::radians(-MouseAngle.first), glm::vec3(0.f, 1.f, 0.f)) * glm::vec4(cPos, 1.f);

		//Trans = glm::translate(Unit, glm::vec3(Position.x + cPos.x-0.5f, Position.y - 0.f, Position.z + cPos.z)+ DirectionPos); //--- 카메라 위치 (어디서 볼건지)
		////cameraDirection = PlayerPos + DirectionPos; //--- 카메라 바라보는 방향 (어디볼건지 하면될듯)
		////glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //--- 카메라 위쪽 방향->벡터임(방향만) (음수하면 화면 상하거꾸로보임)

		//Change = Trans * Scale;

		Trans = glm::translate(Unit, glm::vec3(0, 0.7, -0.5));
		Scale = glm::scale(Unit, glm::vec3(0.35, 0.1, 0.7));

		Change = Scale * Trans;		// 위로 올리고 축소

		//Rotate = glm::rotate(Unit, glm::radians(90.f), glm::vec3(0, 0, 1));
		//Change = Rotate * Change;	// 올려

		//Trans = glm::translate(Unit, glm::vec3(0, -0.7, 0));
		//Change = Trans * Change;	//팔 흔들기 위해 원점에 맞춰주고

		//Rotate = glm::rotate(Unit, glm::radians(rotate), glm::vec3(i * 1.f, 0, 0));
		//Change = Rotate * Change;	//팔 흔드는 모션 해줌

		//Trans = glm::translate(Unit, glm::vec3(0, 0.7, 0));
		//Change = Trans * Change;	//다시 원위치 시켜주고

		Trans = glm::translate(Unit, glm::vec3(0, 1, 0));
		Change = Trans * Change;	// 원하는 높이

		Trans = glm::translate(Unit, glm::vec3(i * 0.375, 0, 0));
		Change = Trans * Change;	// 내가 원하는 위치(왼쪽 오른쪽)

		Rotate = glm::rotate(Unit, glm::radians(Direction), glm::vec3(0, 1, 0));
		Change = Rotate * Change;	//캐릭터 돌려주기

		

		Trans = glm::translate(Unit, glm::vec3(Position.x, Position.y - 1.5f, Position.z));		// 내 이동위치로 무브
		Change = Trans * Change;
	}

}


void Weapon::change(glm::vec3 weaponColor) {

	this->Color = glm::vec3(weaponColor.r, weaponColor.g, weaponColor.b);

}