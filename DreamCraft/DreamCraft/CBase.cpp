#include "CBase.h"
#include "CFragments.h"

CBase::CBase(glm::vec3 Position) : CBlock{ Position }
{
	Initialize();
}

CBase::~CBase()
{
	Release();
}

void CBase::Initialize()
{
	Hp = 10;

	glm::mat4 Trans;

	Trans = glm::translate(Unit, glm::vec3(0.f, -0.5f, 0.f));

	Change = Trans;

	Trans = glm::translate(Unit, Position);

	Change = Trans * Change;

	for (int i = 0; i < 100; ++i)
		myFragments.push_back(new CFragments{ Position,기본흙 });

	for (CFragments*& fragments : myFragments)
		fragments->Update();
}

void CBase::Update()
{
	static int time = 0;
	if (isfragments) {
		if (time > 50) {
			time = 0;
			isfragments = false;
		}
		else
			++time;
	}	
}

void CBase::FixedUpdate()
{
}

void CBase::Render()
{
	glBindVertexArray(BlockVAO);

	GLuint selectColorLocation = glGetUniformLocation(shaderID, "selectColor");	//--- 텍스처 사용
	glUniform1i(selectColorLocation, 1);

	GLuint model = glGetUniformLocation(shaderID, "modelTransform");
	glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(Change));

	glBindTexture(GL_TEXTURE_2D, Texture[0]);
	glDrawArrays(GL_TRIANGLES, 0, 36);


	if (isfragments)
		for (CFragments*& fragments : myFragments)
			fragments->Render();

}

void CBase::Release()
{
	for (auto tmp : myFragments) {
		delete tmp;
	}
}
