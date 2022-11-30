#pragma once
#include "CGameObject.h"

#include "Head.h"
#include "Nose.h"
#include "Body.h"
#include "Arm.h"
#include "Leg.h"
#include "Weapon.h"

class CPlayer : public CGameObject
{
private:
	Head head;
	Nose nose;
	Body body;
	Arm armL;
	Arm armR;
	Leg legL;
	Leg legR;
	Weapon weapon;

	float Direction;

	int Weapon_Name;

public:
	CPlayer(glm::vec3 Position);
	virtual ~CPlayer();			//�Ҹ��ڵ� ����� ���ִ°� ����
	
	void Update(glm::vec3 Position);

	void setWeapon(int Weapon);
	int getWeapon();

	virtual void be_Attacked(int Weapon);

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

