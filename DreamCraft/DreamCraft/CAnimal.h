#pragma once
#include "CGameObject.h"

enum Form {
	creature,
	item
};

class CAnimal : public CGameObject
{
private:
	random_device rd;
	default_random_engine dre;

protected:
	glm::vec3 origin_Position;		// ù ���� ��ġ
	glm::vec3 before_Position;		// ���� ��ȯ ���� ��ġ

	glm::vec3 float_Position;		// �̵��ϰ� �ִ� ���� ��ġ
			// Position�� round, ceil �� x.0 ��

	float animal_Direction, Travel;		// ������ ����, �� �������� �� �� �ִ� �ִ� �Ÿ�(������ �ٲ�� �޶���)
	
	bool Attacked, Attacked_Motion, hold_Scissors;
	
public:
	const int animalType;
	const Form animalForm;

public:
	CAnimal(glm::vec3 Position, Form animalForm, int animalType);
	virtual ~CAnimal() = 0;			// �Ҹ��ڵ� ����� ���ִ°� ����

	virtual void be_Attacked(int Weapon);

	virtual void Initialize() override;		// ������ �� �� ��
	virtual void Update() = 0;			// Ÿ�̸ӿ��� �� ��
	virtual void FixedUpdate() override;		// �浹ó�� ��
	virtual void Render() = 0;			// ��ο�
	virtual void Release() = 0;			// �Ҹ�� �� �� ��

	virtual float getLeft() override;		// ������Ʈ���� �浹üũ�� �� �ʿ䰡 ���� �� �ִ�.
	virtual float getRight() override;		// ���� Position�� ���� �߾��̴�.
	virtual float getBehind() override;
	virtual float getFront() override;
	virtual float getBottom() override;
	virtual float getTop() override;
};

