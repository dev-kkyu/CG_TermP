#include "CPlayer.h"

CPlayer::CPlayer(glm::vec3 Position) : CGameObject{ Position },
	head(Head(glm::vec3(191. / 255, 160. / 255, 237. / 255))),
	nose(Nose(glm::vec3(1.f, 108. / 255, 108. / 255))),
	body(Body(glm::vec3(243. / 255, 1, 72. / 255))),
	armL(Arm(glm::vec3(178. / 255, 204. / 255, 1.f), -1)),
	armR(Arm(glm::vec3(1.f, 193. / 255, 158. / 255), 1)),
	legL(Leg(glm::vec3(1.f, 193. / 255, 158. / 255), -1)),
	legR(Leg(glm::vec3(178. / 255, 204. / 255, 1.f), 1)),
	
	Direction(0.f)
{
	Initialize();
}

CPlayer::~CPlayer()
{
}

void CPlayer::Update(glm::vec3 Position)
{
	this->Position = Position;

	nose.setPos(Position);
	head.setPos(Position);
	armL.setPos(Position);
	armR.setPos(Position);
	body.setPos(Position);
	legL.setPos(Position);
	legR.setPos(Position);
}

void CPlayer::Initialize()
{
	Update();
}

void CPlayer::Update()
{
	Direction = -MouseAngle.first;

	nose.setDirection(Direction);
	head.setDirection(Direction);
	armL.setDirection(Direction);
	armR.setDirection(Direction);
	body.setDirection(Direction);
	legL.setDirection(Direction);
	legR.setDirection(Direction);
}

void CPlayer::FixedUpdate()
{
}

void CPlayer::Render()
{
	nose.Render();
	head.Render();
	armL.Render();
	armR.Render();
	body.Render();
	legL.Render();
	legR.Render();
}

void CPlayer::Release()
{
}

float CPlayer::getLeft()
{
	return Position.x - 0.5f;
}

float CPlayer::getRight()
{
	return Position.x + 0.5f;
}

float CPlayer::getBehind()
{
	return Position.z - 0.5f;
}

float CPlayer::getFront()
{
	return Position.z + 0.5f;
}

float CPlayer::getBottom()
{
	return Position.y - 2.f;
}

float CPlayer::getTop()
{
	return Position.y;
}
