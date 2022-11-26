#pragma once
#include "CGameObject.h"

class CPlayer : public CGameObject
{
private:

public:
	CPlayer(glm::vec3 Position);
	virtual ~CPlayer();			//�Ҹ��ڵ� ����� ���ִ°� ����
	
	void Update(glm::vec3 Position);

	virtual void Initialize() override;		//������ �� �� ��
	virtual void Update() override;			//Ÿ�̸ӿ��� �� ��
	virtual void FixedUpdate() override;		//�浹ó�� ��
	virtual void Render() override;			//��ο�
	virtual void Release() override;			//�Ҹ�� �� �� ��

	virtual float getLeft() override;		//������Ʈ���� �浹üũ�� �� �ʿ䰡 ���� �� �ִ�.
	virtual float getRight() override;		//Player�� Position�� �Ʒ� �߾��̴�.
	virtual float getBehind() override;
	virtual float getFront() override;
	virtual float getBottom() override;
	virtual float getTop() override;
};

