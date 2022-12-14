#pragma once
#include "CAnimalParts.h"

class CChickenBody : public CAnimalParts
{

public:
	CChickenBody(glm::vec3 Position);
	~CChickenBody();

	virtual void Render() override;
	virtual void Update() override;
};

