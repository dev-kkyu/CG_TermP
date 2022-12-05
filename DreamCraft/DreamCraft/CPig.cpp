#include "CPig.h"

CPig::CPig(glm::vec3 Position) : CAnimal{ Position }
{
}

CPig::~CPig()
{
}

void CPig::Release()
{
}

void CPig:: Render() {


	if (Hp > 5) {

		glBindVertexArray(BlockVAO);

		GLuint selectColorLocation = glGetUniformLocation(shaderID, "selectColor");	//--- �ؽ�ó ���
		glUniform1i(selectColorLocation, 1);

		GLuint modelLocation = glGetUniformLocation(shaderID, "modelTransform");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Change)); //--- modelTransform ������ ��ȯ �� �����ϱ�

		for (int i = 0; i < 6; ++i) {
			glBindTexture(GL_TEXTURE_2D, Texture[12]);
			glDrawArrays(GL_TRIANGLES, i * 6, 6);
		}
	}
	else {		// ���� ����

		glBindVertexArray(BlockVAO);

		GLuint selectColorLocation = glGetUniformLocation(shaderID, "selectColor");	//--- �ؽ�ó ���
		glUniform1i(selectColorLocation, 1);

		GLuint modelLocation = glGetUniformLocation(shaderID, "modelTransform");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Change)); //--- modelTransform ������ ��ȯ �� �����ϱ�

		for (int i = 0; i < 6; ++i) {
			glBindTexture(GL_TEXTURE_2D, Texture[13]);		// �����Ӹ��Ϳ���
			glDrawArrays(GL_TRIANGLES, i * 6, 6);
		}

	}
}