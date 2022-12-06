#include "CWorld.h"

CWorld::CWorld() : Player{ CPlayer{glm::vec3(0.f, 2.f, 0.f)} }, PlayerPos{ glm::vec3(0.f, 2.f, 0.f) },
isUp{ false }, isDown{ false }, isLeft{ false }, isRight{ false }, isJump{ 0 }, personView{ 1 },
planToCreateObj{ 기본흙 },
VELOCITY{ 0 }, first_VEL{ 25 }, MASS{ 10 }
{
	Initialize();
}

void CWorld::Keyboard(unsigned char key, int state)
{
	switch (state) {
	case GLUT_DOWN:
		switch (key) {					//뭐 생성할지도 정해줌
			// 무기
		case '1':
			Player.setWeapon(맨손);
			break;
		case '2':
			Player.setWeapon(칼);
			break;
		case '3':
			Player.setWeapon(가위);
			break;
		case '4':
			Player.setWeapon(곡괭이);
			break;
		case '9':
			Player.setWeapon(최강무기);
			break;

			// 블록
		case 'u':
			planToCreateObj = 기본흙;
			break;
		case 'i':
			planToCreateObj = 잔디흙;
			break;
		case 'o':
			planToCreateObj = 벼;
			break;
		case 'j':
			planToCreateObj = 양털;
			break;
			/*case 'k':
				planToCreateObj = ;
				break;
			case 'l':
				planToCreateObj = ;
				break;*/
		case 'm':
			planToCreateObj = 나무;
			break;
		case ',':
			planToCreateObj = 나무줄기;
			break;
		case '.':
			planToCreateObj = 나뭇잎;
			break;


			// 동물
		case 'z':
			planToCreateObj = 돼지;
			break;
		case 'x':
			planToCreateObj = 소;
			break;
		case 'c':
			planToCreateObj = 닭;
			break;
		case 'v':
			planToCreateObj = 양;
			break;
		case 'b':
			planToCreateObj = 무너양;
			break;

			//시점
		case 'f':
			personView = 1;
			break;
		case 't':
			personView = 3;
			break;

			// 이동
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
		case ' ':
			if (isJump == 0)
				isJump = 1;
			else if (isJump == 3)
				isJump = 2;
			break;
		case 27:		//Esc버튼
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
		// 카메라 변환
		glm::vec3 DirectionPos{ 0, 0, -5.f };				//카메라 방향 원본
		glm::mat4 cameraDirRot = glm::rotate(glm::mat4(1.f), glm::radians(-MouseAngle.first), glm::vec3(0.f, 1.f, 0.f));
		cameraDirRot = glm::rotate(cameraDirRot, glm::radians(-MouseAngle.second), glm::vec3(1.f, 0.f, 0.f));
		DirectionPos = cameraDirRot * glm::vec4(DirectionPos, 1.f);

		glm::vec3 cPos = glm::vec3(0, 0, -0.25);
		cPos = glm::rotate(glm::mat4(1.f), glm::radians(-MouseAngle.first), glm::vec3(0.f, 1.f, 0.f)) * glm::vec4(cPos, 1.f);

		cameraPos = glm::vec3(PlayerPos.x + cPos.x, PlayerPos.y - 0.4f, PlayerPos.z + cPos.z); //--- 카메라 위치 (어디서 볼건지)
		cameraDirection = PlayerPos + DirectionPos; //--- 카메라 바라보는 방향 (어디볼건지 하면될듯)
		glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //--- 카메라 위쪽 방향->벡터임(방향만) (음수하면 화면 상하거꾸로보임)

		glm::mat4 view = glm::lookAt(cameraPos, cameraDirection, cameraUp);// *cameraRevolution;

		GLuint viewLocation = glGetUniformLocation(shaderID, "viewTransform"); //--- 뷰잉 변환 설정
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));

		// fragment 쉐이더로 넘어가는 카메라 좌표(조명계산용)
		GLuint viewPosLocation = glGetUniformLocation(shaderID, "viewPos");		//--- viewPos 값 전달: 카메라 위치
		glUniform3f(viewPosLocation, cameraPos.x, cameraPos.y, cameraPos.z);
	}
	else if (3 == personView) {
		// 카메라 변환
		glm::vec3 DirectionPos{ 0, 0, -5.f };				//카메라 방향 원본
		glm::mat4 cameraDirRot = glm::rotate(glm::mat4(1.f), glm::radians(-MouseAngle.first), glm::vec3(0.f, 1.f, 0.f));
		cameraDirRot = glm::rotate(cameraDirRot, glm::radians(-MouseAngle.second), glm::vec3(1.f, 0.f, 0.f));
		DirectionPos = cameraDirRot * glm::vec4(DirectionPos, 1.f);

		glm::vec3 cPos = glm::vec3(0, 0, -0.25);
		cPos = glm::rotate(glm::mat4(1.f), glm::radians(-MouseAngle.first), glm::vec3(0.f, 1.f, 0.f)) * glm::vec4(cPos, 1.f);

		cameraPos = glm::vec3(PlayerPos.x + cPos.x, PlayerPos.y - 0.4f, PlayerPos.z + cPos.z); //--- 카메라 위치 (어디서 볼건지)
		cameraDirection = PlayerPos + DirectionPos; //--- 카메라 바라보는 방향 (어디볼건지 하면될듯)
		glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //--- 카메라 위쪽 방향->벡터임(방향만) (음수하면 화면 상하거꾸로보임)

		glm::mat4 view = glm::translate(glm::mat4(1.f), glm::vec3(0, -1, -5)) * glm::lookAt(cameraPos, cameraDirection, cameraUp);// *cameraRevolution;

		GLuint viewLocation = glGetUniformLocation(shaderID, "viewTransform"); //--- 뷰잉 변환 설정
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));

		// fragment 쉐이더로 넘어가는 카메라 좌표(조명계산용)
		GLuint viewPosLocation = glGetUniformLocation(shaderID, "viewPos");		//--- viewPos 값 전달: 카메라 위치
		glUniform3f(viewPosLocation, cameraPos.x, cameraPos.y, cameraPos.z);
	}
}

void CWorld::Gravity()
{
	double F;
	static int time{ 0 };

	if (1 == isJump) {
		isJump = 3;
		++time;
		VELOCITY = first_VEL;
	}
	else if (2 == isJump) {
		isJump = 4;
		++time;
		VELOCITY = first_VEL;
	}

	if (time != 0)
		++time;

	if (VELOCITY > 0) {
		F = MASS * VELOCITY * VELOCITY;
	}
	else
		F = -MASS * VELOCITY * VELOCITY;

	if (time >= 39 || 0 == time) {
		float PlayerBottomPos = Player.getBottom() + F / 50000.f;

		for (int i = 0; i < 4; ++i) {
			float dx, dz;
			switch (i)
			{
			case 0:
				dx = 0.25f;
				dz = 0.25f;
				break;
			case 1:
				dx = 0.25f;
				dz = -0.25f;
				break;
			case 2:
				dx = -0.25f;
				dz = 0.25f;
				break;
			case 3:
				dx = -0.25f;
				dz = -0.25f;
				break;
			}
			glm::vec3 tempPos(round(PlayerPos.x + dx), ceil(PlayerBottomPos), round(PlayerPos.z + dz));
			CBase tempBlock(tempPos);

			auto tmp = Objects.find(&tempBlock);
			if (tmp != Objects.end()) {
				VELOCITY = 0;
				PlayerPos.y = floor(Player.getTop());
				isJump = 0;
				time = 0;
				return;
			}
		}
	}

	PlayerPos.y += F / 50000.f;

	VELOCITY -= 1;

	//cout << PlayerPos.y << endl;
}

void CWorld::Move()
{
	float speed = 0.075f;

	float SinValue = glm::sin(glm::radians(MouseAngle.first));
	float CosValue = glm::cos(glm::radians(MouseAngle.first));

	// 충돌처리 후 이동
	if (isUp) {
		bool isCollide{ false };
		for (int i = 0; i < 4; ++i) {
			float dx, dz;
			switch (i)
			{
			case 0:
				dx = 0.25f;
				dz = 0.25f;
				break;
			case 1:
				dx = 0.25f;
				dz = -0.25f;
				break;
			case 2:
				dx = -0.25f;
				dz = 0.25f;
				break;
			case 3:
				dx = -0.25f;
				dz = -0.25f;
				break;
			}
			CBase tmpU(glm::vec3(round(PlayerPos.x + dx + SinValue * speed), round(PlayerPos.y), round(PlayerPos.z + dz - CosValue * speed)));
			CBase tmpU2(glm::vec3(round(PlayerPos.x + dx + SinValue * speed), round(PlayerPos.y - 1.f), round(PlayerPos.z + dz - CosValue * speed)));
			if (Objects.find(&tmpU) != Objects.end()) {
				isCollide = true;
				break;
			}
			if (Objects.find(&tmpU2) != Objects.end()) {
				isCollide = true;
				break;
			}
		}
		if (not isCollide) {
			PlayerPos.x += SinValue * speed;
			PlayerPos.z -= CosValue * speed;
		}
	}
	if (isDown) {
		bool isCollide{ false };
		for (int i = 0; i < 4; ++i) {
			float dx, dz;
			switch (i)
			{
			case 0:
				dx = 0.25f;
				dz = 0.25f;
				break;
			case 1:
				dx = 0.25f;
				dz = -0.25f;
				break;
			case 2:
				dx = -0.25f;
				dz = 0.25f;
				break;
			case 3:
				dx = -0.25f;
				dz = -0.25f;
				break;
			}
			CBase tmpD(glm::vec3(round(PlayerPos.x + dx - SinValue * speed), round(PlayerPos.y), round(PlayerPos.z + dz + CosValue * speed)));
			CBase tmpD2(glm::vec3(round(PlayerPos.x + dx - SinValue * speed), round(PlayerPos.y - 1.f), round(PlayerPos.z + dz + CosValue * speed)));
			if (Objects.find(&tmpD) != Objects.end()) {
				isCollide = true;
				break;
			}
			if (Objects.find(&tmpD2) != Objects.end()) {
				isCollide = true;
				break;
			}
		}
		if (not isCollide) {
			PlayerPos.x -= SinValue * speed;
			PlayerPos.z += CosValue * speed;
		}
	}
	if (isLeft) {
		bool isCollide{ false };
		for (int i = 0; i < 4; ++i) {
			float dx, dz;
			switch (i)
			{
			case 0:
				dx = 0.25f;
				dz = 0.25f;
				break;
			case 1:
				dx = 0.25f;
				dz = -0.25f;
				break;
			case 2:
				dx = -0.25f;
				dz = 0.25f;
				break;
			case 3:
				dx = -0.25f;
				dz = -0.25f;
				break;
			}
			CBase tmpL(glm::vec3(round(PlayerPos.x + dx - CosValue * speed), round(PlayerPos.y), round(PlayerPos.z + dz - SinValue * speed)));
			CBase tmpL2(glm::vec3(round(PlayerPos.x + dx - CosValue * speed), round(PlayerPos.y - 1.f), round(PlayerPos.z + dz - SinValue * speed)));
			if (Objects.find(&tmpL) != Objects.end()) {
				isCollide = true;
				break;
			}
			if (Objects.find(&tmpL2) != Objects.end()) {
				isCollide = true;
				break;
			}
		}
		if (not isCollide) {
			PlayerPos.x -= CosValue * speed;
			PlayerPos.z -= SinValue * speed;
		}
	}
	if (isRight) {
		bool isCollide{ false };
		for (int i = 0; i < 4; ++i) {
			float dx, dz;
			switch (i)
			{
			case 0:
				dx = 0.25f;
				dz = 0.25f;
				break;
			case 1:
				dx = 0.25f;
				dz = -0.25f;
				break;
			case 2:
				dx = -0.25f;
				dz = 0.25f;
				break;
			case 3:
				dx = -0.25f;
				dz = -0.25f;
				break;
			}
			CBase tmpR(glm::vec3(round(PlayerPos.x + dx + CosValue * speed), round(PlayerPos.y), round(PlayerPos.z + dz + SinValue * speed)));
			CBase tmpR2(glm::vec3(round(PlayerPos.x + dx + CosValue * speed), round(PlayerPos.y - 1.f), round(PlayerPos.z + dz + SinValue * speed)));
			if (Objects.find(&tmpR) != Objects.end()) {
				isCollide = true;
				break;
			}
			if (Objects.find(&tmpR2) != Objects.end()) {
				isCollide = true;
				break;
			}
		}
		if (not isCollide) {
			PlayerPos.x += CosValue * speed;
			PlayerPos.z += SinValue * speed;
		}
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
			case 기본흙:
				Objects.insert(new CBase(tempPos));
				break;
			case 잔디흙:
				Objects.insert(new CGrass(tempPos));
				break;
				//case 벼:
				//	Objects.insert(new CBase(tempPos));
				//	break;
				//case 양털:
				//	Objects.insert(new CBase(tempPos));
				//	break;

			case 나무:
				MakeTree(tempPos);
				break;
			case 나무줄기:
				Objects.insert(new CTreeTrunk(tempPos));
				break;
			case 나뭇잎:
				Objects.insert(new CLeaves(tempPos));
				break;


			case 돼지:
				Objects.insert(new CPig(tempPos));
				break;
			case 소:
				Objects.insert(new CCow(tempPos));
				break;
			case 닭:
				Objects.insert(new CChicken(tempPos));
				break;
			case 양:
				Objects.insert(new CSheep(tempPos));
				break;
			case 무너양:
				Objects.insert(new CSheepNOTUL(tempPos));
				break;

			}
			break;
		}
	}
}



void CWorld::Initialize()
{
	// 바닥
	for (int i = -25; i <= 24; ++i)
		for (int j = -25; j <= 24; ++j)
			Objects.insert(new CGrass{ glm::vec3{i, 0, j} });
	// 바닥 아래
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
	if (mouseL_On) {										// 누르고 있으면 공격
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

	Gravity();												// 자유낙하 + 점프

	Move();													// 키 입력에 따른 충돌처리가 된 이동

	if (isUp || isDown || isLeft || isRight || isJump)
		Player.Update();

	Player.Update(PlayerPos);
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
			if (!(i == -2 && j == -2) && !(i == -2 && j == 2) && !(i == 2 && j == 2) && !(i == 2 && j == -2))
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

	Objects.insert(new CLeaves{ glm::vec3(x ,y + 6,z) });


}
