#pragma once
#include "CAnimalParts.h"

class AnimalBody : public CAnimalParts
{

public:
	AnimalBody(glm::vec3 Position);
	~AnimalBody();

	virtual void Render() override;
	virtual void Update() override;
};

