#pragma once
#include "CAnimal.h"

#include "AnimalHead.h"
#include "AnimalBody.h"
#include "AnimalLeg.h"

class CPig : public CAnimal
{
private:
	AnimalHead Head;
	AnimalBody Body;
	AnimalLeg Leg1;
	AnimalLeg Leg2;
	AnimalLeg Leg3;
	AnimalLeg Leg4;

public:
	CPig(glm::vec3 Position, Form animalForm);
	virtual ~CPig();			//�Ҹ��ڵ� ����� ���ִ°� ����

	virtual void Release() override;			//�Ҹ�� �� �� ��

	virtual void Update() override;
	virtual void Render() override;		// �� ���� ��, �� ���� ��
};