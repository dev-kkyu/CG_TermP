#pragma once
#include "CAnimal.h"

class CSheep : public CAnimal
{
private:
	bool hairless;

public:
	CSheep(glm::vec3 Position);
	virtual ~CSheep();			//�Ҹ��ڵ� ����� ���ִ°� ����

	virtual void Release() override;			//�Ҹ�� �� �� ��
	
	virtual void Render() override;		// �� ���� ��, �� ���� ��
};

