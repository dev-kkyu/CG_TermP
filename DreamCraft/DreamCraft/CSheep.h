#pragma once
#include "CAnimal.h"

class CSheep : public CAnimal
{
private:

public:
	CSheep(glm::vec3 Position);
	virtual ~CSheep();			//�Ҹ��ڵ� ����� ���ִ°� ����

	virtual void Release() override;			//�Ҹ�� �� �� ��
};

