#pragma once
#include "CAnimal.h"

class CSheep : public CAnimal
{
private:
	bool hairless = false, Wool=false;		// �� ���� ������ �ٲٴ� ����, ���� �����ϴ� ���� 
	glm::vec3 Wool_Position;	// ������ ���� ��ġ ����
public:
	CSheep(glm::vec3 Position, Form animalForm);
	virtual ~CSheep();			//�Ҹ��ڵ� ����� ���ִ°� ����

	virtual void Release() override;			//�Ҹ�� �� �� ��
	
	virtual void Render() override;		// �� ���� ��, �� ���� ��
};

