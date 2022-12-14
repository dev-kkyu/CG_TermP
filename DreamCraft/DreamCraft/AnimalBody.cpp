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

	GLuint selectColorLocation = glGetUniformLocation(shaderID, "selectColor");	//--- 텍스처 사용
	glUniform1i(selectColorLocation, 1);

	GLuint model = glGetUniformLocation(shaderID, "modelTransform");
	glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(Change));

	switch (animalType)
	{
	case 소:
		
		for (int i = 0; i < 6; ++i) {
			glBindTexture(GL_TEXTURE_2D, Texture[8]);
			glDrawArrays(GL_TRIANGLES, i * 6, 6);
		}

		break;
	case 돼지:

		for (int i = 0; i < 6; ++i) {
			glBindTexture(GL_TEXTURE_2D, Texture[12]);
			glDrawArrays(GL_TRIANGLES, i * 6, 6);
		}

		break;
	case 양:

		for (int i = 0; i < 6; ++i) {
			glBindTexture(GL_TEXTURE_2D, Texture[3]);
			glDrawArrays(GL_TRIANGLES, i * 6, 6);
		}

		break;
	case 무너양:

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

	Trans = glm::translate(Unit, glm::vec3(0, 0.5, 0));		// 일단 위로 올려서 계산 시작한다. 마지막에 1 내리는 거 필요.

	Change = Trans;

	Scale = glm::scale(Unit, glm::vec3(0.75, 0.75, 1.5));	// 몸통길이 1.5, 너비 0.75로 가자, 높이 0.75

	Change = Scale * Change;

	Trans = glm::translate(Unit, glm::vec3(0, 0.5, 0));
	Change = Trans * Change;		// 다리 위로 올려준다.

	Trans = glm::translate(Unit, glm::vec3(0, -1, 0));
	Change = Trans * Change;		// 탑미들에 맞춰준다.

	Rotate = glm::rotate(Unit, glm::radians(Direction), glm::vec3(0, 1, 0));
	Change = Rotate * Change;	// 진행방향으로 회전

	Trans = glm::translate(Unit, Position);
	Change = Trans * Change;	// 내 위치로 이동

}
