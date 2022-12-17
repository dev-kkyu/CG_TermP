#include "CAnimal.h"
#include "CWorld.h"

extern CWorld World;

CAnimal::CAnimal(glm::vec3 Position, Form animalForm, int animalType)
	: CGameObject{ Position }, animalForm{ animalForm }, animalType{ animalType }, dre{ rd() }
{
	Initialize();
}

CAnimal::~CAnimal()
{
}

void CAnimal::be_Attacked(int Weapon)
{
	switch (Weapon) {
	case 맨손:
		--Hp;
		Attacked = Attacked_Motion = true;
		hold_Scissors = false;
		cout << "맨손" << endl;
		break;
	case 칼:
		Hp -= 2;
		Attacked = Attacked_Motion = true;
		hold_Scissors = false;
		cout << "칼" << endl;
		break;
	case 가위:
		Attacked_Motion = hold_Scissors = true;
		cout << "가위" << endl;
		break;
	case 곡괭이:
		--Hp;
		Attacked = Attacked_Motion = true;
		hold_Scissors = false;
		cout << "곡괭이" << endl;
		break;
	case 최강무기:
		Hp -= 100;
		Attacked = Attacked_Motion = true;
		hold_Scissors = false;
		cout << "최강무기" << endl;  // 최강무기는 최강이라서 고기가 드랍안된다!
		break;
	}
}

void CAnimal::Initialize()
{
	Hp = 10;

	uniform_int_distribution<int> dict_urd{ 1, 8 };
	uniform_real_distribution<float> travel_urd{ 5.f, 15.f };

	animal_Direction = dict_urd(dre) * 45.f;			// 이동 방향 1-8까지 n*45도 만큼 회전
	Travel = travel_urd(dre);

	origin_Position = Position;
	before_Position = Position;

	float_Position = Position;

	if (animalForm == Form::item) {					// 아이템 생성시 모델변환 적용시킴
		glm::mat4 Rotate;
		glm::mat4 Trans;
		glm::mat4 Scale;

		Trans = glm::translate(Unit, glm::vec3(0.f, -0.5f, 0.f));

		if (animalForm == Form::creature)
			Scale = glm::scale(Unit, glm::vec3(1.f, 1.f, 2.f));
		else if (animalForm == Form::item)
			Scale = glm::scale(Unit, glm::vec3(0.5, 0.5, 0.5));

		Rotate = glm::rotate(glm::mat4(1.0f), glm::radians(animal_Direction), glm::vec3(0.f, 1.f, 0.f));

		Change = glm::translate(Unit, float_Position) * Rotate * Scale * Trans;
	}
}

void CAnimal::FixedUpdate()
{
	uniform_int_distribution<int> dict_urd{ 1, 8 };
	uniform_real_distribution<float> travel_urd{ 5.f, 15.f };

	float speed = 0.005f;

	if (pow(before_Position.x - Position.x, 2)
		+ pow(before_Position.z - Position.z, 2) >= pow(Travel, 2)) {  // 한 방향으로 travel만큼 이동했으면

		animal_Direction = dict_urd(dre) * 45.f;
		Travel = travel_urd(dre);
		before_Position = Position;
	}
	else if (pow(origin_Position.x - Position.x + speed * 2, 2)   // 다다음 이동이 경계에 걸리면
		+ pow(origin_Position.z - Position.z + speed * 2, 2) >= 20 * 20) {
		if (animal_Direction / 45 <= 4)
			animal_Direction = animal_Direction + 45 * 4;
		else
			animal_Direction = animal_Direction - 45 * 4;

		Travel = travel_urd(dre);
		before_Position = Position;
	}

	if (animalForm == Form::creature) {
		if (!Attacked_Motion) {
			switch ((int)(animal_Direction / 45))
			{
			case 1:
				float_Position.x += speed;
				float_Position.z += speed;
				break;
			case 2:
				float_Position.x += speed;

				break;
			case 3:
				float_Position.x += speed;
				float_Position.z -= speed;
				break;
			case 4:
				float_Position.z -= speed;
				break;
			case 5:
				float_Position.x -= speed;
				float_Position.z -= speed;
				break;
			case 6:
				float_Position.x -= speed;
				break;
			case 7:
				float_Position.x -= speed;
				float_Position.z += speed;
				break;
			case 8:
				float_Position.z += speed;
				break;
			}
		}
		else {

			float_Position.x += glm::sin(glm::radians(MouseAngle.first)) * 0.75f;
			float_Position.z -= glm::cos(glm::radians(MouseAngle.first)) * 0.75f;
			Attacked_Motion = false;
		}
	}

	if (animalForm == Form::creature) {
		CBase temp{ glm::vec3(round(float_Position.x), round(float_Position.y), round(float_Position.z)) };
		if (World.Objects.find(&temp) == World.Objects.end()) {

			World.Objects.erase(this);

			Position.x = round(float_Position.x);
			Position.y = round(float_Position.y);
			Position.z = round(float_Position.z);

			World.Objects.insert(this);
		}
	}
}

float CAnimal::getLeft()
{
	return Position.x - 0.5f;
}

float CAnimal::getRight()
{
	return Position.x + 0.5f;
}

float CAnimal::getBehind()
{
	return Position.z - 1.f;
}

float CAnimal::getFront()
{
	return Position.z + 1.f;
}

float CAnimal::getBottom()
{
	return Position.y - 1.f;
}

float CAnimal::getTop()
{
	return Position.y;
}
