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

	GLuint selectColorLocation = glGetUniformLocation(shaderID, "selectColor");	//--- �ؽ�ó ���
	glUniform1i(selectColorLocation, 1);

	GLuint model = glGetUniformLocation(shaderID, "modelTransform");
	glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(Change));

	switch (animalType)
	{
	case ��:
		
		for (int i = 0; i < 6; ++i) {
			glBindTexture(GL_TEXTURE_2D, Texture[8]);
			glDrawArrays(GL_TRIANGLES, i * 6, 6);
		}

		break;
	case ����:

		for (int i = 0; i < 6; ++i) {
			glBindTexture(GL_TEXTURE_2D, Texture[12]);
			glDrawArrays(GL_TRIANGLES, i * 6, 6);
		}

		break;
	case ��:

		for (int i = 0; i < 6; ++i) {
			glBindTexture(GL_TEXTURE_2D, Texture[3]);
			glDrawArrays(GL_TRIANGLES, i * 6, 6);
		}

		break;
	case ���ʾ�:

		for (int i = 0; i < 6; ++i) {
			glBindTexture(GL_TEXTURE_2D, Texture[4]);
			glDrawArrays(GL_TRIANGLES, i * 6, 6);
		}

		break;
	}
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
