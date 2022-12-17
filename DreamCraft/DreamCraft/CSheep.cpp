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
	World.died_Objects.insert(new CSheep{ Position, Form::item , �� });
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

			hairless = true;				// �� ���� ������ ���ٴ� ���� on

			Head.setType(���ʾ�);
			Body.setType(���ʾ�);
			Leg1.setType(���ʾ�);
			Leg2.setType(���ʾ�);
			Leg3.setType(���ʾ�);
			Leg4.setType(���ʾ�);

			// ���о����� �� ����
			World.died_Objects.insert(new CSheep{ Position, Form::item, ���о����� });
		}

		Head.Render();
		Body.Render();
		Leg1.Render();
		Leg2.Render();
		Leg3.Render();
		Leg4.Render();

	}
	else if (animalForm == Form::item && animalType == ��) {			// ������
		glBindVertexArray(BlockVAO);

		GLuint selectColorLocation = glGetUniformLocation(shaderID, "selectColor");	//--- �ؽ�ó ���
		glUniform1i(selectColorLocation, 1);

		GLuint modelLocation = glGetUniformLocation(shaderID, "modelTransform");
		// animal �� �����ڿ��� change�� ��������ش�.
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Change)); //--- modelTransform ������ ��ȯ �� �����ϱ�

		glBindTexture(GL_TEXTURE_2D, Texture[5]);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glBindTexture(GL_TEXTURE_2D, Texture[5]);
		glDrawArrays(GL_TRIANGLES, 6, 6);

		glBindTexture(GL_TEXTURE_2D, Texture[5]);
		glDrawArrays(GL_TRIANGLES, 18, 6);

		glBindTexture(GL_TEXTURE_2D, Texture[5]);
		glDrawArrays(GL_TRIANGLES, 30, 6);


	}
	else if (animalForm == Form::item && animalType == ���о�����) {			// ���о����۱׸���
		glBindVertexArray(BlockVAO);

		GLuint selectColorLocation = glGetUniformLocation(shaderID, "selectColor");	//--- �ؽ�ó ���
		glUniform1i(selectColorLocation, 1);

		GLuint modelLocation = glGetUniformLocation(shaderID, "modelTransform");
		// animal �� �����ڿ��� change�� ��������ش�.
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Change)); //--- modelTransform ������ ��ȯ �� �����ϱ�

		for (int i = 0; i < 6; ++i) {
			glBindTexture(GL_TEXTURE_2D, Texture[3]);
			glDrawArrays(GL_TRIANGLES, i * 6, 6);
		}

	}
}
