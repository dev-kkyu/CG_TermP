#pragma once
#include "CAnimalParts.h"

class CChickenLeg : public CAnimalParts
{
	float rotateValue;
	bool isrotDirec;

	int LocationX;		// 왼쪽, 오른쪽 순으로 -1, 1로 사용하기

public:
	CChickenLeg(glm::vec3 Position, int LocationX);
	~CChickenLeg();

	virtual void Render() override;
	virtual void Update() override;
};

