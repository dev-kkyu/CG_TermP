#pragma once
#include "CAnimal.h"

class CSheep : public CAnimal
{
private:

public:
	CSheep(glm::vec3 Position);
	virtual ~CSheep();			//소멸자도 버츄얼 해주는게 좋음

	virtual void Release() override;			//소멸될 때 할 일
};

