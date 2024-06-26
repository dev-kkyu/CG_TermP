#include "CPlayer.h"
#include "CWorld.h"

extern CWorld World;

CPlayer::CPlayer(glm::vec3 Position) : CGameObject{ Position },
	head(Head(glm::vec3(191. / 255, 160. / 255, 237. / 255))),
	nose(Nose(glm::vec3(1.f, 108. / 255, 108. / 255))),
	body(Body(glm::vec3(243. / 255, 1, 72. / 255))),
	armL(Arm(glm::vec3(178. / 255, 204. / 255, 1.f), -1)),
	armR(Arm(glm::vec3(1.f, 193. / 255, 158. / 255), 1)),
	legL(Leg(glm::vec3(1.f, 193. / 255, 158. / 255), -1)),
	legR(Leg(glm::vec3(178. / 255, 204. / 255, 1.f), 1)),
	weapon(Weapon(1)),
	
	Direction(0.f),

	Weapon_Name(맨손)
{
	Initialize();
}

CPlayer::~CPlayer()
{
}

void CPlayer::Update(glm::vec3 Position)
{
	this->Position = Position;
	this->Direction = -MouseAngle.first;

	nose.setPos(Position, Direction);
	head.setPos(Position, Direction);
	armL.setPos(Position, Direction);
	armR.setPos(Position, Direction);
	body.setPos(Position, Direction);
	legL.setPos(Position, Direction);
	legR.setPos(Position, Direction);
	weapon.setPos(Position, Direction);


	if (getWeapon() == 맨손)
		weapon.change(glm::vec3(0, 0, 0));

	else if (getWeapon() == 칼)
		weapon.change(glm::vec3(1, 0, 1));

	else if (getWeapon() == 가위)
		weapon.change(glm::vec3(1, 1, 0));

	else if (getWeapon() == 곡괭이)
		weapon.change(glm::vec3(0, 126. / 255, 0));

	else if (getWeapon() == 최강무기)
		weapon.change(glm::vec3(0, 1, 1));
}

void CPlayer::setWeapon(int Weapon)
{
	this->Weapon_Name = Weapon;
}

int CPlayer::getWeapon()
{
	return Weapon_Name;
}

void CPlayer::be_Attacked(int Weapon)
{
	//나중에 해주자.
}

void CPlayer::Initialize()
{
	Hp = 10;
	Update();
}

void CPlayer::Update()
{
	armL.FixedUpdate();
	armR.FixedUpdate();
	legL.FixedUpdate();
	legR.FixedUpdate();
	weapon.FixedUpdate();
}

void CPlayer::FixedUpdate()
{
}

void CPlayer::Render()
{
	if (World.getpersonView() == 3) {

		nose.Render();
		head.Render();
		armL.Render();
		armR.Render();
		body.Render();
		legL.Render();
		legR.Render();

	}

	if (getWeapon() != 맨손) {

		weapon.Render();
	}
}

void CPlayer::Release()
{
}

float CPlayer::getLeft()
{
	return Position.x - 0.25f;
}

float CPlayer::getRight()
{
	return Position.x + 0.25f;
}

float CPlayer::getBehind()
{
	return Position.z - 0.25f;
}

float CPlayer::getFront()
{
	return Position.z + 0.25f;
}

float CPlayer::getBottom()
{
	return Position.y - 2.f;
}

float CPlayer::getTop()
{
	return Position.y;
}
