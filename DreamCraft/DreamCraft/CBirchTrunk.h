#pragma once
#include "CBlock.h"

class CBirchTrunk : public CBlock
{
private:

public:
	CBirchTrunk(glm::vec3 Position);
	virtual ~CBirchTrunk();			//�Ҹ��ڵ� ����� ���ִ°� ����

	virtual void Initialize() override;		//������ �� �� ��
	virtual void Update() override;			//Ÿ�̸ӿ��� �� ��
	virtual void FixedUpdate() override;		//�浹ó�� ��
	virtual void Render() override;			//��ο�
	virtual void Release() override;			//�Ҹ�� �� �� ��
};

