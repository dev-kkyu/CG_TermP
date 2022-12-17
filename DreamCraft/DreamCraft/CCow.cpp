#include "CCow.h"
#include "CWorld.h"
extern CWorld World;

CCow::CCow(glm::vec3 Position, Form animalForm) 
	: CAnimal{ Position , animalForm, �� },
	Head{ AnimalHead(Position, ��) }, Body{AnimalBody{Position, ��}},
	Leg1{AnimalLeg{Position, -1, -1, ��}},
	Leg2{AnimalLeg{Position, -1, 1, ��}},
	Leg3{AnimalLeg{Position, 1, -1, ��}},
	Leg4{AnimalLeg{Position, 1, 1, ��}}
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
	else if (animalForm == Form::item) {		// ���� ����

		glBindVertexArray(BlockVAO);

		GLuint selectColorLocation = glGetUniformLocation(shaderID, "selectColor");	//--- �ؽ�ó ���
		glUniform1i(selectColorLocation, 1);

		GLuint modelLocation = glGetUniformLocation(shaderID, "modelTransform");
		// animal �� �����ڿ��� change�� ��������ش�.
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Change)); //--- modelTransform ������ ��ȯ �� �����ϱ�
		
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
