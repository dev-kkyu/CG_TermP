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

	bool hairless/*, Wool*/;		// 털 깎인 양으로 바꾸는 변수, 양털 생성하는 변수 
	//glm::vec3 Wool_Position;	// 양털이 깎인 위치 저장
public:
	CSheep(glm::vec3 Position, Form animalForm, int animalType);
	virtual ~CSheep();			//소멸자도 버츄얼 해주는게 좋음

	virtual void Release() override;			//소멸될 때 할 일
	
	virtual void Update() override;
	virtual void Render() override;		// 털 깎은 양, 안 깎은 양
};

