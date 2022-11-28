#pragma once
#include "Header.h"

class CGameObject
{
protected:
	const glm::mat4 Unit;				//기본행렬 미리 만들어 놓읍시다.

	glm::vec3 Position;					//모든 객체는 위치를 갖는다.
	glm::mat4 Change;					//모든 객체는 모델변환을 한다.

public:
	CGameObject(glm::vec3 Position);
	virtual ~CGameObject() = 0;			//소멸자도 버츄얼 해주는게 좋음

	friend struct CGameObjectCmp;							//set을 포인터로 쓸 때 사용하는 것

	void show();

	virtual void Initialize() = 0;		//생성될 때 할 일
	virtual void Update() = 0;			//타이머에서 할 일
	virtual void FixedUpdate() = 0;		//충돌처리 등
	virtual void Render() = 0;			//드로우
	virtual void Release() = 0;			//소멸될 때 할 일


	virtual float getLeft() = 0;		//오브젝트들은 충돌체크를 할 필요가 있을 때 있다.
	virtual float getRight() = 0;
	virtual float getBehind() = 0;
	virtual float getFront() = 0;
	virtual float getBottom() = 0;
	virtual float getTop() = 0;
};

struct CGameObjectCmp {
	bool operator () (const CGameObject* lhs, const CGameObject* rhs) const;
};