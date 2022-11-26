#pragma once
#include "Header.h"
#include "CBase.h"
#include "CPlayer.h"
#include <set>

class CBlock;

class CWorld
{
	set<CBlock*> Blocks;

	CPlayer Player;
	glm::vec3 PlayerPos;

public:
	CWorld();

	void Camera(int personView);

	void Initialize();		//������ �� �� ��
	void Update();			//Ÿ�̸ӿ��� �� ��
	void FixedUpdate();		//�浹ó�� ��
	void Render();			//��ο�
	void Release();			//�Ҹ�� �� �� ��
	
};

