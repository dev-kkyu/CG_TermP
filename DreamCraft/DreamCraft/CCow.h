#pragma once
#include "CAnimal.h"

class CCow : public CAnimal
{
private:
	glm::vec3 Color;

public:
	CCow(glm::vec3 Position);
	virtual ~CCow();			//�Ҹ��ڵ� ����� ���ִ°� ����

	virtual void FixedUpdate() override;		//�浹ó�� ��
	virtual void Release() override;			//�Ҹ�� �� �� ��
};

