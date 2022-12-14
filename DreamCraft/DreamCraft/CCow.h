#pragma once
#include "CAnimal.h"

#include "AnimalHead.h"
#include "AnimalBody.h"
#include "AnimalLeg.h"

class CCow : public CAnimal
{
private:
	AnimalHead Head;
	AnimalBody Body;
	AnimalLeg Leg1;
	AnimalLeg Leg2;
	AnimalLeg Leg3;
	AnimalLeg Leg4;

public:
	CCow(glm::vec3 Position, Form animalForm);
	virtual ~CCow();			//소멸자도 버츄얼 해주는게 좋음

	virtual void Release() override;			//소멸될 때 할 일

	virtual void Update() override;
	virtual void Render() override;		// 털 깎은 양, 안 깎은 양
};