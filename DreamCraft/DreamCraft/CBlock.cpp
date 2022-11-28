#include "CBlock.h"

CBlock::CBlock(glm::vec3 Position) : CGameObject{Position}
{
	Initialize();
}

CBlock::~CBlock()
{
}

void CBlock::Initialize()
{
	glm::mat4 Trans;
	
	Trans = glm::translate(Unit, glm::vec3(0.f, -0.5f, 0.f));

	Change = Trans;

	Trans = glm::translate(Unit, Position);

	Change = Trans * Change;
}

void CBlock::Render()
{
	glBindVertexArray(BlockVAO);

	GLuint modelLocation = glGetUniformLocation(shaderID, "modelTransform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Change)); //--- modelTransform 변수에 변환 값 적용하기

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

float CBlock::getLeft()
{
	return Position.x - 0.5f;
}

float CBlock::getRight()
{
	return Position.x + 0.5f;
}

float CBlock::getBehind()
{
	return Position.z - 0.5f;
}

float CBlock::getFront()
{
	return Position.z + 0.5f;
}

float CBlock::getBottom()
{
	return Position.y - 1.f;
}

float CBlock::getTop()
{
	return Position.y;
}
