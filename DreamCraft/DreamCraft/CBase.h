#pragma once
#include "CBlock.h"

class CFragments;
class CBase : public CBlock
{
private:
	vector<CFragments*> myFragments;
public:
	CBase(glm::vec3 Position);
	virtual ~CBase();			//�Ҹ��ڵ� ����� ���ִ°� ����

	virtual void Initialize() override;		//������ �� �� ��
	virtual void Update() override;			//Ÿ�̸ӿ��� �� ��
	virtual void FixedUpdate() override;		//�浹ó�� ��
	virtual void Render() override;			//��ο�
	virtual void Release() override;			//�Ҹ�� �� �� ��

};

