#pragma once
#include "CSheep.h"

class CSheep_NoTER : public CSheep
{
private:
	bool hairless;

public:
	CSheep_NoTER(glm::vec3 Position, Form animalForm);
	virtual ~CSheep_NoTER();			//�Ҹ��ڵ� ����� ���ִ°� ����

	virtual void Release() override;			//�Ҹ�� �� �� ��

	virtual void Render() override;		// �� ���� ��, �� ���� ��
};
