#include "CPlayer.h"

CPlayer::CPlayer(glm::vec3 Position) : CGameObject{ Position }
{
	Initialize();
}

CPlayer::~CPlayer()
{
}

void CPlayer::Update(glm::vec3 Position)
{
	this->Position = Position;
}

void CPlayer::Initialize()
{
	Update();
}

void CPlayer::Update()
{
	glm::mat4 Trans;
	glm::mat4 Scale;
	glm::mat4 Rotate;

	Trans = glm::translate(Unit, glm::vec3(0.f, -0.5f, 0.f));
	Scale = glm::scale(Unit, glm::vec3(1.f, 2.f, 1.f));

	Change = Scale * Trans;

	Rotate = glm::rotate(Unit, glm::radians(-MouseAngle.first + 180.f), glm::vec3(0, 1, 0));
	Change = Rotate * Change;

	Trans = glm::translate(Unit, Position);

	Change = Trans * Change;
}

void CPlayer::FixedUpdate()
{
}

void CPlayer::Render()
{
	glBindVertexArray(BlockVAO);

	GLuint Color = glGetUniformLocation(shaderID, "objectColor");
	glUniform3f(Color, 1, 1, 1);

	GLuint modelLocation = glGetUniformLocation(shaderID, "modelTransform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Change)); //--- modelTransform 변수에 변환 값 적용하기

	glDrawArrays(GL_TRIANGLES, 0, 36);
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
