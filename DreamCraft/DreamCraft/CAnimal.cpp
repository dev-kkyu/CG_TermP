#include "CAnimal.h"

CAnimal::CAnimal(glm::vec3 Position) : CGameObject{ Position }
{
	Initialize();
}

CAnimal::~CAnimal()
{
}

void CAnimal::Initialize()
{
	random_device rd;
	default_random_engine dre{ rd() };
	uniform_real_distribution<float> urd{ 0.f, 1.f };

	Color = glm::vec3{ urd(dre),urd(dre), urd(dre) };

	Update();
}

void CAnimal::Update()
{
	glm::mat4 Trans;
	glm::mat4 Scale;

	Trans = glm::translate(Unit, glm::vec3(0.f, -0.5f, 0.f));
	Scale = glm::scale(Unit, glm::vec3(1.f, 1.f, 2.f));

	Change = Scale * Trans;

	Trans = glm::translate(Unit, Position);

	Change = Trans * Change;
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
