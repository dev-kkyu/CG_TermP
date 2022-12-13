#include "CCloud.h"

CCloud::CCloud(glm::vec3 Position) : CBlock{ Position }
{
	Initialize();
}

CCloud::~CCloud()
{
}

void CCloud::Initialize()
{

	
	Color = glm::vec3{ 1,1,1 };


	glm::mat4 Trans;

	Trans = glm::translate(Unit, glm::vec3(0.f, -0.5f, 0.f));

	Change = Trans;

	Trans = glm::translate(Unit, Position);

	Change = Trans * Change;
}

void CCloud::Update()
{
}

void CCloud::FixedUpdate()
{
}

void CCloud::Render()
{
	glBindVertexArray(BlockVAO);

	GLuint selectColorLocation = glGetUniformLocation(shaderID, "selectColor");	//--- 텍스처 사용
	glUniform1i(selectColorLocation, 0);

	GLuint Color = glGetUniformLocation(shaderID, "objectColor");
	glUniform4f(Color, this->Color.r, this->Color.g, this->Color.b, 1.0);

	GLuint modelLocation = glGetUniformLocation(shaderID, "modelTransform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Change)); //--- modelTransform 변수에 변환 값 적용하기

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void CCloud::Release()
{
}
