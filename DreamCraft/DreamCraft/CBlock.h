#pragma once
#include "CGameObject.h"

class CBlock : public CGameObject
{
protected:


public:
	CBlock(glm::vec3 Position);
	virtual ~CBlock() = 0;			//�Ҹ��ڵ� ����� ���ִ°� ����

	//bool operator<(const CBlock& other) const;		//�׳� set �� �� ����ϴ� ��
	friend struct CBlockCmp;							//set�� �����ͷ� �� �� ����ϴ� ��

	virtual void Initialize() override;		//������ �� �� ��
	virtual void Update() = 0;			//Ÿ�̸ӿ��� �� ��
	virtual void FixedUpdate() = 0;		//�浹ó�� ��
	virtual void Render() override;			//��ο�
	virtual void Release() = 0;			//�Ҹ�� �� �� ��


	virtual float getLeft() override;		//������Ʈ���� �浹üũ�� �� �ʿ䰡 ���� �� �ִ�.
	virtual float getRight() override;		//���� Position�� ���� �߾��̴�.
	virtual float getBehind() override;
	virtual float getFront() override;
	virtual float getBottom() override;
	virtual float getTop() override;

};

struct CBlockCmp {
	bool operator () (const CBlock* lhs, const CBlock* rhs) const;
};