#include "CChicken.h"

CChicken::CChicken(glm::vec3 Position) : CAnimal{ Position }
{
}

CChicken::~CChicken()
{
}

void CChicken::Release()
{
}

void CChicken::Render() 
{


	if (Hp > 5) {

		glBindVertexArray(BlockVAO);

		GLuint selectColorLocation = glGetUniformLocation(shaderID, "selectColor");	//--- �ؽ�ó ���
		glUniform1i(selectColorLocation, 1);

		GLuint modelLocation = glGetUniformLocation(shaderID, "modelTransform");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Change)); //--- modelTransform ������ ��ȯ �� �����ϱ�

		for (int i = 0; i < 6; ++i) {
			glBindTexture(GL_TEXTURE_2D, Texture[16]);
			glDrawArrays(GL_TRIANGLES, i * 6, 6);
		}
	}
	else {		// ���� ����

		glBindVertexArray(BlockVAO);

		GLuint selectColorLocation = glGetUniformLocation(shaderID, "selectColor");	//--- �ؽ�ó ���
		glUniform1i(selectColorLocation, 1);

		GLuint modelLocation = glGetUniformLocation(shaderID, "modelTransform");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Change)); //--- modelTransform ������ ��ȯ �� �����ϱ�

		//for (int i = 0; i < 6; ++i) {
		//	glBindTexture(GL_TEXTURE_2D, Texture[20]);		// �߸Ӹ��Ϳ���
		//	glDrawArrays(GL_TRIANGLES, i * 6, 6);
		//}

		glBindTexture(GL_TEXTURE_2D, Texture[17]);		
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glBindTexture(GL_TEXTURE_2D, Texture[17]);		
		glDrawArrays(GL_TRIANGLES, 6, 6);

		glBindTexture(GL_TEXTURE_2D, Texture[17]);		
		glDrawArrays(GL_TRIANGLES, 18, 6);

		glBindTexture(GL_TEXTURE_2D, Texture[17]);		
		glDrawArrays(GL_TRIANGLES, 30, 6);


	}
}

//void CChicken::Updata()
//{
//
//	//----- ��ȯ
//	glm::mat4 Rotate;
//	glm::mat4 Trans;
//	glm::mat4 Scale;
//
//	Trans = glm::translate(Unit, glm::vec3(0.f, -0.5f, 0.f));
//
//	if (Hp > 5)
//		Scale = glm::scale(Unit, glm::vec3(1.f, 1.f, 2.f));
//	else
//		Scale = glm::scale(Unit, glm::vec3(0.5, 0.5, 0.5));
//
//	Rotate = glm::rotate(glm::mat4(1.0f), glm::radians(animal_Direction), glm::vec3(0.f, 1.f, 0.f));
//
//	Change = glm::translate(Unit, float_Position) * Rotate * Scale * Trans;
//}
