#pragma once
#include "CAnimal.h"

class CCow : public CAnimal
{
private:

public:
	CCow(glm::vec3 Position, Form animalForm);
	virtual ~CCow();			//�Ҹ��ڵ� ����� ���ִ°� ����

	virtual void Release() override;			//�Ҹ�� �� �� ��

	virtual void Render() override;		// �� ���� ��, �� ���� ��
};