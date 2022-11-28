#pragma once
#include "CGameObject.h"

class CAnimal : public CGameObject
{
protected:
	glm::vec3 Color;

	glm::vec3 origin_Position;

	float cowView, cow_move_x, cow_move_z, travel;
	float before_location_x, before_location_z;

public:
	CAnimal(glm::vec3 Position);
	virtual ~CAnimal() = 0;			//소멸자도 버츄얼 해주는게 좋음

	virtual void Initialize() override;		//생성될 때 할 일
	virtual void Update() override;			//타이머에서 할 일
	virtual void FixedUpdate() = 0;		//충돌처리 등
	virtual void Render() override;			//드로우
	virtual void Release() = 0;			//소멸될 때 할 일


	virtual float getLeft() override;		//오브젝트들은 충돌체크를 할 필요가 있을 때 있다.
	virtual float getRight() override;		//블럭의 Position은 윗면 중앙이다.
	virtual float getBehind() override;
	virtual float getFront() override;
	virtual float getBottom() override;
	virtual float getTop() override;
};

