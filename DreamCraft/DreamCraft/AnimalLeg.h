#pragma once
#include "CAnimalParts.h"

class AnimalLeg : public CAnimalParts
{
	float rotateValue;
	bool isrotDirec;

	int LocationX;		// 왼쪽, 오른쪽 순으로 -1, 1로 사용하기
	int LocationZ;		// 뒤, 앞 기준으로 -1, 1로 사용하기.
public:
	AnimalLeg(glm::vec3 Position, int LocationX, int LocationZ, int animalType);
	~AnimalLeg();

	virtual void Render() override;
	virtual void Update() override;
};

