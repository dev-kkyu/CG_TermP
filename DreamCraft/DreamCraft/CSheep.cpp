#include "CSheep.h"

#include "CWorld.h"
extern CWorld World;

CSheep::CSheep(glm::vec3 Position) : CAnimal{ Position }
{
}

CSheep::~CSheep()
{
}

void CSheep::Release()
{
}

void CSheep::Render()
{
	if (Hp > 5) {
		if (hold_Scissors && !hairless) {
			glBindVertexArray(BlockVAO);

			//GLuint selectColorLocation = glGetUniformLocation(shaderID, "selectColor");	//--- 텍스처 사용
			//glUniform1i(selectColorLocation, 0);

			//GLuint Color = glGetUniformLocation(shaderID, "objectColor");
			////glUniform3f(Color, this->Color.r, this->Color.g, this->Color.b);
			//glUniform3f(Color, 1, 1, 1);

			//GLuint modelLocation = glGetUniformLocation(shaderID, "modelTransform");
			//glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Change)); //--- modelTransform 변수에 변환 값 적용하기

			//glDrawArrays(GL_TRIANGLES, 0, 36);

			hairless = true;				// 털 깎인 양으로 빠꾸는 변수 on
			Wool = true;					// 양털 생성하는 변수 on
			Wool_Position = Position;		// 양털이 깎인 위치 저장

			this->Color = glm::vec3(1, 1, 1);
			origin_Color = this->Color;

		}
		else if (hairless) {
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
		else if (!hairless) {
			glBindVertexArray(BlockVAO);

			GLuint selectColorLocation = glGetUniformLocation(shaderID, "selectColor");	//--- 텍스처 사용
			glUniform1i(selectColorLocation, 1);

			GLuint modelLocation = glGetUniformLocation(shaderID, "modelTransform");
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Change)); //--- modelTransform 변수에 변환 값 적용하기

			for (int i = 0; i < 6; ++i) {
				glBindTexture(GL_TEXTURE_2D, Texture[3]);
				glDrawArrays(GL_TRIANGLES, i * 6, 6);
			}



		}
	}
	else {			// 양죽음
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

	if (Wool) {		// 양털 드랍

		glBindVertexArray(BlockVAO);

		GLuint selectColorLocation = glGetUniformLocation(shaderID, "selectColor");	//--- 텍스처 사용
		glUniform1i(selectColorLocation, 1);

		glm::mat4 Trans;
		glm::mat4 Scale;

		Trans = glm::translate(Unit, Wool_Position);
		Scale = glm::scale(Unit, glm::vec3(0.5, 0.5, 0.5));

		glm::mat4 Change_Wool = Trans * Scale;

		GLuint model = glGetUniformLocation(shaderID, "modelTransform");
		glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(Change_Wool));

		for (int i = 0; i < 6; ++i) {
			glBindTexture(GL_TEXTURE_2D, Texture[3]);
			glDrawArrays(GL_TRIANGLES, i * 6, 6);
		}

	}
}
