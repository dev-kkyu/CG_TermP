#include "CRice.h"
#include "CWorld.h"
extern CWorld World;

CRice::CRice(glm::vec3 Position, bool isItem) : CBlock{ Position }, isItem{ isItem }
{
	Initialize();
}

CRice::~CRice()
{
	Release();
}

void CRice::Initialize()
{
	Hp = 10;

	glm::mat4 Trans;
	glm::mat4 Scale;

	Trans = glm::translate(Unit, glm::vec3(0.f, -0.5f, 0.f));

	Change = Trans;

	if (isItem) {
		Scale = glm::scale(Unit, glm::vec3(0.5, 0.5, 0.5));
		Change = Scale * Change;
	}

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

	glDisable(GL_CULL_FACE);
	for (int i = 0; i < 6; ++i) {
		if (i != 2 && i != 4) {
			glBindTexture(GL_TEXTURE_2D, Texture[31]);
			glDrawArrays(GL_TRIANGLES, i * 6, 6);
		}
	}
	glEnable(GL_CULL_FACE);
}

void CRice::Release()
{
	World.mined_Objects.insert(new CRice{ Position, true });
}
