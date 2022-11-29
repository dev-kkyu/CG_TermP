#pragma once
#include "Header.h"
#include "CBase.h"
#include "CPlayer.h"
#include "CCow.h"
#include <set>

class CWorld
{
private:
	CPlayer Player;
	glm::vec3 PlayerPos;

	glm::vec3 cameraPos;
	glm::vec3 cameraDirection;

	bool isUp, isDown, isLeft, isRight;
	int isJump;
	int personView;

public:
	set<CGameObject*, CGameObjectCmp> Objects;

public:
	CWorld();

	void Keyboard(unsigned char key, int state);
	void SpecialKeyboard(int key, int state);
	void Mouse(int button, int state);

	void Camera();

	set<CGameObject*, CGameObjectCmp>::iterator getObject();		//set에서 내가 클릭한 오브젝트의 iterator를 받아온다.
	void newBlock();									//내가 클릭한 오브젝트의 앞쪽에 블럭을 생성한다.

	void Initialize();		//생성될 때 할 일
	void Update();			//타이머에서 할 일
	void FixedUpdate();		//충돌처리 등
	void Render();			//드로우
	void Release();			//소멸될 때 할 일
	
};

