#pragma once
#include "CAnimal.h"

class CCow : public CAnimal
{
private:
	glm::vec3 Color;

public:
	CCow(glm::vec3 Position);
	virtual ~CCow();			//소멸자도 버츄얼 해주는게 좋음

	virtual void FixedUpdate() override;		//충돌처리 등
	virtual void Release() override;			//소멸될 때 할 일
};

