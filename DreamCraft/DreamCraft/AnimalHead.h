#pragma once
#include "CAnimalParts.h"

class AnimalHead : public CAnimalParts
{

public:
	AnimalHead(glm::vec3 Position);
	~AnimalHead();

	virtual void Render() override;
	virtual void Update() override;
};

