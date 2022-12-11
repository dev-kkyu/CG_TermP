#include "CSheepNOTUL.h"

#include "CWorld.h"
extern CWorld World;

CSheepNOTUL::CSheepNOTUL(glm::vec3 Position, Form animalForm) 
	: CAnimal{ Position, animalForm, 무너양 }
{
}

CSheepNOTUL::~CSheepNOTUL()
{
	Release();
}

void CSheepNOTUL::Release()
{
	World.died_Objects.insert(new CSheepNOTUL{ Position, Form::item });
}

void CSheepNOTUL::Render()
{
	if (animalForm == Form::creature) {
		
		glBindVertexArray(BlockVAO);

		GLuint selectColorLocation = glGetUniformLocation(shaderID, "selectColor");	//--- 텍스처 사용
		glUniform1i(selectColorLocation, 1);

		GLuint modelLocation = glGetUniformLocation(shaderID, "modelTransform");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Change)); //--- modelTransform 변수에 변환 값 적용하기

		for (int i = 0; i < 6; ++i) {
			glBindTexture(GL_TEXTURE_2D, Texture[4]);
			glDrawArrays(GL_TRIANGLES, i * 6, 6);
		}
		
	}
	else if (animalForm == Form::item) {			// 양죽음
		glBindVertexArray(BlockVAO);

		GLuint selectColorLocation = glGetUniformLocation(shaderID, "selectColor");	//--- 텍스처 사용
		glUniform1i(selectColorLocation, 1);

		GLuint modelLocation = glGetUniformLocation(shaderID, "modelTransform");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Change)); //--- modelTransform 변수에 변환 값 적용하기

		for (int i = 0; i < 6; ++i) {
			glBindTexture(GL_TEXTURE_2D, Texture[7]);
			glDrawArrays(GL_TRIANGLES, i * 6, 6);
		}

	}

}
