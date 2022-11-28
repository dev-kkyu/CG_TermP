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
	Scale = glm::scale(Unit, glm::vec3(0.25, 0.7, 0.25));	//다리길이 0.7
	
	Change = Scale * Trans;		// 위로 올리고 축소

	Trans = glm::translate(Unit, glm::vec3(0, -0.7f, 0));
	Change = Trans * Change;				//흔들기 위해 위쪽을 원점으로 맞춰줌

	Rotate = glm::rotate(Unit, glm::radians(rotate), glm::vec3(i * -1.f, 0, 0));
	Change = Rotate * Change;	//다리 흔드는 모션 해줌

	Trans = glm::translate(Unit, glm::vec3(0, 0.7f, 0));
	Change = Trans * Change;				//다시 위로 올림

	Trans = glm::translate(Unit, glm::vec3(i * 0.125, 0, 0));	
	Change = Trans * Change;	// 내가 원하는 위치(왼쪽 오른쪽)

	Rotate = glm::rotate(Unit, glm::radians(Direction), glm::vec3(0, 1, 0));
	Change = Rotate * Change;	//캐릭터 돌려주기


	Trans = glm::translate(Unit, glm::vec3(Position.x, Position.y - 2.f, Position.z));		// 내 이동위치로 무브
	Change = Trans * Change;


}
