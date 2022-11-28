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
	Scale = glm::scale(Unit, glm::vec3(0.5));	//머리사이즈 0.5

	Change = Scale * Trans;		//위로 올리고 축소

	Trans = glm::translate(Unit, glm::vec3(0, 1.35, 0));
	Change = Trans * Change;	//바디 위로 올려줌

	Rotate = glm::rotate(Unit, glm::radians(Direction), glm::vec3(0, 1, 0));
	Change = Rotate * Change;	//캐릭터 돌려주기


	Trans = glm::translate(Unit, glm::vec3(Position.x, Position.y - 2.f, Position.z));
	Change = Trans * Change;	// 내 포지션으로 이동
}
