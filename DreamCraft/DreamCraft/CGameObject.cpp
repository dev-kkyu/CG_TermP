#include "CGameObject.h"

CGameObject::CGameObject(glm::vec3 Position) : Unit{ glm::mat4(1.f) }, Position{ Position }, Change{ glm::mat4(1.f) }
{
}

CGameObject::~CGameObject()
{
}

void CGameObject::show()
{
	cout << Position.x << " " << Position.y << ' ' << Position.z << endl;
}

bool CGameObject::isDead()
{
	return Hp <= 0;
}

bool CGameObjectCmp::operator()(const CGameObject* lhs, const CGameObject* rhs) const
{
	if (lhs->Position.x != rhs->Position.x)
		return lhs->Position.x < rhs->Position.x;
	if (lhs->Position.y != rhs->Position.y)
		return lhs->Position.y < rhs->Position.y;
	return lhs->Position.z < rhs->Position.z;
}
