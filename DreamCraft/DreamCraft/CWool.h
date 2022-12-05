#pragma once
#include "CBlock.h"
 
class CWool: public CBlock
{
private:

public:
	CWool(glm::vec3 Position);
	virtual ~CWool();			//소멸자도 버츄얼 해주는게 좋음

	virtual void Initialize() override;		//생성될 때 할 일
	virtual void Update() override;			//타이머에서 할 일
	virtual void FixedUpdate() override;		//충돌처리 등
	virtual void Render() override;			//드로우
	virtual void Release() override;			//소멸될 때 할 일
};

