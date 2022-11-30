#pragma once
#include "CAnimal.h"

class CPig : public CAnimal
{
private:

public:
	CPig(glm::vec3 Position);
	virtual ~CPig();			//소멸자도 버츄얼 해주는게 좋음

	virtual void Release() override;			//소멸될 때 할 일
};