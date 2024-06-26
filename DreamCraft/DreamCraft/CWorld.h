﻿#pragma once
#include "Header.h"
#include "CPlayer.h"
#include "CSound.h"

#include <set>

struct Item {
	int Chicken;
	int Pig;
	int Rice;
	int Cow;
	int Sheep;
	int SheepTer;

	void show() {
		cout << "닭 : " << Chicken << ", 소 : " << Cow << endl;
		cout << "양 : " << Sheep << ", 돼지 : " << Pig << endl;
		cout << "양털아이템 : " << SheepTer << endl;
		cout << "벼 : " << Rice << endl;
		cout << endl;
	}

	bool isComplete() {
		if (Chicken >= 5 &&
			Cow >= 5 &&
			Pig >= 5 &&
			Rice >= 5 &&
			Sheep >= 5 &&
			SheepTer >= 5
			) return true;
		return false;
	}
};

class CWorld
{
private:
	bool gameStart;
	bool gameEnd;

	GLUquadricObj* qobj;			// 실린더 생성하자

	CSound Sound;

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

	Item itemCount{};

public:
	set<CGameObject*, CGameObjectCmp> Objects;
	set<CGameObject*, CGameObjectCmp> died_Objects;
	set<CGameObject*, CGameObjectCmp> mined_Objects;

public:
	CWorld();

	void Keyboard(unsigned char key, int state);
	void SpecialKeyboard(int key, int state);
	void Mouse(int button, int state);

	void Camera();

	void Gravity();
	void Move();

	set<CGameObject*, CGameObjectCmp>::iterator getObject();		//set에서 내가 클릭한 오브젝트의 iterator를 받아온다.
	void addNewObject(const int& ObjectType);									//내가 클릭한 오브젝트의 앞쪽에 오브젝트를 생성한다.
	void insertObject(const int& ObjectType, const glm::vec3& ObjectPos);

	void Initialize();		//생성될 때 할 일
	void Update();			//타이머에서 할 일
	void FixedUpdate();		//충돌처리 등
	void Render();			//드로우
	void Release();			//소멸될 때 할 일

	void viewInventory();
	void GameClearAnimation(int time);

	int getpersonView();

	void MakeTree(glm::vec3 position);
	void MakeTree2(glm::vec3 position);

	void MakeCloud(glm::vec3 position);
	void MakeCloud2(glm::vec3 position);
	void MakeCloud3(glm::vec3 position);
	void MakeCloud4(glm::vec3 position);
	
	void MakeWorld();


};
