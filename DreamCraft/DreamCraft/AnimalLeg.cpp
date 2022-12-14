#include "AnimalLeg.h"

AnimalLeg::AnimalLeg(glm::vec3 Position, int LocationX, int LocationZ, int animalType)
	: CAnimalParts{ Position, animalType }, LocationX{ LocationX }, LocationZ{ LocationZ }, rotateValue(0.f), isrotDirec(false)
{
}

AnimalLeg::~AnimalLeg()
{
}

void AnimalLeg::Render()
{
	glBindVertexArray(BlockVAO);

	GLuint selectColorLocation = glGetUniformLocation(shaderID, "selectColor");	//--- 텍스처 사용
	glUniform1i(selectColorLocation, 1);

	GLuint model = glGetUniformLocation(shaderID, "modelTransform");
	glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(Change));

	switch (animalType)
	{
	case 소:

		glBindTexture(GL_TEXTURE_2D, Texture[10]);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glBindTexture(GL_TEXTURE_2D, Texture[10]);
		glDrawArrays(GL_TRIANGLES, 6, 6);

		glBindTexture(GL_TEXTURE_2D, Texture[8]);	// 위
		glDrawArrays(GL_TRIANGLES, 12, 6);

		glBindTexture(GL_TEXTURE_2D, Texture[10]);
		glDrawArrays(GL_TRIANGLES, 18, 6);

		glBindTexture(GL_TEXTURE_2D, Texture[8]);	// 바닥
		glDrawArrays(GL_TRIANGLES, 24, 6);

		glBindTexture(GL_TEXTURE_2D, Texture[10]);
		glDrawArrays(GL_TRIANGLES, 30, 6);

		break;
	case 돼지:
	
		glBindTexture(GL_TEXTURE_2D, Texture[14]);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glBindTexture(GL_TEXTURE_2D, Texture[14]);
		glDrawArrays(GL_TRIANGLES, 6, 6);

		glBindTexture(GL_TEXTURE_2D, Texture[12]);	// 위
		glDrawArrays(GL_TRIANGLES, 12, 6);

		glBindTexture(GL_TEXTURE_2D, Texture[14]);
		glDrawArrays(GL_TRIANGLES, 18, 6);

		glBindTexture(GL_TEXTURE_2D, Texture[12]);	// 바닥
		glDrawArrays(GL_TRIANGLES, 24, 6);

		glBindTexture(GL_TEXTURE_2D, Texture[14]);
		glDrawArrays(GL_TRIANGLES, 30, 6);

		break;
	case 양:
		
		glBindTexture(GL_TEXTURE_2D, Texture[6]);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glBindTexture(GL_TEXTURE_2D, Texture[6]);
		glDrawArrays(GL_TRIANGLES, 6, 6);

		glBindTexture(GL_TEXTURE_2D, Texture[3]);	// 위
		glDrawArrays(GL_TRIANGLES, 12, 6);

		glBindTexture(GL_TEXTURE_2D, Texture[6]);
		glDrawArrays(GL_TRIANGLES, 18, 6);

		glBindTexture(GL_TEXTURE_2D, Texture[3]);	// 바닥
		glDrawArrays(GL_TRIANGLES, 24, 6);

		glBindTexture(GL_TEXTURE_2D, Texture[6]); 
		glDrawArrays(GL_TRIANGLES, 30, 6);

		break;
	}

}

void AnimalLeg::Update()
{
	if (isrotDirec) {
		rotateValue += 1.f;
		if (rotateValue > 30.f)
			isrotDirec = false;
	}
	else {
		rotateValue -= 1.f;
		if (rotateValue < -30.f)
			isrotDirec = true;
	}

	glm::mat4 Scale;
	glm::mat4 Rotate;
	glm::mat4 Trans;

	Trans = glm::translate(Unit, glm::vec3(0, 0.5, 0));		// 일단 위로 올려서 계산 시작한다. 마지막에 1 내리는 거 필요.

	Change = Trans;

	Scale = glm::scale(Unit, glm::vec3(0.3, 0.55, 0.3));	// 다리길이 0.55, 너비 0.3

	Change = Scale * Change;

	Trans = glm::translate(Unit, glm::vec3(0, -0.55f, 0));
	Change = Trans * Change;				//흔들기 위해 위쪽을 원점으로 맞춰줌 + 

	Rotate = glm::rotate(Unit, glm::radians(rotateValue), glm::vec3(LocationX * -1.f, 0, 0));
	Change = Rotate * Change;	//다리 흔드는 모션 해줌

	Trans = glm::translate(Unit, glm::vec3(0, 0.55f, 0));
	Change = Trans * Change;				//다시 위로 올림

	Trans = glm::translate(Unit, glm::vec3(LocationX * 0.2f, 0, LocationZ * 0.6f));
	Change = Trans * Change;	// 내가 원하는 위치(왼쪽 오른쪽), 앞 뒤

	Trans = glm::translate(Unit, glm::vec3(0,-1,0));
	Change = Trans * Change;	// 한칸 내려줌: 탑미들이 중앙이기 때문

	Rotate = glm::rotate(Unit, glm::radians(Direction), glm::vec3(0, 1, 0));
	Change = Rotate * Change;	// 진행방향으로 회전

	Trans = glm::translate(Unit, Position);
	Change = Trans * Change;	// 내 위치로 이동


}
