#pragma once
#include "CAnimalParts.h"

class CChickenHead : public CAnimalParts
{

public:
	CChickenHead(glm::vec3 Position);
	~CChickenHead();

	virtual void Render() override;
	virtual void Update() override;
};

