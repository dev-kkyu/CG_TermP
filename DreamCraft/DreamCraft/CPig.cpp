#include "CPig.h"
#include "CWorld.h"
extern CWorld World;

CPig::CPig(glm::vec3 Position, Form animalForm) 
	: CAnimal{ Position, animalForm, 돼지 },
	Head{ AnimalHead(Position, 돼지) }, Body{ AnimalBody{Position, 돼지} },
	Leg1{ AnimalLeg{Position, -1, -1, 돼지} },
	Leg2{ AnimalLeg{Position, -1, 1, 돼지} },
	Leg3{ AnimalLeg{Position, 1, -1, 돼지} },
	Leg4{ AnimalLeg{Position, 1, 1, 돼지} }
{
}

CPig::~CPig()
{
	Release();
}

void CPig::Release()
{
	World.died_Objects.insert(new CPig{ Position, Form::item });
}

void CPig::Update()
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

void CPig:: Render() {
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

		glBindTexture(GL_TEXTURE_2D, Texture[13]);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glBindTexture(GL_TEXTURE_2D, Texture[13]);
		glDrawArrays(GL_TRIANGLES, 6, 6);

		glBindTexture(GL_TEXTURE_2D, Texture[13]);
		glDrawArrays(GL_TRIANGLES, 18, 6);

		glBindTexture(GL_TEXTURE_2D, Texture[13]);
		glDrawArrays(GL_TRIANGLES, 30, 6);

	}
}