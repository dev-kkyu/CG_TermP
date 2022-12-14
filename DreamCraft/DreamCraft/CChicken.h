#pragma once
#include "CAnimal.h"

#include "CChickenBody.h"
#include "CChickenHead.h"
#include "CChickenLeg.h"

class CChicken : public CAnimal
{
private:
	CChickenHead Head;
	CChickenBody Body;
	CChickenLeg Leg1;
	CChickenLeg Leg2;

public:
	CChicken(glm::vec3 Position, Form animalForm);
	virtual ~CChicken();			//소멸자도 버츄얼 해주는게 좋음

	virtual void Release() override;			//소멸될 때 할 일

	virtual void Update() override;
	virtual void Render() override;
};

