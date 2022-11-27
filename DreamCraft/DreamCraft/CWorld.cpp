#include "CWorld.h"

CWorld::CWorld() : Player{ CPlayer{glm::vec3(0.f)} }, PlayerPos{ glm::vec3(0.f) },
	isUp{ false }, isDown{ false }, isLeft{ false }, isRight{ false }, isJump{ false }, personView{ 1 }
{
	Initialize();
}

void CWorld::Keyboard(unsigned char key, int state)
{
	switch (state) {
	case GLUT_DOWN:
		switch (key) {
		case '1':
			personView = 1;
			break;
		case '3':
			personView = 3;
			break;
		case 'w':
		case 'W':
			isUp = true;
			break;
		case 'a':
		case 'A':
			isLeft = true;
			break;
		case 's':
		case 'S':
			isDown = true;
			break;
		case 'd':
		case 'D':
			isRight = true;
			break;
		case 'j':
		case 'J':
		case ' ':
			if (isJump != 2) {
				++isJump;
			}
			break;
		case 27:		//Esc��ư
			glutLeaveMainLoop();
			break;
		default:
			break;
		}
		break;
	case GLUT_UP:
		switch (key) {
		case 'w':
		case 'W':
			isUp = false;
			break;
		case 'a':
		case 'A':
			isLeft = false;
			break;
		case 's':
		case 'S':
			isDown = false;
			break;
		case 'd':
		case 'D':
			isRight = false;
			break;
		}
		break;
	}
}

void CWorld::SpecialKeyboard(int key, int state)
{
	switch (state) {
	case GLUT_DOWN:
		switch (key) {
		case GLUT_KEY_F5:
			glutFullScreenToggle();
			break;
		case GLUT_KEY_LEFT:
			isLeft = true;
			break;
		case GLUT_KEY_RIGHT:
			isRight = true;
			break;
		case GLUT_KEY_UP:
			isUp = true;
			break;
		case GLUT_KEY_DOWN:
			isDown = true;
			break;
		}
		break;
	case GLUT_UP:
		switch (key) {
		case GLUT_KEY_LEFT:
			isLeft = false;
			break;
		case GLUT_KEY_RIGHT:
			isRight = false;
			break;
		case GLUT_KEY_UP:
			isUp = false;
			break;
		case GLUT_KEY_DOWN:
			isDown = false;
			break;
		}
		break;
	}
}

void CWorld::Mouse(int button, int state)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
	getObject();
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {

	}
}


void CWorld::Camera(int personView)
{
	if (1 == personView) {
		// ī�޶� ��ȯ
		glm::vec3 DirectionPos{ 0, 1.5f, -5.f };				//ī�޶� ���� ����
		glm::mat4 cameraDirRot = glm::rotate(glm::mat4(1.f), glm::radians(-MouseAngle.first), glm::vec3(0.f, 1.f, 0.f));
		cameraDirRot = glm::rotate(cameraDirRot, glm::radians(-MouseAngle.second), glm::vec3(1.f, 0.f, 0.f));
		DirectionPos = cameraDirRot * glm::vec4(DirectionPos, 1.f);

		cameraPos = glm::vec3(PlayerPos.x, PlayerPos.y + 1.5f, PlayerPos.z); //--- ī�޶� ��ġ (��� ������)
		cameraDirection = glm::vec3(PlayerPos.x + DirectionPos.x, PlayerPos.y + DirectionPos.y, PlayerPos.z + DirectionPos.z); //--- ī�޶� �ٶ󺸴� ���� (��𺼰��� �ϸ�ɵ�)
		glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //--- ī�޶� ���� ����->������(���⸸) (�����ϸ� ȭ�� ���ϰŲٷκ���)

		glm::mat4 view = glm::lookAt(cameraPos, cameraDirection, cameraUp);// *cameraRevolution;

		GLuint viewLocation = glGetUniformLocation(shaderID, "viewTransform"); //--- ���� ��ȯ ����
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));

		// fragment ���̴��� �Ѿ�� ī�޶� ��ǥ(�������)
		GLuint viewPosLocation = glGetUniformLocation(shaderID, "viewPos");		//--- viewPos �� ����: ī�޶� ��ġ
		glUniform3f(viewPosLocation, cameraPos.x, cameraPos.y, cameraPos.z);
	}
	else if (3 == personView) {
		// ī�޶� ��ȯ
		glm::vec3 DirectionPos{ 0, 1.8, -5.f };				//ī�޶� ���� ����
		glm::mat4 cameraDirRot = glm::rotate(glm::mat4(1.f), glm::radians(-MouseAngle.first), glm::vec3(0.f, 1.f, 0.f));
		cameraDirRot = glm::rotate(cameraDirRot, glm::radians(-MouseAngle.second), glm::vec3(1.f, 0.f, 0.f));
		DirectionPos = cameraDirRot * glm::vec4(DirectionPos, 1.f);

		cameraPos = glm::vec3(PlayerPos.x, PlayerPos.y + 1.8f, PlayerPos.z); //--- ī�޶� ��ġ (��� ������)
		cameraDirection = glm::vec3(PlayerPos.x + DirectionPos.x, PlayerPos.y + DirectionPos.y, PlayerPos.z + DirectionPos.z); //--- ī�޶� �ٶ󺸴� ���� (��𺼰��� �ϸ�ɵ�)
		glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //--- ī�޶� ���� ����->������(���⸸) (�����ϸ� ȭ�� ���ϰŲٷκ���)

		glm::mat4 view = glm::translate(glm::mat4(1.f), glm::vec3(0, -1, -5)) * glm::lookAt(cameraPos, cameraDirection, cameraUp);// *cameraRevolution;

		GLuint viewLocation = glGetUniformLocation(shaderID, "viewTransform"); //--- ���� ��ȯ ����
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));

		// fragment ���̴��� �Ѿ�� ī�޶� ��ǥ(�������)
		GLuint viewPosLocation = glGetUniformLocation(shaderID, "viewPos");		//--- viewPos �� ����: ī�޶� ��ġ
		glUniform3f(viewPosLocation, cameraPos.x, cameraPos.y, cameraPos.z);
	}
}

CGameObject* CWorld::getObject()
{
	glm::vec3 normalDirection = cameraDirection - cameraPos;
	normalDirection = glm::normalize(normalDirection);

	//set<CBlock*, CBlockCmp>::iterator itr;
	for (int i = 1; i < 55; ++i) {
		glm::vec3 temp(cameraPos + (normalDirection * (i / 10.f)));
		temp.x = round(temp.x);
		temp.y = ceil(temp.y);
		temp.z = round(temp.z);
		CBase test(temp);
		auto itr = Blocks.find(&test);
		if (itr != Blocks.end()) {
			(*itr)->show();
			glm::vec3 temps(cameraPos + (normalDirection * ((i - 1) / 10.f)));
			temps.x = round(temps.x);
			temps.y = ceil(temps.y);
			temps.z = round(temps.z);
			Blocks.insert(new CBase(temps));


			return *itr;
		}
	}
	return nullptr;
}



void CWorld::Initialize()
{
	for (int i = -30; i <= 30; ++i) {
		for (int j = -30; j <= 30; ++j) {
			Blocks.insert(new CBase{ glm::vec3{i, 0, j} });
		}
	}
	for (int i = -30; i <= 30; ++i) {
		for (int j = -30; j <= 30; ++j) {
			Blocks.insert(new CBase{ glm::vec3{i, 0, j} });
		}
	}
	Blocks.insert(new CBase{ glm::vec3(-30,1,-30) });
	Blocks.insert(new CBase{ glm::vec3(-30,2,-30) });
	Blocks.insert(new CBase{ glm::vec3(-30,1,-29) });
}

void CWorld::Update()
{
	if (isUp) {
		PlayerPos.x += glm::sin(glm::radians(MouseAngle.first)) * 0.075f;
		PlayerPos.z -= glm::cos(glm::radians(MouseAngle.first)) * 0.075f;
	}
	if (isLeft) {
		PlayerPos.x -= glm::cos(glm::radians(MouseAngle.first)) * 0.075f;
		PlayerPos.z -= glm::sin(glm::radians(MouseAngle.first)) * 0.075f;
	}
	if (isDown) {
		PlayerPos.x -= glm::sin(glm::radians(MouseAngle.first)) * 0.075f;
		PlayerPos.z += glm::cos(glm::radians(MouseAngle.first)) * 0.075f;
	}
	if (isRight) {
		PlayerPos.x += glm::cos(glm::radians(MouseAngle.first)) * 0.075f;
		PlayerPos.z += glm::sin(glm::radians(MouseAngle.first)) * 0.075f;
	}
	if (isJump) {
		;
	}
	Player.Update(PlayerPos);
	Player.Update();
}

void CWorld::FixedUpdate()
{
}

void CWorld::Render()
{
	Camera(personView);

	for (auto Block : Blocks) {
		Block->Render();
	}

	Player.Render();
}

void CWorld::Release()
{
}

