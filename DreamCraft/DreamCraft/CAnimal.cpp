#include "CAnimal.h"

#include "CWorld.h"
extern CWorld World;

random_device rd;
default_random_engine dre(rd());
uniform_int_distribution<int> dict_urd{ 1, 8 };
uniform_real_distribution<float> travel_urd{ 5.f, 15.f };

CAnimal::CAnimal(glm::vec3 Position) : CGameObject{ Position }
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
		Attacked = Attacked_Motion = hold_Scissors = true;
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

	if (0 < Hp && Hp <= 5)
		Hp = 5;
}

void CAnimal::Initialize()
{
	Hp = 15;

	animal_Direction = dict_urd(dre) * 45.f;			// 이동 방향 1-8까지 n*45도 만큼 회전
	Travel = travel_urd(dre);

	origin_Position = Position;
	before_Position = Position;

	float_Position = Position;

	uniform_real_distribution<float> urd{ 0.f, 1.f };

	Color = glm::vec3{ urd(dre),urd(dre), urd(dre) };
	origin_Color = Color;

	Update();
}

void CAnimal::Update()
{
	FixedUpdate();

	//----- 변환
	glm::mat4 Rotate;
	glm::mat4 Trans;
	glm::mat4 Scale;

	Trans = glm::translate(Unit, glm::vec3(0.f, -0.5f, 0.f));

	if (Hp > 5)
		Scale = glm::scale(Unit, glm::vec3(1.f, 1.f, 2.f));
	else
		Scale = glm::scale(Unit, glm::vec3(0.5,0.5,0.5));

	Rotate = glm::rotate(glm::mat4(1.0f), glm::radians(animal_Direction), glm::vec3(0.f, 1.f, 0.f));
	
	
	Change = glm::translate(Unit, float_Position) * Rotate * Scale * Trans;

	static int time = 0;
	if (Attacked) {
		Color *= glm::vec3(1, 0, 0);
		if (time > 20) {
			time = 0;
			Attacked = false;
		}
		else
			++time;
	}
	else
		Color = origin_Color;
}

void CAnimal::FixedUpdate()
{
	float speed = 0.02;

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

	if (Hp > 5)
	if(!Attacked_Motion)
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
	else {

		float_Position.x += glm::sin(glm::radians(MouseAngle.first)) * 0.75f;
		float_Position.z -= glm::cos(glm::radians(MouseAngle.first)) * 0.75f;
		Attacked_Motion = false;
	}

	auto itrTemp = World.Objects.find(this);
	if (itrTemp != World.Objects.end()) {
		World.Objects.erase(itrTemp);
	}

	Position.x = round(float_Position.x);
	Position.y = ceil(float_Position.y);
	Position.z = round(float_Position.z);

	World.Objects.insert(this);
}

void CAnimal::Render()
{
	if (Hp > 5) {

		glBindVertexArray(BlockVAO);

		GLuint Color = glGetUniformLocation(shaderID, "objectColor");
		glUniform3f(Color, this->Color.r, this->Color.g, this->Color.b);

		GLuint modelLocation = glGetUniformLocation(shaderID, "modelTransform");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Change)); //--- modelTransform 변수에 변환 값 적용하기

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	else {

		glBindVertexArray(BlockVAO);

		GLuint Color = glGetUniformLocation(shaderID, "objectColor");
		//glUniform3f(Color, this->Color.r, this->Color.g, this->Color.b);
		glUniform3f(Color, 0,0,0);

		GLuint modelLocation = glGetUniformLocation(shaderID, "modelTransform");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Change)); //--- modelTransform 변수에 변환 값 적용하기

		glDrawArrays(GL_TRIANGLES, 0, 36);
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
