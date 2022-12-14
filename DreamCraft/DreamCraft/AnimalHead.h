#pragma once
#include "CAnimalParts.h"

class AnimalHead : public CAnimalParts
{

public:
	AnimalHead(glm::vec3 Position, int animalType);
	~AnimalHead();

	virtual void Render() override;
	virtual void Update() override;
};

