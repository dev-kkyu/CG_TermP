#pragma once
#include "CAnimalParts.h"

class CChickenLeg : public CAnimalParts
{
	float rotateValue;
	bool isrotDirec;

	int LocationX;		// ����, ������ ������ -1, 1�� ����ϱ�

public:
	CChickenLeg(glm::vec3 Position, int LocationX);
	~CChickenLeg();

	virtual void Render() override;
	virtual void Update() override;
};

