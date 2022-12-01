#include "CSheep.h"

#include "CWorld.h"
extern CWorld World;

CSheep::CSheep(glm::vec3 Position) : CAnimal{ Position }
{
}

CSheep::~CSheep()
{
}

void CSheep::Release()
{
}

void CSheep::Render()
{
	

	if (hold_Scissors || hairless) {
		glBindVertexArray(BlockVAO);

		GLuint Color = glGetUniformLocation(shaderID, "objectColor");
		//glUniform3f(Color, this->Color.r, this->Color.g, this->Color.b);
		glUniform3f(Color, 1, 1, 1);

		GLuint modelLocation = glGetUniformLocation(shaderID, "modelTransform");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Change)); //--- modelTransform 변수에 변환 값 적용하기

		glDrawArrays(GL_TRIANGLES, 0, 36);

		if (!hairless) {
			hairless = true;
			this->Hp++;
		}

		////auto getObject();
		//auto itrTemp = World.Objects.find(this);
		//if (itrTemp != World.Objects.end()) {
		//	//World.Objects.erase(itrTemp);
		//	getPosition();
		//	delete (*itrTemp);
		//	**itrTemp = new 
		//}
	}
	else if (!hairless) {
		glBindVertexArray(BlockVAO);

		GLuint Color = glGetUniformLocation(shaderID, "objectColor");
		glUniform3f(Color, this->Color.r, this->Color.g, this->Color.b);

		GLuint modelLocation = glGetUniformLocation(shaderID, "modelTransform");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Change)); //--- modelTransform 변수에 변환 값 적용하기

		glDrawArrays(GL_TRIANGLES, 0, 36);

		

	}
}
