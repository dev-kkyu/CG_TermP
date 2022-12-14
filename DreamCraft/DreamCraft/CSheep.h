#pragma once
#include "CAnimal.h"

#include "AnimalHead.h"
#include "AnimalBody.h"
#include "AnimalLeg.h"

class CSheep : public CAnimal
{
private:
	AnimalHead Head;
	AnimalBody Body;
	AnimalLeg Leg1;
	AnimalLeg Leg2;
	AnimalLeg Leg3;
	AnimalLeg Leg4;

	bool hairless;		// �� ���� ������ �ٲٴ� ����, ���� �����ϴ� ����
public:
	CSheep(glm::vec3 Position, Form animalForm, int animalType);
	virtual ~CSheep();			//�Ҹ��ڵ� ����� ���ִ°� ����

	virtual void Release() override;			//�Ҹ�� �� �� ��
	
	virtual void Update() override;
	virtual void Render() override;		// �� ���� ��, �� ���� ��
};

