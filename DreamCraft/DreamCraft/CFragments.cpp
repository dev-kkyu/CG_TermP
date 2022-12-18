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
	random_device rd;
	default_random_engine dre(rd());
	std::uniform_real_distribution<float> x(Position.x-0.7, Position.x+0.7);
	std::uniform_real_distribution<float> y(Position.y-1.2, Position.y+0.2);
	std::uniform_real_distribution<float> z(Position.z-0.7, Position.z+0.7);
	std::uniform_real_distribution<float> sped(0.1, 1);

	std::uniform_int_distribution<int> ren(0, 2);

	int num = ren(dre);

	

	switch (object)
	{
	case 기본흙:
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

	case 잔디흙:
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
	pos = glm::vec3(x(dre), y(dre), z(dre));

	Update();


}

void CFragments::Update()
{

	glm::mat4 scaleMat;
	glm::mat4 posMat;

	scaleMat = glm::scale(glm::mat4(1.0f), scale);    //--- 신축 행렬
	posMat = glm::translate(glm::mat4(1.0f), pos);   //--- 이동 행렬

	Change = posMat * scaleMat;

}

void CFragments::FixedUpdate()
{
}

void CFragments::Render()
{
	glBindVertexArray(BlockVAO);


	GLuint selectColorLocation = glGetUniformLocation(shaderID, "selectColor");	//--- 텍스처 사용
	glUniform1i(selectColorLocation, 0);

	GLuint model = glGetUniformLocation(shaderID, "modelTransform");
	glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(Change));

	//glBindTexture(GL_TEXTURE_2D, Texture[0]);
	GLuint Color = glGetUniformLocation(shaderID, "objectColor");

	
	
	glUniform4f(Color, color.r, color.g, color.b, 1);
	glDrawArrays(GL_TRIANGLES, 0, 36);

}

void CFragments::Release()
{
}
