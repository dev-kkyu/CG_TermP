#pragma once
#include "CAnimal.h"

class CCow : public CAnimal
{
private:
	glm::vec3 Color;

public:
	CCow(glm::vec3 Position);
	virtual ~CCow();			//�Ҹ��ڵ� ����� ���ִ°� ����

	virtual void Initialize() override;		//������ �� �� ��
	virtual void Update() override;			//Ÿ�̸ӿ��� �� ��
	virtual void FixedUpdate() override;		//�浹ó�� ��
	virtual void Render() override;			//��ο�
	virtual void Release() override;			//�Ҹ�� �� �� ��
};

