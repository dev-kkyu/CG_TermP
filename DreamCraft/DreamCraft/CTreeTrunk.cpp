#include "CTreeTrunk.h"

CTreeTrunk::CTreeTrunk(glm::vec3 Position) : CBlock{ Position }
{
	Initialize();
}

CTreeTrunk::~CTreeTrunk()
{
}

void CTreeTrunk::Initialize()
{
	Hp = 10;

	glm::mat4 Trans;

	Trans = glm::translate(Unit, glm::vec3(0.f, -0.5f, 0.f));

	Change = Trans;

	Trans = glm::translate(Unit, Position);

	Change = Trans * Change;
}

void CTreeTrunk::Update()
{
}

void CTreeTrunk::FixedUpdate()
{
}

void CTreeTrunk::Render()
{
	glBindVertexArray(BlockVAO);

	GLuint selectColorLocation = glGetUniformLocation(shaderID, "selectColor");	//--- 텍스처 사용
	glUniform1i(selectColorLocation, 1);

	GLuint model = glGetUniformLocation(shaderID, "modelTransform");
	glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(Change));

	//for (int i = 0; i < 6; ++i) {
	//	glBindTexture(GL_TEXTURE_2D, Texture[1]);
	//	glDrawArrays(GL_TRIANGLES, i * 6, 6);
	//}

	glBindTexture(GL_TEXTURE_2D, Texture[25]);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindTexture(GL_TEXTURE_2D, Texture[25]);
	glDrawArrays(GL_TRIANGLES, 6, 6);

	glBindTexture(GL_TEXTURE_2D, Texture[26]);	// 위
	glDrawArrays(GL_TRIANGLES, 12, 6);

	glBindTexture(GL_TEXTURE_2D, Texture[25]);
	glDrawArrays(GL_TRIANGLES, 18, 6);

	glBindTexture(GL_TEXTURE_2D, Texture[26]);	// 바닥
	glDrawArrays(GL_TRIANGLES, 24, 6);

	glBindTexture(GL_TEXTURE_2D, Texture[25]);
	glDrawArrays(GL_TRIANGLES, 30, 6);
}

void CTreeTrunk::Release()
{
}