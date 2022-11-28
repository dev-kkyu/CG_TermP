#include "CWorld.h"

CWorld::CWorld() : Player{ CPlayer{glm::vec3(0.f, 2.f, 0.f)} }, PlayerPos{ glm::vec3(0.f, 2.f, 0.f) },
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
	switch (state) {
	case GLUT_DOWN:
		switch (button) {
		case GLUT_LEFT_BUTTON: {
			auto temp = getObject();
			if (temp != Objects.end()) {
				delete (*temp);
				Objects.erase(temp);
			}
		}
			break;
		case GLUT_RIGHT_BUTTON:
			newBlock();
			break;
		}
		break;
	case GLUT_UP:
		switch (button) {
		case GLUT_LEFT_BUTTON:
			break;
		case GLUT_RIGHT_BUTTON:
			break;
		}
		break;
	}
}


void CWorld::Camera()
{
	if (1 == personView) {
		// ī�޶� ��ȯ
		glm::vec3 DirectionPos{ 0, 0, -5.f };				//ī�޶� ���� ����
		glm::mat4 cameraDirRot = glm::rotate(glm::mat4(1.f), glm::radians(-MouseAngle.first), glm::vec3(0.f, 1.f, 0.f));
		cameraDirRot = glm::rotate(cameraDirRot, glm::radians(-MouseAngle.second), glm::vec3(1.f, 0.f, 0.f));
		DirectionPos = cameraDirRot * glm::vec4(DirectionPos, 1.f);

		glm::vec3 cPos = glm::vec3(0, 0, -0.25);
		cPos = glm::rotate(glm::mat4(1.f), glm::radians(-MouseAngle.first), glm::vec3(0.f, 1.f, 0.f)) * glm::vec4(cPos, 1.f);

		cameraPos = glm::vec3(PlayerPos.x + cPos.x, PlayerPos.y - 0.4f, PlayerPos.z + cPos.z); //--- ī�޶� ��ġ (��� ������)
		cameraDirection = PlayerPos + DirectionPos; //--- ī�޶� �ٶ󺸴� ���� (��𺼰��� �ϸ�ɵ�)
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

		cameraPos = glm::vec3(PlayerPos.x, PlayerPos.y - 0.2f, PlayerPos.z); //--- ī�޶� ��ġ (��� ������)
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

set<CGameObject*, CGameObjectCmp>::iterator CWorld::getObject()
{
	glm::vec3 normalDirection = cameraDirection - cameraPos;
	normalDirection = glm::normalize(normalDirection);

	for (int i = 1; i < 65; ++i) {
		glm::vec3 tempPos(cameraPos + (normalDirection * (i / 10.f)));
		tempPos.x = round(tempPos.x);
		tempPos.y = ceil(tempPos.y);
		tempPos.z = round(tempPos.z);
		CBase tempBlock(tempPos);
		auto itr = Objects.find(&tempBlock);
		if (itr != Objects.end()) {
			(*itr)->show();
			return itr;
		}
	}
	return Objects.end();
}

void CWorld::newBlock()
{
	glm::vec3 normalDirection = cameraDirection - cameraPos;
	normalDirection = glm::normalize(normalDirection);

	for (int i = 1; i < 65; ++i) {
		glm::vec3 tempPos(cameraPos + (normalDirection * (i / 10.f)));
		tempPos.x = round(tempPos.x);
		tempPos.y = ceil(tempPos.y);
		tempPos.z = round(tempPos.z);
		CBase tempBlock(tempPos);
		auto itr = Objects.find(&tempBlock);
		if (itr != Objects.end()) {
			(*itr)->show();
			tempPos = glm::vec3(cameraPos + (normalDirection * ((i - 1) / 10.f)));
			tempPos.x = round(tempPos.x);
			tempPos.y = ceil(tempPos.y);
			tempPos.z = round(tempPos.z);
			Objects.insert(new CBase(tempPos));
			break;
		}
	}
}



void CWorld::Initialize()
{
	for (int i = -25; i <= 24; ++i) {
		for (int j = -25; j <= 24; ++j) {
			Objects.insert(new CBase{ glm::vec3{i, 0, j} });
		}
	}

	Objects.insert(new CCow{ glm::vec3(3,1,3) });
	Objects.insert(new CCow{ glm::vec3(-3,1,3) });
	Objects.insert(new CCow{ glm::vec3(3,1,-3) });
}

void CWorld::Update()
{
	for (auto Object : Objects) {
		Object->Update();
	}

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
	if (isUp || isDown || isLeft || isRight)
		Player.Update(PlayerPos);
	Player.Update();
}

void CWorld::FixedUpdate()
{
}

void CWorld::Render()
{
	Camera();

	for (auto Object : Objects) {
		Object->Render();
	}

	Player.Render();
}

void CWorld::Release()
{
}

