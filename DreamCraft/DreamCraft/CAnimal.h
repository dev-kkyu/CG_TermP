#pragma once
#include "CGameObject.h"

class CAnimal : public CGameObject
{
protected:
	glm::vec3 Color;

	glm::vec3 origin_Position;		// ù ���� ��ġ

	float animalView, travel;		// ������ �ü�(����), �� �������� �� �� �ִ� �ִ� �Ÿ�(������ �ٲ�� �޶���)
	float before_location_x, before_location_z;		// ���� ��ȯ ���� ��ġ

public:
	CAnimal(glm::vec3 Position);
	virtual ~CAnimal() = 0;			// �Ҹ��ڵ� ����� ���ִ°� ����

	virtual void Initialize() override;		// ������ �� �� ��
	virtual void Update() override;			// Ÿ�̸ӿ��� �� ��
	virtual void FixedUpdate() = 0;		// �浹ó�� ��
	virtual void Render() override;			// ��ο�
	virtual void Release() = 0;			// �Ҹ�� �� �� ��


	virtual float getLeft() override;		// ������Ʈ���� �浹üũ�� �� �ʿ䰡 ���� �� �ִ�.
	virtual float getRight() override;		// ���� Position�� ���� �߾��̴�.
	virtual float getBehind() override;
	virtual float getFront() override;
	virtual float getBottom() override;
	virtual float getTop() override;
};

