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

	CGameObject* getObject();		//길이 4 안으로 받아온다.

	void Initialize();		//생성될 때 할 일
	void Update();			//타이머에서 할 일
	void FixedUpdate();		//충돌처리 등
	void Render();			//드로우
	void Release();			//소멸될 때 할 일
	
};

