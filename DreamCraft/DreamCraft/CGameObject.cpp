#include "CGameObject.h"

CGameObject::CGameObject(glm::vec3 Position) : Unit{ glm::mat4(1.f) }, Position{ Position }, Change{ glm::mat4(1.f) }
{
}

CGameObject::~CGameObject()
{
}
