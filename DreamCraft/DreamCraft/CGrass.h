#pragma once
#include "CBlock.h"

class CGrass : public CBlock
{
private:

public:
	CGrass(glm::vec3 Position);
	virtual ~CGrass();			//�Ҹ��ڵ� ����� ���ִ°� ����

	virtual void Initialize() override;		//������ �� �� ��
	virtual void Update() override;			//Ÿ�̸ӿ��� �� ��
	virtual void FixedUpdate() override;		//�浹ó�� ��
	virtual void Render() override;			//��ο�
	virtual void Release() override;			//�Ҹ�� �� �� ��
};

