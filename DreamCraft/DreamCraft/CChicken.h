#pragma once
#include "CAnimal.h"

class CChicken : public CAnimal
{
private:

public:
	CChicken(glm::vec3 Position);
	virtual ~CChicken();			//�Ҹ��ڵ� ����� ���ִ°� ����

	virtual void Release() override;			//�Ҹ�� �� �� ��
};

