#pragma once

#include "Header.h"

class RobotParts
{
protected:
	const glm::mat4 Unit;
	glm::mat4 Change;

	glm::vec3 Color;


	glm::vec3 Position;

	float Direction;

public:
	RobotParts();
	virtual ~RobotParts();

	void Render();
	void setPos(glm::vec3 Position);
	void setDirection(float Direction);
	virtual void Update() = 0;			//���� �����Լ�, �߻�Ŭ����

};
