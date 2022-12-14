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
	World.died_Objects.insert(new CSheep{ Position, Form::item , 양});
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

	//static int time = 0;
	//if (Attacked /* && playerWeapon != 가위*/) {
	//	Color = glm::vec3(1, 0, 0);
	//	if (time > 20) {
	//		time = 0;
	//		Attacked = false;
	//	}
	//	else
	//		++time;
	//}
	//else
	//	Color = origin_Color;
}

void CSheep::Render()
{
	if (animalForm == Form::creature) {
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

			Head.setType(무너양);
			Body.setType(무너양);
			Leg1.setType(무너양);
			Leg2.setType(무너양);
			Leg3.setType(무너양);
			Leg4.setType(무너양);

			// 양털아이템 블럭 생성
			World.died_Objects.insert(new CSheep{ Position, Form::item, 양털아이템 });
			//Wool = true;					// 양털 생성하는 변수 on
			//Wool_Position = Position;		// 양털이 깎인 위치 저장

			this->Color = glm::vec3(1, 1, 1);
			origin_Color = this->Color;

		}
		else if (hairless) {					// 털 없을때 그리는거
			//glBindVertexArray(BlockVAO);

			//GLuint selectColorLocation = glGetUniformLocation(shaderID, "selectColor");	//--- 텍스처 사용
			//glUniform1i(selectColorLocation, 1);

			//GLuint modelLocation = glGetUniformLocation(shaderID, "modelTransform");
			//glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Change)); //--- modelTransform 변수에 변환 값 적용하기

			//for (int i = 0; i < 6; ++i) {
			//	glBindTexture(GL_TEXTURE_2D, Texture[4]);
			//	glDrawArrays(GL_TRIANGLES, i * 6, 6);
			//}
			Head.Render();
			Body.Render();
			Leg1.Render();
			Leg2.Render();
			Leg3.Render();
			Leg4.Render();

		}
		else if (!hairless) {					// 평소 그리는거
			Head.Render();
			Body.Render();
			Leg1.Render();
			Leg2.Render();
			Leg3.Render();
			Leg4.Render();
			//glBindVertexArray(BlockVAO);

			//GLuint selectColorLocation = glGetUniformLocation(shaderID, "selectColor");	//--- 텍스처 사용
			//glUniform1i(selectColorLocation, 1);

			//GLuint modelLocation = glGetUniformLocation(shaderID, "modelTransform");
			//glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Change)); //--- modelTransform 변수에 변환 값 적용하기

			//for (int i = 0; i < 6; ++i) {
			//	glBindTexture(GL_TEXTURE_2D, Texture[3]);
			//	glDrawArrays(GL_TRIANGLES, i * 6, 6);
			//}
		}
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

	//if (Wool) {		// 양털 드랍

	//	glBindVertexArray(BlockVAO);

	//	GLuint selectColorLocation = glGetUniformLocation(shaderID, "selectColor");	//--- 텍스처 사용
	//	glUniform1i(selectColorLocation, 1);

	//	glm::mat4 Trans;
	//	glm::mat4 Scale;

	//	Trans = glm::translate(Unit, Wool_Position);
	//	Scale = glm::scale(Unit, glm::vec3(0.5, 0.5, 0.5));

	//	glm::mat4 Change_Wool = Trans * Scale;

	//	GLuint model = glGetUniformLocation(shaderID, "modelTransform");
	//	glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(Change_Wool));

	//	for (int i = 0; i < 6; ++i) {
	//		glBindTexture(GL_TEXTURE_2D, Texture[3]);
	//		glDrawArrays(GL_TRIANGLES, i * 6, 6);
	//	}
	//}
}
