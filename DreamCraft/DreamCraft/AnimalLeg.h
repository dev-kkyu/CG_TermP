#pragma once
#include "CAnimalParts.h"

class AnimalLeg : public CAnimalParts
{
	float rotateValue;
	bool isrotDirec;

	int LocationX;		// ����, ������ ������ -1, 1�� ����ϱ�
	int LocationZ;		// ��, �� �������� -1, 1�� ����ϱ�.
public:
	AnimalLeg(glm::vec3 Position, int LocationX, int LocationZ, int animalType);
	~AnimalLeg();

	virtual void Render() override;
	virtual void Update() override;
};

