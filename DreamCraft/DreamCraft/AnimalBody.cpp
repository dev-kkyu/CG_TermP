#include "AnimalBody.h"

AnimalBody::AnimalBody(glm::vec3 Position, int animalType) : CAnimalParts{ Position, animalType }
{
}

AnimalBody::~AnimalBody()
{
}

void AnimalBody::Render()
{
	glBindVertexArray(BlockVAO);

	GLuint selectColorLocation = glGetUniformLocation(shaderID, "selectColor");
	glUniform1i(selectColorLocation, 0);	//--- ���� ���(�ؽ��� ������ �� �ٲ��ֱ�

	GLuint Color = glGetUniformLocation(shaderID, "objectColor");
	glUniform4f(Color, 1, 1, 0, 1);

	GLuint modelLocation = glGetUniformLocation(shaderID, "modelTransform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Change)); //--- modelTransform ������ ��ȯ �� �����ϱ�

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void AnimalBody::Update()
{
	glm::mat4 Trans;
	glm::mat4 Rotate;
	glm::mat4 Scale;

	Trans = glm::translate(Unit, glm::vec3(0, 0.5, 0));		// �ϴ� ���� �÷��� ��� �����Ѵ�. �������� 1 ������ �� �ʿ�.

	Change = Trans;

	Scale = glm::scale(Unit, glm::vec3(0.75, 0.75, 1.5));	// ������� 1.5, �ʺ� 0.75�� ����, ���� 0.75

	Change = Scale * Change;

	Trans = glm::translate(Unit, glm::vec3(0, 0.5, 0));
	Change = Trans * Change;		// �ٸ� ���� �÷��ش�.

	Trans = glm::translate(Unit, glm::vec3(0, -1, 0));
	Change = Trans * Change;		// ž�̵鿡 �����ش�.

	Rotate = glm::rotate(Unit, glm::radians(Direction), glm::vec3(0, 1, 0));
	Change = Rotate * Change;	// ����������� ȸ��

	Trans = glm::translate(Unit, Position);
	Change = Trans * Change;	// �� ��ġ�� �̵�

}