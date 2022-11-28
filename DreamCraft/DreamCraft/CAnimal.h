#pragma once
#include "CGameObject.h"

class CAnimal : public CGameObject
{
protected:
	glm::vec3 Color;

	glm::vec3 origin_Position;

	float cowView, cow_move_x, cow_move_z, travel;
	float before_location_x, before_location_z;

public:
	CAnimal(glm::vec3 Position);
	virtual ~CAnimal() = 0;			//�Ҹ��ڵ� ����� ���ִ°� ����

	virtual void Initialize() override;		//������ �� �� ��
	virtual void Update() override;			//Ÿ�̸ӿ��� �� ��
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

