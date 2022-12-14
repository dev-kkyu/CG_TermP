#include "CAnimalParts.h"

CAnimalParts::CAnimalParts(glm::vec3 Position, int animalType)
	: Unit{ glm::mat4(1.f) }, Change{ glm::mat4(1.f) }, animalType{ animalType }, Position{ Position }, Direction{ 0.f }
{
}

CAnimalParts::~CAnimalParts()
{
}

void CAnimalParts::setPos(glm::vec3 Position, float Direction)
{
	this->Position = Position;
	this->Direction = Direction;
}

void CAnimalParts::setType(int animalType)
{
	this->animalType = animalType;
}
