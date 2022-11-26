#pragma once
#include "CGameObject.h"

class CPlayer : public CGameObject
{
private:

public:
	CPlayer(glm::vec3 Position);
	virtual ~CPlayer();			//소멸자도 버츄얼 해주는게 좋음
	
	void Update(glm::vec3 Position);

	virtual void Initialize() override;		//생성될 때 할 일
	virtual void Update() override;			//타이머에서 할 일
	virtual void FixedUpdate() override;		//충돌처리 등
	virtual void Render() override;			//드로우
	virtual void Release() override;			//소멸될 때 할 일

	virtual float getLeft() override;		//오브젝트들은 충돌체크를 할 필요가 있을 때 있다.
	virtual float getRight() override;		//Player의 Position은 아래 중앙이다.
	virtual float getBehind() override;
	virtual float getFront() override;
	virtual float getBottom() override;
	virtual float getTop() override;
};

