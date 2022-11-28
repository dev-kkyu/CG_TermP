#pragma once
#include "Header.h"

class CGameObject
{
protected:
	const glm::mat4 Unit;				//�⺻��� �̸� ����� �����ô�.

	glm::vec3 Position;					//��� ��ü�� ��ġ�� ���´�.
	glm::mat4 Change;					//��� ��ü�� �𵨺�ȯ�� �Ѵ�.

public:
	CGameObject(glm::vec3 Position);
	virtual ~CGameObject() = 0;			//�Ҹ��ڵ� ����� ���ִ°� ����

	friend struct CGameObjectCmp;							//set�� �����ͷ� �� �� ����ϴ� ��

	void show();

	virtual void Initialize() = 0;		//������ �� �� ��
	virtual void Update() = 0;			//Ÿ�̸ӿ��� �� ��
	virtual void FixedUpdate() = 0;		//�浹ó�� ��
	virtual void Render() = 0;			//��ο�
	virtual void Release() = 0;			//�Ҹ�� �� �� ��


	virtual float getLeft() = 0;		//������Ʈ���� �浹üũ�� �� �ʿ䰡 ���� �� �ִ�.
	virtual float getRight() = 0;
	virtual float getBehind() = 0;
	virtual float getFront() = 0;
	virtual float getBottom() = 0;
	virtual float getTop() = 0;
};

struct CGameObjectCmp {
	bool operator () (const CGameObject* lhs, const CGameObject* rhs) const;
};