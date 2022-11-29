#pragma once
#include "CGameObject.h"

class CAnimal : public CGameObject
{
protected:
	glm::vec3 Color;

	glm::vec3 origin_Position;		// 첫 스폰 위치
	glm::vec3 before_Position;		// 방향 전환 직전 위치

	glm::vec3 float_Position;		// 이동하고 있는 현재 위치
			// Position은 round, ceil 된 x.0 값

	float animal_Direction, Travel;		// 동물의 방향, 한 방향으로 갈 수 있는 최대 거리(방향이 바뀌면 달라짐)
	
public:
	CAnimal(glm::vec3 Position);
	virtual ~CAnimal() = 0;			// 소멸자도 버츄얼 해주는게 좋음

	virtual void Initialize() override;		// 생성될 때 할 일
	virtual void Update() override;			// 타이머에서 할 일
	virtual void FixedUpdate() override;		// 충돌처리 등
	virtual void Render() override;			// 드로우
	virtual void Release() = 0;			// 소멸될 때 할 일


	virtual float getLeft() override;		// 오브젝트들은 충돌체크를 할 필요가 있을 때 있다.
	virtual float getRight() override;		// 블럭의 Position은 윗면 중앙이다.
	virtual float getBehind() override;
	virtual float getFront() override;
	virtual float getBottom() override;
	virtual float getTop() override;
};

