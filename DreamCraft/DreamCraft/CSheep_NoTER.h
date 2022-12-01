#pragma once
#include "CAnimal.h"

class CSheep_NoTER : public CAnimal
{
private:
	bool hairless;

public:
	CSheep_NoTER(glm::vec3 Position);
	virtual ~CSheep_NoTER();			//소멸자도 버츄얼 해주는게 좋음

	virtual void Release() override;			//소멸될 때 할 일

	virtual void Render() override;		// 털 깎은 양, 안 깎은 양
};
