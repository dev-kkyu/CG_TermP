#pragma once
#include "CBlock.h"

class CRice : public CBlock
{
private:

public:
	CRice(glm::vec3 Position);
	virtual ~CRice();			//�Ҹ��ڵ� ����� ���ִ°� ����

	virtual void Initialize() override;		//������ �� �� ��
	virtual void Update() override;			//Ÿ�̸ӿ��� �� ��
	virtual void FixedUpdate() override;		//�浹ó�� ��
	virtual void Render() override;			//��ο�
	virtual void Release() override;			//�Ҹ�� �� �� ��
};

