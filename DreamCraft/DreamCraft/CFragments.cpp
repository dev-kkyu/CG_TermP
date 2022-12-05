#include "CFragments.h"

CFragments::CFragments(glm::vec3 Position, int object) : 
	CBlock{ Position },  object{  object }
{
	Initialize();
}

CFragments::~CFragments()
{
}

void CFragments::Initialize()
{
	random_device r;
	default_random_engine ge(r());
	std::uniform_real_distribution<float> x(Position.x-0.7, Position.x+0.7);
	std::uniform_real_distribution<float> y(Position.y-1, Position.y+0.2);
	std::uniform_real_distribution<float> z(Position.z-0.7, Position.z+0.7);
	std::uniform_real_distribution<float> sped(0.1, 1);

	std::uniform_int_distribution<int> ren(0, 2);

	int num = ren(ge);

	

	switch (object)
	{
	case �⺻��:
		switch (num)
		{
		case 0:
			color = glm::vec3(140 / 255., 140 / 255., 140 / 255.);
			break;
		case 1:
			color = glm::vec3(180 / 255., 121 / 255., 86 / 255.);
			break;
		case 2:
			color = glm::vec3(237 / 255., 175 / 255., 140 / 255.);
			break;
		}
		break;

	case �ܵ���:
		switch (num)
		{
		case 0:
			color = glm::vec3(92 / 255., 142 / 255., 81 / 255.);
			break;
		case 1:
			color = glm::vec3(180 / 255., 121 / 255., 86 / 255.);
			break;
		case 2:
			color = glm::vec3(237 / 255., 175 / 255., 140 / 255.);
			break;

		}

		break;
	}

	scale = glm::vec3(0.07, 0.07, 0.07);
	pos = glm::vec3(x(ge), y(ge), z(ge));

	Update();


}

void CFragments::Update()
{

	glm::mat4 scaleMat;
	glm::mat4 posMat;

	scaleMat = glm::scale(glm::mat4(1.0f), glm::vec3(scale.x, scale.y, scale.z));    //--- ���� ���
	posMat = glm::translate(glm::mat4(1.0f), glm::vec3(pos.x, pos.y, pos.z));   //--- �̵� ���

	transMatrix = posMat * scaleMat;

}

void CFragments::FixedUpdate()
{
}

void CFragments::Render()
{
	glBindVertexArray(BlockVAO);


	GLuint selectColorLocation = glGetUniformLocation(shaderID, "selectColor");	//--- �ؽ�ó ���
	glUniform1i(selectColorLocation, 0);

	GLuint model = glGetUniformLocation(shaderID, "modelTransform");
	glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(transMatrix));

	//glBindTexture(GL_TEXTURE_2D, Texture[0]);
	GLuint Color = glGetUniformLocation(shaderID, "objectColor");

	
	
	glUniform3f(Color, color.r, color.g, color.b);
	glDrawArrays(GL_TRIANGLES, 0, 36);

}

void CFragments::Release()
{
}
