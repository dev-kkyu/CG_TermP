#include "CBlock.h"

#include "CWorld.h"
extern CWorld World;

CBlock::CBlock(glm::vec3 Position) : CGameObject{Position}
{
	Initialize();
}

CBlock::~CBlock()
{
}

void CBlock::be_Attacked(int Weapon)
{
	switch (Weapon) {
	case ¸Ç¼Õ:
		cout << "¸Ç¼Õ" << endl;
		--Hp;
		break;
	case Ä®:
		cout << "Ä®" << endl;
		break;
	case °î±ªÀÌ:
		cout << "°î±ªÀÌ" << endl;
		Hp -= 2;
		break;
	case ÃÖ°­¹«±â:
		cout << "ÃÖ°­¹«±â" << endl;
		Hp -= 100;
		break;
	}
	isfragments = true;

}

void CBlock::Initialize()
{

}

void CBlock::Render()
{
	glBindVertexArray(BlockVAO);

	GLuint modelLocation = glGetUniformLocation(shaderID, "modelTransform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Change)); //--- modelTransform º¯¼ö¿¡ º¯È¯ °ª Àû¿ëÇÏ±â

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
