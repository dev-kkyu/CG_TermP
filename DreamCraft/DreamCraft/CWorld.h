#pragma once
#include "Header.h"
#include "CBase.h"
#include "CPlayer.h"
#include <set>

class CWorld
{
	set<CBlock*, CBlockCmp> Blocks;

	CPlayer Player;
	glm::vec3 PlayerPos;

	glm::vec3 cameraPos;
	glm::vec3 cameraDirection;

	bool isUp, isDown, isLeft, isRight;
	int isJump;
	int personView;


public:
	CWorld();

	void Keyboard(unsigned char key, int state);
	void SpecialKeyboard(int key, int state);
	void Mouse(int button, int state);

	void Camera(int personView);

	set<CBlock*, CBlockCmp>::iterator getObject();		//set���� ���� Ŭ���� ������Ʈ�� iterator�� �޾ƿ´�.
	void newBlock();									//���� Ŭ���� ������Ʈ�� ���ʿ� ������ �����Ѵ�.

	void Initialize();		//������ �� �� ��
	void Update();			//Ÿ�̸ӿ��� �� ��
	void FixedUpdate();		//�浹ó�� ��
	void Render();			//��ο�
	void Release();			//�Ҹ�� �� �� ��
	
};
