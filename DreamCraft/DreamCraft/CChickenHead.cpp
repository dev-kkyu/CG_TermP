#include "CChickenHead.h"

CChickenHead::CChickenHead(glm::vec3 Position) : CAnimalParts{ Position, �� }
{
}

CChickenHead::~CChickenHead()
{
}

void CChickenHead::Render()
{
	glBindVertexArray(BlockVAO);

	GLuint selectColorLocation = glGetUniformLocation(shaderID, "selectColor");	//--- �ؽ�ó ���
	glUniform1i(selectColorLocation, 1);

	GLuint model = glGetUniformLocation(shaderID, "modelTransform");
	glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(Change));

	glBindTexture(GL_TEXTURE_2D, Texture[16]);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindTexture(GL_TEXTURE_2D, Texture[16]);
	glDrawArrays(GL_TRIANGLES, 6, 6);

	glBindTexture(GL_TEXTURE_2D, Texture[16]);	// ��
	glDrawArrays(GL_TRIANGLES, 12, 6);

	glBindTexture(GL_TEXTURE_2D, Texture[16]);
	glDrawArrays(GL_TRIANGLES, 18, 6);

	glBindTexture(GL_TEXTURE_2D, Texture[16]);	// �ٴ�
	glDrawArrays(GL_TRIANGLES, 24, 6);

	glBindTexture(GL_TEXTURE_2D, Texture[20]);  // �Ӹ�
	glDrawArrays(GL_TRIANGLES, 30, 6);

}

void CChickenHead::Update()
{
	glm::mat4 Trans;
	glm::mat4 Rotate;
	glm::mat4 Scale;

	Trans = glm::translate(Unit, glm::vec3(0, 0.5, 0));		// �ϴ� ���� �÷��� ��� �����Ѵ�. �������� 1 ������ �� �ʿ�.

	Change = Trans;

	Scale = glm::scale(Unit, glm::vec3(0.4));	// �Ӹ� ũ�� 0.5

	Change = Scale * Change;

	Trans = glm::translate(Unit, glm::vec3(0, 0.7f, 0.25f));
	Change = Trans * Change;		// �ٵ� ���� �ø��� ������ �����

	Trans = glm::translate(Unit, glm::vec3(0, -1, 0));
	Change = Trans * Change;		// ž�̵鿡 �����ش�.

	Rotate = glm::rotate(Unit, glm::radians(Direction), glm::vec3(0, 1, 0));
	Change = Rotate * Change;	// ����������� ȸ��

	Trans = glm::translate(Unit, Position);
	Change = Trans * Change;	// �� ��ġ�� �̵�
}
