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

	// 중력용 변수들
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

	set<CGameObject*, CGameObjectCmp>::iterator getObject();		//set에서 내가 클릭한 오브젝트의 iterator를 받아온다.
	void addNewObject(int ObjectType);									//내가 클릭한 오브젝트의 앞쪽에 오브젝트를 생성한다.

	void Initialize();		//생성될 때 할 일
	void Update();			//타이머에서 할 일
	void FixedUpdate();		//충돌처리 등
	void Render();			//드로우
	void Release();			//소멸될 때 할 일
	int getpersonView();

	void MakeTree(glm::vec3 position);
	void MakeTree2(glm::vec3 position);
};
