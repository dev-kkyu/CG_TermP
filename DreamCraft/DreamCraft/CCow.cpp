#include "CCow.h"
#include "CWorld.h"
extern CWorld World;

CCow::CCow(glm::vec3 Position) : CAnimal{ Position }
{
}

CCow::~CCow()
{
}

void CCow::Release()
{
}

void CCow::Render()
{
	if (Hp > 5) {

		glBindVertexArray(BlockVAO);

		GLuint selectColorLocation = glGetUniformLocation(shaderID, "selectColor");	//--- 텍스처 사용
		glUniform1i(selectColorLocation, 1);

		GLuint modelLocation = glGetUniformLocation(shaderID, "modelTransform");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Change)); //--- modelTransform 변수에 변환 값 적용하기

		for (int i = 0; i < 6; ++i) {
			glBindTexture(GL_TEXTURE_2D, Texture[8]);
			glDrawArrays(GL_TRIANGLES, i * 6, 6);
		}
	}
	else {		// 동물 죽음

		glBindVertexArray(BlockVAO);

		GLuint selectColorLocation = glGetUniformLocation(shaderID, "selectColor");	//--- 텍스처 사용
		glUniform1i(selectColorLocation, 1);

		GLuint modelLocation = glGetUniformLocation(shaderID, "modelTransform");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Change)); //--- modelTransform 변수에 변환 값 적용하기

		for (int i = 0; i < 6; ++i) {
			glBindTexture(GL_TEXTURE_2D, Texture[11]);
			glDrawArrays(GL_TRIANGLES, i * 6, 6);
		}

	}

}
