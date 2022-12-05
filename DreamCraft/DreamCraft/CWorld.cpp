#include "CWorld.h"

CWorld::CWorld() : Player{ CPlayer{glm::vec3(0.f, 2.f, 0.f)} }, PlayerPos{ glm::vec3(0.f, 2.f, 0.f) },
isUp{ false }, isDown{ false }, isLeft{ false }, isRight{ false }, isJump{ 0 }, personView{ 1 },
planToCreateObj{ �⺻���� },
first_VEL{ 25 }, MASS{ 10 }
{
	VELOCITY = first_VEL;
	Initialize();
}

void CWorld::Keyboard(unsigned char key, int state)
{
	switch (state) {
	case GLUT_DOWN:
		switch (key) {					//�� ���������� ������
			// ����
		case '1':
			Player.setWeapon(�Ǽ�);
			break;
		case '2':
			Player.setWeapon(Į);
			break;
		case '3':
			Player.setWeapon(����);
			break;
		case '4':
			Player.setWeapon(���);
			break;
		case '9':
			Player.setWeapon(�ְ�����);
			break;

			// ����
		case 'u':
			planToCreateObj = �⺻��;
			break;
		case 'i':
			planToCreateObj = �ܵ���;
			break;
		case 'o':
			planToCreateObj = ��;
			break;
		case 'j':
			planToCreateObj = ����;
			break;
		/*case 'k':
			planToCreateObj = ;
			break;
		case 'l':
			planToCreateObj = ;
			break;*/
		case 'm':
			planToCreateObj = ����;
			break;
		case ',':
			planToCreateObj = �����ٱ�;
			break;
		case '.':
			planToCreateObj = ������;
			break;


			// ����
		case 'z':
			planToCreateObj = ����;
			break;
		case 'x':
			planToCreateObj = ��;
			break;
		case 'c':
			planToCreateObj = ��;
			break;
		case 'v':
			planToCreateObj = ��;
			break;
		case 'b':
			planToCreateObj = ���ʾ�;
			break;

			//����
		case 'f':
			personView = 1;
			break;
		case 't':
			personView = 3;
			break;

			// �̵�
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
		//case 'j':
		//case 'J':
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
		case GLUT_LEFT_BUTTON:
			mouseL_On = true;
			break;
		case GLUT_RIGHT_BUTTON:
			addNewObject(planToCreateObj);
			break;
		}
		break;
	case GLUT_UP:
		switch (button) {
		case GLUT_LEFT_BUTTON:
			mouseL_On = false;
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

		// fragment ���̴��� �Ѿ�� ī�޶� ��ǥ(��������)
		GLuint viewPosLocation = glGetUniformLocation(shaderID, "viewPos");		//--- viewPos �� ����: ī�޶� ��ġ
		glUniform3f(viewPosLocation, cameraPos.x, cameraPos.y, cameraPos.z);




	}
	else if (3 == personView) {
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

		glm::mat4 view = glm::translate(glm::mat4(1.f), glm::vec3(0, -1, -5)) * glm::lookAt(cameraPos, cameraDirection, cameraUp);// *cameraRevolution;

		GLuint viewLocation = glGetUniformLocation(shaderID, "viewTransform"); //--- ���� ��ȯ ����
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));

		// fragment ���̴��� �Ѿ�� ī�޶� ��ǥ(��������)
		GLuint viewPosLocation = glGetUniformLocation(shaderID, "viewPos");		//--- viewPos �� ����: ī�޶� ��ġ
		glUniform3f(viewPosLocation, cameraPos.x, cameraPos.y, cameraPos.z);
	}
}

void CWorld::Jump()
{
	double F;

	if (isJump == 2) {
		isJump = 3;
		VELOCITY = first_VEL;
	}

	if (VELOCITY > 0) {
		F = MASS * VELOCITY * VELOCITY;
	}
	else
		F = -MASS * VELOCITY * VELOCITY;

	PlayerPos.y += F / 50000.f;

	VELOCITY -= 1;

	if (PlayerPos.y <= 2.f) {
		VELOCITY = first_VEL;
		PlayerPos.y = 2.f;
		isJump = false;
	}
	cout << PlayerPos.y << endl;
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

void CWorld::addNewObject(int ObjectType)
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
			switch (ObjectType) {
			case �⺻��:
				Objects.insert(new CBase(tempPos));
				break;
			case �ܵ���:
				Objects.insert(new CGrass(tempPos));
				break;
			//case ��:
			//	Objects.insert(new CBase(tempPos));
			//	break;
			//case ����:
			//	Objects.insert(new CBase(tempPos));
			//	break;

			case ����:
				 MakeTree(tempPos);
				break;
			case �����ٱ�:
				Objects.insert(new CTreeTrunk(tempPos));
				break;
			case ������:
				Objects.insert(new CLeaves(tempPos));
				break;


			case ����:
				Objects.insert(new CPig(tempPos));
				break;
			case ��:
				Objects.insert(new CCow(tempPos));
				break;
			case ��:
				Objects.insert(new CChicken(tempPos));
				break;
			case ��:
				Objects.insert(new CSheep(tempPos));
				break;
			case ���ʾ�:
				Objects.insert(new CSheepNOTUL(tempPos));
				break;
			
			}
			break;
		}
	}
}



void CWorld::Initialize()
{
	// �ٴ�
	for (int i = -25; i <= 24; ++i)
		for (int j = -25; j <= 24; ++j)
			Objects.insert(new CGrass{ glm::vec3{i, 0, j} });
	// �ٴ� �Ʒ�
	for (int k = -1; k > -5; --k)
		for (int i = -25; i <= 24; ++i)
			for (int j = -25; j <= 24; ++j)
				Objects.insert(new CBase{ glm::vec3{i, k, j} });

	Objects.insert(new CSheep{ glm::vec3(3,1,3) });
	Objects.insert(new CPig{ glm::vec3(-3,1,3) });
	Objects.insert(new CCow{ glm::vec3(5,1,-3) });
	Objects.insert(new CChicken{ glm::vec3(3,1,-6) });




}

void CWorld::Update()
{
	for (auto Object : Objects) {
		Object->Update();
	}

	static int time = 0;
	if (mouseL_On) {
		if (0 == time) {
			auto temp = getObject();
			if (temp != Objects.end()) {
				(*temp)->be_Attacked(Player.getWeapon());
				if ((*temp)->isDead()) {
					delete (*temp);
					Objects.erase(temp);
				}
			}
			time = 1;
		}
		else
			time = (time + 1) % 20;
	}
	else {
		time = 0;
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
		Jump();
	}
	if (isUp || isDown || isLeft || isRight || isJump)
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

int CWorld::getpersonView()
{
	return personView;
}

void CWorld::MakeTree(glm::vec3 position)
{
	float x{ position.x }, y{ position.y }, z{ position.z };

	for (int i = 0; i < 3; ++i)
		Objects.insert(new CTreeTrunk{ glm::vec3(x,y + i,z) });

	for (int i = -1; i < 2; ++i) {
		if (i != 0) {
			Objects.insert(new CLeaves{ glm::vec3(x + i,y + 2,z) });
			Objects.insert(new CLeaves{ glm::vec3(x,y + 2,z + i) });
		}
	}

	Objects.insert(new CLeaves{ glm::vec3(x + 1,y + 2,z + 1) });

	for (int i = -2; i < 3; ++i) {
		for (int j = -2; j < 3; ++j) {
			if (!(i == -2 && j == -2)&& !(i == -2 && j == 2) && !(i == 2 && j == 2) && !(i == 2 && j == -2))
				Objects.insert(new CLeaves{ glm::vec3(x + i,y + 3,z + j) });
		}
	}


	for (int i = -1; i < 2; ++i) {
		for (int j = -1; j < 2; ++j) {
			if (!(i == 1 && j == 1))
			Objects.insert(new CLeaves{ glm::vec3(x + i,y + 4,z + j) });
		}
	}

	Objects.insert(new CLeaves{ glm::vec3(x ,y + 5,z) });
	Objects.insert(new CLeaves{ glm::vec3(x ,y + 5,z + 1) });

	Objects.insert(new CLeaves{ glm::vec3(x ,y + 6,z ) });


}

