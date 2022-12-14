#include "CChicken.h"

#include "CWorld.h"
extern CWorld World;

CChicken::CChicken(glm::vec3 Position, Form animalForm)
	: CAnimal{ Position, animalForm, 닭 },
	Head{ CChickenHead{Position} }, Body{ CChickenBody{Position} }, Leg1{ CChickenLeg{Position, -1} }, Leg2{ CChickenLeg{Position, 1} }
{
}

CChicken::~CChicken()
{
	Release();
}

void CChicken::Release()
{
	World.died_Objects.insert(new CChicken{ Position, Form::item });
}

void CChicken::Update()
{
	FixedUpdate();

	Head.setPos(float_Position, animal_Direction);
	Body.setPos(float_Position, animal_Direction);
	Leg1.setPos(float_Position, animal_Direction);
	Leg2.setPos(float_Position, animal_Direction);

	Head.Update();
	Body.Update();
	Leg1.Update();
	Leg2.Update();
}

void CChicken::Render()
{


	if (animalForm == Form::creature) {
		Head.Render();
		Body.Render();
		Leg1.Render();
		Leg2.Render();
	}
	else if (animalForm == Form::item) {		// 동물 죽음

		glBindVertexArray(BlockVAO);

		GLuint selectColorLocation = glGetUniformLocation(shaderID, "selectColor");	//--- 텍스처 사용
		glUniform1i(selectColorLocation, 1);

		GLuint modelLocation = glGetUniformLocation(shaderID, "modelTransform");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Change)); //--- modelTransform 변수에 변환 값 적용하기

		//for (int i = 0; i < 6; ++i) {
		//	glBindTexture(GL_TEXTURE_2D, Texture[20]);		// 닭머리귀엽당
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
