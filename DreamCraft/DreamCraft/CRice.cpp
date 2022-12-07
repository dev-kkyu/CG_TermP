#include "CRice.h"

CRice::CRice(glm::vec3 Position) : CBlock{ Position }
{
	Initialize();
}

CRice::~CRice()
{
}

void CRice::Initialize()
{
	Hp = 10;

	random_device rd;
	default_random_engine dre{ rd() };
	uniform_real_distribution<float> urd{ 0.f, 1.f };

	Color = glm::vec3{ urd(dre),urd(dre), urd(dre) };


	glm::mat4 Trans;

	Trans = glm::translate(Unit, glm::vec3(0.f, -0.5f, 0.f));

	Change = Trans;

	Trans = glm::translate(Unit, Position);

	Change = Trans * Change;
}

void CRice::Update()
{
}

void CRice::FixedUpdate()
{
}

void CRice::Render()
{
	glBindVertexArray(BlockVAO);

	GLuint selectColorLocation = glGetUniformLocation(shaderID, "selectColor");	//--- 텍스처 사용
	glUniform1i(selectColorLocation, 1);

	GLuint model = glGetUniformLocation(shaderID, "modelTransform");
	glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(Change));

	for (int i = 0; i < 6; ++i) {
		if (i != 2 && i != 4) {
			glBindTexture(GL_TEXTURE_2D, Texture[31]);
			glDrawArrays(GL_TRIANGLES, i * 6, 6);
		}
	}
}

void CRice::Release()
{
}
