#pragma once
#include "Header.h"

class CAnimalParts
{
protected:
	const glm::mat4 Unit;
	glm::mat4 Change;

	glm::vec3 Position;

	float Direction;

	int animalType;

public:
	CAnimalParts(glm::vec3 Position, int animalType);
	virtual ~CAnimalParts();

	virtual void Render() = 0;
	void setPos(glm::vec3 Position, float Direction);
	virtual void Update() = 0;			//���� �����Լ�, �߻�Ŭ����

	void setType(int animalType);
};

