#include "AnimalHead.h"

AnimalHead::AnimalHead(glm::vec3 Position, int animalType) : CAnimalParts{ Position, animalType }
{
}

AnimalHead::~AnimalHead()
{
}

void AnimalHead::Render()
{
	glBindVertexArray(BlockVAO);

	GLuint selectColorLocation = glGetUniformLocation(shaderID, "selectColor");	//--- 텍스처 사용
	glUniform1i(selectColorLocation, 1);

	GLuint model = glGetUniformLocation(shaderID, "modelTransform");
	glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(Change));

	switch (animalType)
	{
	case 소:

		glBindTexture(GL_TEXTURE_2D, Texture[8]);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glBindTexture(GL_TEXTURE_2D, Texture[8]);
		glDrawArrays(GL_TRIANGLES, 6, 6);

		glBindTexture(GL_TEXTURE_2D, Texture[8]);	// 위
		glDrawArrays(GL_TRIANGLES, 12, 6);

		glBindTexture(GL_TEXTURE_2D, Texture[8]);
		glDrawArrays(GL_TRIANGLES, 18, 6);

		glBindTexture(GL_TEXTURE_2D, Texture[8]);	// 바닥
		glDrawArrays(GL_TRIANGLES, 24, 6);

		glBindTexture(GL_TEXTURE_2D, Texture[11]);  // 머리
		glDrawArrays(GL_TRIANGLES, 30, 6);

		break;
	case 돼지:
						
		glBindTexture(GL_TEXTURE_2D, Texture[12]);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glBindTexture(GL_TEXTURE_2D, Texture[12]);
		glDrawArrays(GL_TRIANGLES, 6, 6);

		glBindTexture(GL_TEXTURE_2D, Texture[12]);	// 위
		glDrawArrays(GL_TRIANGLES, 12, 6);

		glBindTexture(GL_TEXTURE_2D, Texture[12]);
		glDrawArrays(GL_TRIANGLES, 18, 6);

		glBindTexture(GL_TEXTURE_2D, Texture[12]);	// 바닥
		glDrawArrays(GL_TRIANGLES, 24, 6);

		glBindTexture(GL_TEXTURE_2D, Texture[15]);  // 머리
		glDrawArrays(GL_TRIANGLES, 30, 6);

		break;
	case 양:

		glBindTexture(GL_TEXTURE_2D, Texture[3]);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glBindTexture(GL_TEXTURE_2D, Texture[3]);
		glDrawArrays(GL_TRIANGLES, 6, 6);

		glBindTexture(GL_TEXTURE_2D, Texture[3]);	// 위
		glDrawArrays(GL_TRIANGLES, 12, 6);

		glBindTexture(GL_TEXTURE_2D, Texture[3]);
		glDrawArrays(GL_TRIANGLES, 18, 6);

		glBindTexture(GL_TEXTURE_2D, Texture[3]);	// 바닥
		glDrawArrays(GL_TRIANGLES, 24, 6);

		glBindTexture(GL_TEXTURE_2D, Texture[7]);  // 머리
		glDrawArrays(GL_TRIANGLES, 30, 6);

		break;
	}
	
}

void AnimalHead::Update()
{
	glm::mat4 Trans;
	glm::mat4 Rotate;
	glm::mat4 Scale;

	Trans = glm::translate(Unit, glm::vec3(0, 0.5, 0));		// 일단 위로 올려서 계산 시작한다. 마지막에 1 내리는 거 필요.

	Change = Trans;

	Scale = glm::scale(Unit, glm::vec3(0.5));	// 머리 크기 0.5

	Change = Scale * Change;

	Trans = glm::translate(Unit, glm::vec3(0, 1.f, 0.75));
	Change = Trans * Change;		// 바디 위로 올리고 앞으로 땡기고

	Trans = glm::translate(Unit, glm::vec3(0, -1, 0));
	Change = Trans * Change;		// 탑미들에 맞춰준다.

	Rotate = glm::rotate(Unit, glm::radians(Direction), glm::vec3(0, 1, 0));
	Change = Rotate * Change;	// 진행방향으로 회전

	Trans = glm::translate(Unit, Position);
	Change = Trans * Change;	// 내 위치로 이동
}
