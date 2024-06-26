#include "CBirchTrunk.h"

CBirchTrunk::CBirchTrunk(glm::vec3 Position) : CBlock{ Position }
{
	Initialize();
}

CBirchTrunk::~CBirchTrunk()
{
}

void CBirchTrunk::Initialize()
{
	Hp = 10;

	glm::mat4 Trans;

	Trans = glm::translate(Unit, glm::vec3(0.f, -0.5f, 0.f));

	Change = Trans;

	Trans = glm::translate(Unit, Position);

	Change = Trans * Change;
}

void CBirchTrunk::Update()
{
}

void CBirchTrunk::FixedUpdate()
{
}

void CBirchTrunk::Render()
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

	glBindTexture(GL_TEXTURE_2D, Texture[28]);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindTexture(GL_TEXTURE_2D, Texture[28]);
	glDrawArrays(GL_TRIANGLES, 6, 6);

	glBindTexture(GL_TEXTURE_2D, Texture[29]);	// 위
	glDrawArrays(GL_TRIANGLES, 12, 6);

	glBindTexture(GL_TEXTURE_2D, Texture[28]);
	glDrawArrays(GL_TRIANGLES, 18, 6);

	glBindTexture(GL_TEXTURE_2D, Texture[29]);	// 바닥
	glDrawArrays(GL_TRIANGLES, 24, 6);

	glBindTexture(GL_TEXTURE_2D, Texture[28]);
	glDrawArrays(GL_TRIANGLES, 30, 6);
}

void CBirchTrunk::Release()
{
}