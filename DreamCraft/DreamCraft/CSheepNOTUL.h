#pragma once
#include "CAnimal.h"

class CSheepNOTUL : public CAnimal
{
private:
	bool hairless = false, Wool = false;		// �� ���� ������ �ٲٴ� ����, ���� �����ϴ� ���� 
	glm::vec3 Wool_Position;	// ������ ���� ��ġ ����
public:
	CSheepNOTUL(glm::vec3 Position, Form animalForm);
	virtual ~CSheepNOTUL();			//�Ҹ��ڵ� ����� ���ִ°� ����

	virtual void Release() override;			//�Ҹ�� �� �� ��

	virtual void Render() override;		// �� ���� ��, �� ���� ��
};

