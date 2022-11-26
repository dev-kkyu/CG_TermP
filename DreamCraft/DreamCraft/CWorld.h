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

	void Initialize();		//생성될 때 할 일
	void Update();			//타이머에서 할 일
	void FixedUpdate();		//충돌처리 등
	void Render();			//드로우
	void Release();			//소멸될 때 할 일
	
};

