#include "CSheep.h"

#include "CWorld.h"
extern CWorld World;

CSheep::CSheep(glm::vec3 Position, Form animalForm, int animalType)
	: CAnimal{ Position, animalForm, animalType }, hairless{ false },
	Head{ AnimalHead(Position, animalType) }, Body{ AnimalBody{Position, animalType} },
	Leg1{ AnimalLeg{Position, -1, -1, animalType} },
	Leg2{ AnimalLeg{Position, -1, 1, animalType} },
	Leg3{ AnimalLeg{Position, 1, -1, animalType} },
	Leg4{ AnimalLeg{Position, 1, 1, animalType} }
{
}

CSheep::~CSheep()
{
	Release();
}

void CSheep::Release()
{
	World.died_Objects.insert(new CSheep{ Position, Form::item , 양 });
}

void CSheep::Update()
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

void CSheep::Render()
{
	if (animalForm == Form::creature) {
		if (hold_Scissors && !hairless) {

			hairless = true;				// 털 깎인 양으로 빠꾸는 변수 on

			Head.setType(무너양);
			Body.setType(무너양);
			Leg1.setType(무너양);
			Leg2.setType(무너양);
			Leg3.setType(무너양);
			Leg4.setType(무너양);

			// 양털아이템 블럭 생성
			World.died_Objects.insert(new CSheep{ Position, Form::item, 양털아이템 });
		}

		Head.Render();
		Body.Render();
		Leg1.Render();
		Leg2.Render();
		Leg3.Render();
		Leg4.Render();

	}
	else if (animalForm == Form::item && animalType == 양) {			// 양죽음
		glBindVertexArray(BlockVAO);

		GLuint selectColorLocation = glGetUniformLocation(shaderID, "selectColor");	//--- 텍스처 사용
		glUniform1i(selectColorLocation, 1);

		GLuint modelLocation = glGetUniformLocation(shaderID, "modelTransform");
		// animal 의 생성자에서 change를 적용시켜준다.
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Change)); //--- modelTransform 변수에 변환 값 적용하기

		glBindTexture(GL_TEXTURE_2D, Texture[5]);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glBindTexture(GL_TEXTURE_2D, Texture[5]);
		glDrawArrays(GL_TRIANGLES, 6, 6);

		glBindTexture(GL_TEXTURE_2D, Texture[5]);
		glDrawArrays(GL_TRIANGLES, 18, 6);

		glBindTexture(GL_TEXTURE_2D, Texture[5]);
		glDrawArrays(GL_TRIANGLES, 30, 6);


	}
	else if (animalForm == Form::item && animalType == 양털아이템) {			// 양털아이템그리기
		glBindVertexArray(BlockVAO);

		GLuint selectColorLocation = glGetUniformLocation(shaderID, "selectColor");	//--- 텍스처 사용
		glUniform1i(selectColorLocation, 1);

		GLuint modelLocation = glGetUniformLocation(shaderID, "modelTransform");
		// animal 의 생성자에서 change를 적용시켜준다.
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Change)); //--- modelTransform 변수에 변환 값 적용하기

		for (int i = 0; i < 6; ++i) {
			glBindTexture(GL_TEXTURE_2D, Texture[3]);
			glDrawArrays(GL_TRIANGLES, i * 6, 6);
		}

	}
}
