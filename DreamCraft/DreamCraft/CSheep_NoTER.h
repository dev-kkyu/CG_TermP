#pragma once
#include "CAnimal.h"

class CSheep_NoTER : public CAnimal
{
private:
	bool hairless;

public:
	CSheep_NoTER(glm::vec3 Position);
	virtual ~CSheep_NoTER();			//�Ҹ��ڵ� ����� ���ִ°� ����

	virtual void Release() override;			//�Ҹ�� �� �� ��

	virtual void Render() override;		// �� ���� ��, �� ���� ��
};
