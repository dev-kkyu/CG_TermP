#pragma once
#include "Header.h"

class CAnimalParts
{
protected:
	const glm::mat4 Unit;
	glm::mat4 Change;

	glm::vec3 Position;

	float Direction;

public:
	CAnimalParts(glm::vec3 Position);
	virtual ~CAnimalParts();

	virtual void Render() = 0;
	void setPos(glm::vec3 Position, float Direction);
	virtual void Update() = 0;			//���� �����Լ�, �߻�Ŭ����
};

