#include "CAnimal.h"

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

void CAnimal::Initialize()
{
	animal_Direction = dict_urd(dre) * 45.f;			// 이동 방향 1-8까지 n*45도 만큼 회전
	Travel = travel_urd(dre);

	origin_Position = Position;
	before_Position = Position;

	random_device rd;
	default_random_engine dre{ rd() };
	uniform_real_distribution<float> urd{ 0.f, 1.f };

	Color = glm::vec3{ urd(dre),urd(dre), urd(dre) };

	Update();
}

void CAnimal::Update()
{
	static float temp_x = 0, temp_z = 0;

	if (pow(before_Position.x - Position.x, 2)
		+ pow(before_Position.z - Position.z, 2) >= pow(Travel, 2)  // 한 방향으로 travel만큼 이동했으면
		||
		(pow(temp_x- origin_Position.x, 2) + pow(temp_z- origin_Position.z, 2) >= 100)   //다음 이동이 경계에 걸리면
		) {

		animal_Direction = dict_urd(dre) * 45.f;
		Travel = travel_urd(dre);
		before_Position = Position;
	}

	float speed = 0.05;
	
	switch ((int)(animal_Direction / 45))
	{
	case 1:
		Position.x += speed;
		Position.z += speed;
		temp_x = Position.x + speed * 2;
		temp_z = Position.z + speed * 2;
		break;
	case 2:
		Position.x += speed;
		temp_x = Position.x + speed * 2;

		break;
	case 3:
		Position.x += speed;
		Position.z -= speed;
		temp_x = Position.x + speed * 2;
		temp_z = Position.z - speed * 2;
		break;
	case 4:
		Position.z -= speed;
		temp_z = Position.z - speed * 2;
		break;
	case 5:
		Position.x -= speed;
		Position.z -= speed;
		temp_x = Position.x - speed * 2;
		temp_z = Position.z - speed * 2;
		break;
	case 6:
		Position.x -= speed;
		temp_x = Position.x - speed * 2;
		break;
	case 7:
		Position.x -= speed;
		Position.z += speed;
		temp_x = Position.x - speed * 2;
		temp_z = Position.z + speed * 2;
		break;
	case 8:
		Position.z += speed;
		temp_z = Position.z + speed * 2;
		break;
	}

	//----- 변환
	glm::mat4 rotation;
	glm::mat4 Trans;
	glm::mat4 Scale;

	Trans = glm::translate(Unit, glm::vec3(0.f, -0.5f, 0.f));
	Scale = glm::scale(Unit, glm::vec3(1.f, 1.f, 2.f));
	rotation = glm::rotate(glm::mat4(1.0f), glm::radians(animal_Direction), glm::vec3(0.f, 1.f, 0.f));
	
	
	Change = glm::translate(Unit, Position) * Trans * rotation * Scale;
}

void CAnimal::Render()
{
	glBindVertexArray(BlockVAO);

	GLuint Color = glGetUniformLocation(shaderID, "objectColor");
	glUniform3f(Color, this->Color.r, this->Color.g, this->Color.b);

	GLuint modelLocation = glGetUniformLocation(shaderID, "modelTransform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Change)); //--- modelTransform 변수에 변환 값 적용하기

	glDrawArrays(GL_TRIANGLES, 0, 36);
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
