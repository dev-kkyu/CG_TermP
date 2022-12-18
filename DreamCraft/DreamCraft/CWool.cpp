#include "CWool.h"

CWool::CWool(glm::vec3 Position) : CBlock{ Position }
{
	Initialize();
}

CWool::~CWool()
{
}

void CWool::Initialize()
{
	Hp = 10;

	glm::mat4 Trans;

	Trans = glm::translate(Unit, glm::vec3(0.f, -0.5f, 0.f));

	Change = Trans;

	Trans = glm::translate(Unit, Position);

	Change = Trans * Change;
}

void CWool::Update()
{
}

void CWool::FixedUpdate()
{
}

void CWool::Render()
{
	glBindVertexArray(BlockVAO);

	GLuint selectColorLocation = glGetUniformLocation(shaderID, "selectColor");	//--- 텍스처 사용
	glUniform1i(selectColorLocation, 1);

	GLuint model = glGetUniformLocation(shaderID, "modelTransform");
	glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(Change));

	for (int i = 0; i < 6; ++i) {
		glBindTexture(GL_TEXTURE_2D, Texture[3]);
		glDrawArrays(GL_TRIANGLES, i * 6, 6);
	}
}

void CWool::Release()
{
}
