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
	virtual ~CChicken();			//�Ҹ��ڵ� ����� ���ִ°� ����

	virtual void Release() override;			//�Ҹ�� �� �� ��

	virtual void Update() override;
	virtual void Render() override;
};

