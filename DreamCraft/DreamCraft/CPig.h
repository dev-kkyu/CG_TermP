#pragma once
#include "CAnimal.h"

class CPig : public CAnimal
{
private:

public:
	CPig(glm::vec3 Position);
	virtual ~CPig();			//�Ҹ��ڵ� ����� ���ִ°� ����

	virtual void Release() override;			//�Ҹ�� �� �� ��
};