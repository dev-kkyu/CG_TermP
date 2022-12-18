#pragma once
#include "CBlock.h"

class CCloud : public CBlock
{
private:
	glm::vec3 Color;

public:
	CCloud(glm::vec3 Position);
	virtual ~CCloud();			//�Ҹ��ڵ� ����� ���ִ°� ����

	virtual void Initialize() override;		//������ �� �� ��
	virtual void Update() override;			//Ÿ�̸ӿ��� �� ��
	virtual void FixedUpdate() override;		//�浹ó�� ��
	virtual void Render() override;			//��ο�
	virtual void Release() override;			//�Ҹ�� �� �� ��
};

