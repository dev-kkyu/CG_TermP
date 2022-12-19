#include "CGrass.h"
#include "CFragments.h"

CGrass::CGrass(glm::vec3 Position) : CBlock{ Position }
{
	Initialize();
}

CGrass::~CGrass()
{
	Release();
}

void CGrass::Initialize()
{
	Hp = 10;

	glm::mat4 Trans;

	Trans = glm::translate(Unit, glm::vec3(0.f, -0.5f, 0.f));

	Change = Trans;

	Trans = glm::translate(Unit, Position);

	Change = Trans * Change;

	for (int i = 0; i < 100; ++i)
		myFragments.push_back(new CFragments{ Position ,ÀÜµðÈë });

	for (CFragments*& fragments : myFragments)
		fragments->Update();
}

void CGrass::Update()
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

void CGrass::FixedUpdate()
{
}

void CGrass::Render()
{
	glBindVertexArray(BlockVAO);

	GLuint selectColorLocation = glGetUniformLocation(shaderID, "selectColor");	//--- ÅØ½ºÃ³ »ç¿ë
	glUniform1i(selectColorLocation, 1);

	GLuint model = glGetUniformLocation(shaderID, "modelTransform");
	glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(Change));


	glBindTexture(GL_TEXTURE_2D, Texture[1]);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindTexture(GL_TEXTURE_2D, Texture[1]);
	glDrawArrays(GL_TRIANGLES, 6, 6);

	glBindTexture(GL_TEXTURE_2D, Texture[2]);	// À§
	glDrawArrays(GL_TRIANGLES, 12, 6);

	glBindTexture(GL_TEXTURE_2D, Texture[1]);
	glDrawArrays(GL_TRIANGLES, 18, 6);

	glBindTexture(GL_TEXTURE_2D, Texture[0]);	// ¹Ù´Ú
	glDrawArrays(GL_TRIANGLES, 24, 6);

	glBindTexture(GL_TEXTURE_2D, Texture[1]);
	glDrawArrays(GL_TRIANGLES, 30, 6);


	if (isfragments)
		for (CFragments*& fragments : myFragments)
			fragments->Render();
}

void CGrass::Release()
{
	for (auto tmp : myFragments) {
		delete tmp;
	}
}
