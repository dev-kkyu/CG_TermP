#include "CCow.h"
#include "CWorld.h"
extern CWorld World;

CCow::CCow(glm::vec3 Position, Form animalForm) 
	: CAnimal{ Position , animalForm, 소 },
	Head{ AnimalHead(Position, 소) }, Body{AnimalBody{Position, 소}},
	Leg1{AnimalLeg{Position, -1, -1, 소}},
	Leg2{AnimalLeg{Position, -1, 1, 소}},
	Leg3{AnimalLeg{Position, 1, -1, 소}},
	Leg4{AnimalLeg{Position, 1, 1, 소}}
{
}

CCow::~CCow()
{
	Release();
}

void CCow::Release()
{
	World.died_Objects.insert(new CCow{ Position, Form::item });
}

void CCow::Update()
{
	FixedUpdate();

	Head.setPos(float_Position, animal_Direction);
	Body.setPos(float_Position, animal_Direction);
	Leg1.setPos(float_Position, animal_Direction);
	Leg2.setPos(float_Position, animal_Direction);
	Leg3.setPos(float_Position, animal_Direction);
	Leg4.setPos(float_Position, animal_Direction);

	Head.Update();
	Body.Update();
	Leg1.Update();
	Leg2.Update();
	Leg3.Update();
	Leg4.Update();
}

void CCow::Render()
{
	if (animalForm == Form::creature) {
		Head.Render();
		Body.Render();
		Leg1.Render();
		Leg2.Render();
		Leg3.Render();
		Leg4.Render();
	}
	else if (animalForm == Form::item) {		// 동물 죽음

		glBindVertexArray(BlockVAO);

		GLuint selectColorLocation = glGetUniformLocation(shaderID, "selectColor");	//--- 텍스처 사용
		glUniform1i(selectColorLocation, 1);

		GLuint modelLocation = glGetUniformLocation(shaderID, "modelTransform");
		// animal 의 생성자에서 change를 적용시켜준다.
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Change)); //--- modelTransform 변수에 변환 값 적용하기
		
		glBindTexture(GL_TEXTURE_2D, Texture[9]);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glBindTexture(GL_TEXTURE_2D, Texture[9]);
		glDrawArrays(GL_TRIANGLES, 6, 6);

		glBindTexture(GL_TEXTURE_2D, Texture[9]);
		glDrawArrays(GL_TRIANGLES, 18, 6);

		glBindTexture(GL_TEXTURE_2D, Texture[9]);
		glDrawArrays(GL_TRIANGLES, 30, 6);

	}

}
