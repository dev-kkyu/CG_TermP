#include "CSheepNOTUL.h"

#include "CWorld.h"
extern CWorld World;

CSheepNOTUL::CSheepNOTUL(glm::vec3 Position) : CAnimal{ Position }
{
}

CSheepNOTUL::~CSheepNOTUL()
{
}

void CSheepNOTUL::Release()
{
}

void CSheepNOTUL::Render()
{
	if (Hp > 5) {
		
		glBindVertexArray(BlockVAO);

		GLuint selectColorLocation = glGetUniformLocation(shaderID, "selectColor");	//--- �ؽ�ó ���
		glUniform1i(selectColorLocation, 1);

		GLuint modelLocation = glGetUniformLocation(shaderID, "modelTransform");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Change)); //--- modelTransform ������ ��ȯ �� �����ϱ�

		for (int i = 0; i < 6; ++i) {
			glBindTexture(GL_TEXTURE_2D, Texture[4]);
			glDrawArrays(GL_TRIANGLES, i * 6, 6);
		}
		
	}
	else {			// ������
		glBindVertexArray(BlockVAO);

		GLuint selectColorLocation = glGetUniformLocation(shaderID, "selectColor");	//--- �ؽ�ó ���
		glUniform1i(selectColorLocation, 1);

		GLuint modelLocation = glGetUniformLocation(shaderID, "modelTransform");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Change)); //--- modelTransform ������ ��ȯ �� �����ϱ�

		for (int i = 0; i < 6; ++i) {
			glBindTexture(GL_TEXTURE_2D, Texture[7]);
			glDrawArrays(GL_TRIANGLES, i * 6, 6);
		}

	}

}
