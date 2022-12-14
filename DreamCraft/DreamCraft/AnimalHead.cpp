#include "AnimalHead.h"

AnimalHead::AnimalHead(glm::vec3 Position) : CAnimalParts{ Position }
{
}

AnimalHead::~AnimalHead()
{
}

void AnimalHead::Render()
{
	glBindVertexArray(BlockVAO);

	GLuint selectColorLocation = glGetUniformLocation(shaderID, "selectColor");
	glUniform1i(selectColorLocation, 0);	//--- ���� ���(�ؽ��� ������ �� �ٲ��ֱ�

	GLuint Color = glGetUniformLocation(shaderID, "objectColor");
	glUniform4f(Color, 1, 0, 0, 1);

	GLuint modelLocation = glGetUniformLocation(shaderID, "modelTransform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Change)); //--- modelTransform ������ ��ȯ �� �����ϱ�

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void AnimalHead::Update()
{
	glm::mat4 Trans;
	glm::mat4 Rotate;
	glm::mat4 Scale;

	Trans = glm::translate(Unit, glm::vec3(0, 0.5, 0));		// �ϴ� ���� �÷��� ��� �����Ѵ�. �������� 1 ������ �� �ʿ�.

	Change = Trans;

	Scale = glm::scale(Unit, glm::vec3(0.5));	// �Ӹ� ũ�� 0.5

	Change = Scale * Change;

	Trans = glm::translate(Unit, glm::vec3(0, 1.f, 0.75));
	Change = Trans * Change;		// �ٵ� ���� �ø��� ������ �����

	Trans = glm::translate(Unit, glm::vec3(0, -1, 0));
	Change = Trans * Change;		// ž�̵鿡 �����ش�.

	Rotate = glm::rotate(Unit, glm::radians(Direction), glm::vec3(0, 1, 0));
	Change = Rotate * Change;	// ����������� ȸ��

	Trans = glm::translate(Unit, Position);
	Change = Trans * Change;	// �� ��ġ�� �̵�
}
