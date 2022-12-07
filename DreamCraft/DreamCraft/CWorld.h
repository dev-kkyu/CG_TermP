#pragma once
#include "Header.h"
#include "CBase.h"
#include "CGrass.h"
#include "CPlayer.h"
#include "CCow.h"
#include "CChicken.h"
#include "CPig.h"
#include "CSheep.h"
#include "CLeaves.h"
#include "CTreeTrunk.h"
#include "CSheepNOTUL.h"
#include "CRice.h"
#include "CWool.h"
#include "CBirchTrunk.h"

#include <set>

class CWorld
{
private:
	CPlayer Player;
	glm::vec3 PlayerPos;

	glm::vec3 cameraPos;
	glm::vec3 cameraDirection;

	bool mouseL_On;

	bool isUp, isDown, isLeft, isRight;
	int isJump;

	// �߷¿� ������
	int VELOCITY;
	const int first_VEL;
	const int MASS;

	int personView;

	int planToCreateObj;

public:
	set<CGameObject*, CGameObjectCmp> Objects;

public:
	CWorld();

	void Keyboard(unsigned char key, int state);
	void SpecialKeyboard(int key, int state);
	void Mouse(int button, int state);

	void Camera();

	void Gravity();
	void Move();

	set<CGameObject*, CGameObjectCmp>::iterator getObject();		//set���� ���� Ŭ���� ������Ʈ�� iterator�� �޾ƿ´�.
	void addNewObject(int ObjectType);									//���� Ŭ���� ������Ʈ�� ���ʿ� ������Ʈ�� �����Ѵ�.

	void Initialize();		//������ �� �� ��
	void Update();			//Ÿ�̸ӿ��� �� ��
	void FixedUpdate();		//�浹ó�� ��
	void Render();			//��ο�
	void Release();			//�Ҹ�� �� �� ��
	int getpersonView();

	void MakeTree(glm::vec3 position);
	void MakeTree2(glm::vec3 position);
};
