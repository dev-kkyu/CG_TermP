#pragma once
#include "CAnimal.h"

class CSheepNOTUL : public CAnimal
{
private:
	bool hairless = false, Wool = false;		// 털 깎인 양으로 바꾸는 변수, 양털 생성하는 변수 
	glm::vec3 Wool_Position;	// 양털이 깎인 위치 저장
public:
	CSheepNOTUL(glm::vec3 Position, Form animalForm);
	virtual ~CSheepNOTUL();			//소멸자도 버츄얼 해주는게 좋음

	virtual void Release() override;			//소멸될 때 할 일

	virtual void Render() override;		// 털 깎은 양, 안 깎은 양
};

