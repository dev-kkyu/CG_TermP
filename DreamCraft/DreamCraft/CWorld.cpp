#include "CWorld.h"

CWorld::CWorld() : Player{ CPlayer{glm::vec3(0.f, 10.f, 0.f)} }, PlayerPos{ glm::vec3(0.f, 10.f, 0.f) },
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

			// 나무
		case 'm':
			planToCreateObj = 나무;
			break;
		case ',':
			planToCreateObj = 나무줄기;
			break;
		case '.':
			planToCreateObj = 나뭇잎;
			break;
		case 'M':
			planToCreateObj = 나무2;
			break;
		case '<':
			planToCreateObj = 나무줄기2;
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
		//case 'b':
		//	planToCreateObj = 무너양;
		//	break;

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

		cameraPos = PlayerPos;						//--- 카메라 위치 (어디서 볼건지)
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
		glm::vec3 cPos{ 0, 0, 7.5f };						// 카메라 위치 원본
		glm::vec3 DirectionPos{ 0, 0, -5.f };				// 카메라 방향 원본

		glm::mat4 cameraDirRot = glm::rotate(glm::mat4(1.f), glm::radians(-MouseAngle.first), glm::vec3(0.f, 1.f, 0.f));
		cameraDirRot = glm::rotate(cameraDirRot, glm::radians(-MouseAngle.second), glm::vec3(1.f, 0.f, 0.f));
		cPos = cameraDirRot * glm::vec4(cPos, 1.f);
		DirectionPos = cameraDirRot * glm::vec4(DirectionPos, 1.f);

		cameraPos = PlayerPos + cPos; //--- 카메라 위치 (어디서 볼건지)
		cameraDirection = PlayerPos + DirectionPos; //--- 카메라 바라보는 방향 (어디볼건지 하면될듯)
		glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //--- 카메라 위쪽 방향->벡터임(방향만) (음수하면 화면 상하거꾸로보임)

		glm::mat4 view = glm::lookAt(cameraPos, cameraDirection, cameraUp);

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


	// item 얻기
	{
		CBase ItemTemp(glm::vec3(round(PlayerPos.x), round(PlayerPos.y - 1), round(PlayerPos.z)));
		auto itr = died_Objects.find(&ItemTemp);
		auto itr2 = mined_Objects.find(&ItemTemp);
		if (itr != died_Objects.end()) {
			switch (((CAnimal*)*itr)->animalType) {
			case 닭:
				++itemCount.Chicken;
				break;
			case 소:
				++itemCount.Cow;
				break;
			case 돼지:
				++itemCount.Pig;
				break;
			case 양:
				++itemCount.Sheep;
				break;
			case 양털아이템:
				++itemCount.SheepTer;
				break;
			}
			delete (*itr);
			died_Objects.erase(itr);

			itemCount.show();
		}
		else if (itr2 != mined_Objects.end()) {
			++itemCount.Rice;
			delete (*itr2);
			mined_Objects.erase(itr2);

			itemCount.show();
		}
	}

}

set<CGameObject*, CGameObjectCmp>::iterator CWorld::getObject()
{
	glm::vec3 normalDirection = cameraDirection - cameraPos;
	normalDirection = glm::normalize(normalDirection);

	if (1 == personView)
		for (int i = 2; i < 65; ++i) {
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
	else if (3 == personView)
		for (int i = 77; i < 140; ++i) {
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

void CWorld::addNewObject(const int& ObjectType)
{
	glm::vec3 normalDirection = cameraDirection - cameraPos;
	normalDirection = glm::normalize(normalDirection);

	if (1 == personView)
		for (int i = 2; i < 65; ++i) {
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
				insertObject(ObjectType, tempPos);
				break;
			}
		}
	else if (3 == personView)
		for (int i = 77; i < 140; ++i) {
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
				insertObject(ObjectType, tempPos);
				break;
			}
		}
}

void CWorld::insertObject(const int& ObjectType, const glm::vec3& ObjectPos)
{
	switch (ObjectType) {
	case 기본흙:
		Objects.insert(new CBase(ObjectPos));
		break;
	case 잔디흙:
		Objects.insert(new CGrass(ObjectPos));
		break;
	case 벼:
		Objects.insert(new CRice(ObjectPos, false));
		break;
	case 양털:
		Objects.insert(new CWool(ObjectPos));
		break;

	case 나무:
		MakeTree(ObjectPos);
		break;
	case 나무줄기:
		Objects.insert(new CTreeTrunk(ObjectPos));
		break;
	case 나뭇잎:
		Objects.insert(new CLeaves(ObjectPos));
		break;


	case 돼지:
		Objects.insert(new CPig(ObjectPos, Form::creature));
		break;
	case 소:
		Objects.insert(new CCow(ObjectPos, Form::creature));
		break;
	case 닭:
		Objects.insert(new CChicken(ObjectPos, Form::creature));
		break;
	case 양:
		Objects.insert(new CSheep(ObjectPos, Form::creature, 양));
		break;
	//case 무너양:
	//	Objects.insert(new CSheepNOTUL(ObjectPos, Form::creature));
	//	break;

	}
}



void CWorld::Initialize()
{
	qobj = gluNewQuadric();		// 실린더 객체 생성
	MakeWorld();
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
	// 투영변환 - 원근투영
	glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)winWidth / (float)winHeight, 0.1f, 200.f);
	GLuint projectionLocation = glGetUniformLocation(shaderID, "projectionTransform"); //--- 투영 변환 값 설정
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

	Camera();

	// 태양 표현
	{
		glClearColor(0.5f, 1.f, 1.f, 1.0f);					// 기본 하늘색은 하늘색

		//조명 색상과 위치
		GLuint lightColorLocation = glGetUniformLocation(shaderID, "lightColor");	//--- lightColor 값 전달: (1.0, 1.0, 1.0) 백색
		glUniform3f(lightColorLocation, 1.f, 1.f, 1.f);
		GLuint lightPosLocation = glGetUniformLocation(shaderID, "lightPos"); //--- lightPos 값 전달: (0.0, 0.0, 5.0);
		glUniform3f(lightPosLocation, 0.0, 50.0, 0.0);

		glBindVertexArray(BlockVAO);

		GLuint selectColorLocation = glGetUniformLocation(shaderID, "selectColor");	//--- 색상 사용
		GLuint objectColorLocation = glGetUniformLocation(shaderID, "objectColor");	//--- 색상 사용
		glUniform1i(selectColorLocation, 0);
		glUniform4f(objectColorLocation, 1, 1, 1, 1);

		glm::mat4 change = glm::translate(glm::mat4(1.f), glm::vec3(0, 55, 0)) * glm::scale(glm::mat4(1.f), glm::vec3(10, 0.1, 10));

		GLuint model = glGetUniformLocation(shaderID, "modelTransform");
		glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(change));

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}


	// 하늘 표현식입니다. 나는 천재
	{
		GLuint normalOption = glGetUniformLocation(shaderID, "normalOption");
		GLuint selectColorLocation = glGetUniformLocation(shaderID, "selectColor");	//--- 색상 사용
		GLuint objectColorLocation = glGetUniformLocation(shaderID, "objectColor");	//--- 색상 사용
		GLuint modelLocation = glGetUniformLocation(shaderID, "modelTransform");
		glDisable(GL_CULL_FACE);
		glUniform1i(normalOption, 1);
		glUniform1i(selectColorLocation, 0);
		glm::mat4 Rotate = glm::rotate(glm::mat4(1.f), glm::radians(-90.f), glm::vec3(1, 0, 0));
		glm::mat4 change;

		change = glm::translate(glm::mat4(1.f), glm::vec3(0, -50, 0)) * Rotate;
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(change));
		glUniform4f(objectColorLocation, 1, 1, 1, 0.2);
		gluCylinder(qobj, 165.0, 165.0, 100.0, 100, 10);

		change = glm::translate(glm::mat4(1.f), glm::vec3(0, -40, 0)) * Rotate;
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(change));
		glUniform4f(objectColorLocation, 1, 1, 1, 0.2);
		gluCylinder(qobj, 160.0, 160.0, 80.0, 100, 8);

		change = glm::translate(glm::mat4(1.f), glm::vec3(0, -30, 0)) * Rotate;
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(change));
		glUniform4f(objectColorLocation, 1, 1, 1, 0.2);
		gluCylinder(qobj, 155.0, 155.0, 60.0, 100, 6);

		change = glm::translate(glm::mat4(1.f), glm::vec3(0, -20, 0)) * Rotate;
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(change));
		glUniform4f(objectColorLocation, 1, 1, 1, 0.2);
		gluCylinder(qobj, 150.0, 150.0, 40.0, 100, 4);

		change = glm::translate(glm::mat4(1.f), glm::vec3(0, -10, 0)) * Rotate;
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(change));
		glUniform4f(objectColorLocation, 1, 1, 1, 0.2);
		gluCylinder(qobj, 145.0, 145.0, 20.0, 100, 2);

		glUniform1i(normalOption, 0);
		glEnable(GL_CULL_FACE);
	}

	for (auto Object : Objects) {
		Object->Render();
	}
	for (auto Object : died_Objects) {
		Object->Render();
	}
	for (auto Object : mined_Objects) {
		Object->Render();
	}

	Player.Render();


	// 인벤토리 표시
	viewInventory();
}

void CWorld::Release()
{
}

void CWorld::viewInventory()
{
	// 투영변환 - 원근투영
	GLuint projectionLocation = glGetUniformLocation(shaderID, "projectionTransform"); //--- 투영 변환 값 설정
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.f)));

	GLuint viewLocation = glGetUniformLocation(shaderID, "viewTransform"); //--- 뷰잉 변환 설정
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.f)));

	GLuint modelLocation = glGetUniformLocation(shaderID, "modelTransform");

	GLuint selectColorLocation = glGetUniformLocation(shaderID, "selectColor");	//--- 텍스처 사용
	glUniform1i(selectColorLocation, 1);

	glBindVertexArray(InvenVAO);
	glm::mat4 Change;
	glm::mat4 Trans;
	glm::mat4 Scale;
	int num;

	Scale = glm::scale(glm::mat4(1.f), glm::vec3(0.2, 0.1, 0.1));

	// 치킨
	Trans = glm::translate(glm::mat4(1.f), glm::vec3(-0.8, 0.9, 0));
	Change = Trans * Scale;
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Change)); //--- modelTransform 변수에 변환 값 적용하기
	num = itemCount.Chicken;
	if (num > 5)num = 5;
	glBindTexture(GL_TEXTURE_2D, ItemTexture[0][num]);
	glDrawArrays(GL_QUADS, 0, 4);

	// 돼지
	Trans = glm::translate(glm::mat4(1.f), glm::vec3(-0.8, 0.7, 0));
	Change = Trans * Scale;
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Change)); //--- modelTransform 변수에 변환 값 적용하기
	num = itemCount.Pig;
	if (num > 5)num = 5;
	glBindTexture(GL_TEXTURE_2D, ItemTexture[1][num]);
	glDrawArrays(GL_QUADS, 0, 4);

	// 벼
	Trans = glm::translate(glm::mat4(1.f), glm::vec3(-0.8, 0.5, 0));
	Change = Trans * Scale;
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Change)); //--- modelTransform 변수에 변환 값 적용하기
	num = itemCount.Rice;
	if (num > 5)num = 5;
	glBindTexture(GL_TEXTURE_2D, ItemTexture[2][num]);
	glDrawArrays(GL_QUADS, 0, 4);

	// 소
	Trans = glm::translate(glm::mat4(1.f), glm::vec3(-0.8, 0.3, 0));
	Change = Trans * Scale;
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Change)); //--- modelTransform 변수에 변환 값 적용하기
	num = itemCount.Cow;
	if (num > 5)num = 5;
	glBindTexture(GL_TEXTURE_2D, ItemTexture[3][num]);
	glDrawArrays(GL_QUADS, 0, 4);

	// 양
	Trans = glm::translate(glm::mat4(1.f), glm::vec3(-0.8, 0.1, 0));
	Change = Trans * Scale;
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Change)); //--- modelTransform 변수에 변환 값 적용하기
	num = itemCount.Sheep;
	if (num > 5)num = 5;
	glBindTexture(GL_TEXTURE_2D, ItemTexture[4][num]);
	glDrawArrays(GL_QUADS, 0, 4);

	// 양털
	Trans = glm::translate(glm::mat4(1.f), glm::vec3(-0.8, -0.1, 0));
	Change = Trans * Scale;
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Change)); //--- modelTransform 변수에 변환 값 적용하기
	num = itemCount.SheepTer;
	if (num > 5)num = 5;
	glBindTexture(GL_TEXTURE_2D, ItemTexture[5][num]);
	glDrawArrays(GL_QUADS, 0, 4);

}

int CWorld::getpersonView()
{
	return personView;
}

void CWorld::MakeTree(glm::vec3 position)
{
	float x{ position.x }, y{ position.y }, z{ position.z };

	for (int i = 0; i < 4; ++i)
		Objects.insert(new CTreeTrunk{ glm::vec3(x,y + i,z) });

	for (int i = -1; i < 2; ++i) {
		Objects.insert(new CLeaves{ glm::vec3(x + i,y + 2,z) });
		Objects.insert(new CLeaves{ glm::vec3(x,y + 2,z + i) });
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

void CWorld::MakeTree2(glm::vec3 position)
{
	float x{ position.x }, y{ position.y+1 }, z{ position.z };

	for (int i = 0; i < 5; ++i)
		Objects.insert(new CBirchTrunk{ glm::vec3(x,y + i,z) });

	for (int i = -2; i < 3; ++i) {
		for (int j = -2; j < 3; ++j) {
			Objects.insert(new CLeaves{ glm::vec3(x + i,y + 3,z + j) });
		}
	}

	for (int i = -1; i < 2; ++i) {
		for (int j = -1; j < 2; ++j) {
			Objects.insert(new CLeaves{ glm::vec3(x + i,y + 4,z + j) });
		}
	}

	Objects.insert(new CLeaves{ glm::vec3(x ,y + 5,z) });


}

void CWorld::MakeCloud(glm::vec3 position)
{
	float x{ position.x }, y{ position.y }, z{ position.z };
	int sky{ 30 };

	for (int i = 2; i < 7; ++i)
		Objects.insert(new CCloud{ glm::vec3(x + i,y + sky,z) });

	for (int i = 1; i < 5; ++i)
		Objects.insert(new CCloud{ glm::vec3(x + i,y + sky,z+1) });

	for (int i = 0; i < 5; ++i)
		Objects.insert(new CCloud{ glm::vec3(x + i,y + sky,z+2) });

	for (int i = 3; i < 6; ++i)
		Objects.insert(new CCloud{ glm::vec3(x + i,y + sky,z+3) });

}

void CWorld::MakeCloud2(glm::vec3 position)
{
	float x{ position.x }, y{ position.y }, z{ position.z };
	int sky{ 30 };

	for (int i = 0; i < 4; ++i)
		Objects.insert(new CCloud{ glm::vec3(x + i,y + sky,z) });

	for (int i = 1; i < 4; ++i)
		Objects.insert(new CCloud{ glm::vec3(x + i,y + sky,z + 1) });

	for (int i = 0; i < 3; ++i)
		Objects.insert(new CCloud{ glm::vec3(x + i,y + sky,z + 2) });

}

void CWorld::MakeCloud3(glm::vec3 position)
{
	float x{ position.x }, y{ position.y }, z{ position.z };
	int sky{ 30 };

	for (int i = 4; i < 8; ++i)
		Objects.insert(new CCloud{ glm::vec3(x + i,y + sky,z) });

	for (int i = 2; i < 8; ++i)
		Objects.insert(new CCloud{ glm::vec3(x + i,y + sky,z + 1) });

	for (int i = 0; i < 6; ++i)
		Objects.insert(new CCloud{ glm::vec3(x + i,y + sky,z + 2) });

	for (int i = 1; i < 6; ++i)
		Objects.insert(new CCloud{ glm::vec3(x + i,y + sky,z + 3) });

}

void CWorld::MakeCloud4(glm::vec3 position)
{
	float x{ position.x }, y{ position.y }, z{ position.z };
	int sky{ 30 };

	for (int i = 2; i < 4; ++i)
		Objects.insert(new CCloud{ glm::vec3(x + i,y + sky,z) });

	for (int i = 1; i < 4; ++i)
		Objects.insert(new CCloud{ glm::vec3(x + i,y + sky,z + 1) });

	for (int i = 0; i < 5; ++i)
		Objects.insert(new CCloud{ glm::vec3(x + i,y + sky,z + 2) });

	for (int i = 1; i < 4; ++i)
		Objects.insert(new CCloud{ glm::vec3(x + i,y + sky,z + 3) });

}

void CWorld::MakeWorld()
{

	// 바닥 아래
	for (int k = -1; k > -5; --k)
		for (int i = -25; i <= 24; ++i)
			for (int j = -25; j <= 24; ++j)
				Objects.insert(new CBase{ glm::vec3{i, k, j} });

	// 바닥 0
	for (int i = -25; i <= 24; ++i)
		for (int j = -25; j <= 24; ++j) {
			if (i >= -7 && i <= 23 && j >= -24 && j <= 5)
				Objects.insert(new CGrass{ glm::vec3{i, 0, j} });
			else
				Objects.insert(new CBase{ glm::vec3{i, 0, j} });
		}

	// 바닥 1
	for (int i = -25; i <= 24; ++i)
		for (int j = -25; j <= 24; ++j) {
			if (!(i >= -7 && i <= 23 && j >= -24 && j <= 5)) {
				if (i >= -7 && i <= 24 && j == -25)
					Objects.insert(new CGrass{ glm::vec3{i, 1, j} });
				else if (i == 24 && j >= -25 && j <= 5)
					Objects.insert(new CGrass{ glm::vec3{i, 1, j} });
				else if (i >= -24 && i <= -6 && j >= -24 && j <= 10)
					Objects.insert(new CGrass{ glm::vec3{i, 1, j} });
				else if (i >= -7&& i <= 24 && j >= 5 && j <= 10)
					Objects.insert(new CGrass{ glm::vec3{i, 1, j} });
				else {
					Objects.insert(new CBase{ glm::vec3{i, 1, j} });
					Objects.insert(new CGrass{ glm::vec3{i, 2, j} });
				}
			}
		}


	
	MakeTree(glm::vec3(-7, 0+1, - 24));
	MakeTree(glm::vec3(-8, 2 + 1, -25));
	MakeTree(glm::vec3(23, 0 + 1, -9));
	MakeTree(glm::vec3(20, 0 + 1, 0));
	MakeTree(glm::vec3(16, 0 + 1, -19));
	MakeTree(glm::vec3(11, 0 + 1, -22));
	MakeTree(glm::vec3(23, 0 + 1, -23));
	MakeTree(glm::vec3(21, 0 + 1, -16));
	MakeTree(glm::vec3(8, 0 + 1, -5));
	MakeTree(glm::vec3(-23, 1 + 1, 6));
	MakeTree(glm::vec3(-12, 1 + 1, -9));
	MakeTree(glm::vec3(-20, 2 + 1, 21));
	MakeTree(glm::vec3(-3, 2 + 1, 14));
	MakeTree(glm::vec3(5, 2 + 1, 22));
	MakeTree(glm::vec3(21, 2 + 1, 17));
	MakeTree(glm::vec3(23, 2 + 1, 23));

	MakeTree2(glm::vec3(-14, 2 + 1, 14));
	MakeTree2(glm::vec3(-18, 1 + 1, -23));
	MakeTree2(glm::vec3(-25, 1 + 1, -19));
	MakeTree2(glm::vec3(-25, 2 + 1, -19	));
	MakeTree2(glm::vec3(-24, 1 + 1, -18));
	MakeTree2(glm::vec3(-25, 2 + 1, -19));
	MakeTree2(glm::vec3(-21, 1 + 1, -6));
	MakeTree2(glm::vec3(2, 1 + 1, 10));
	MakeTree2(glm::vec3(23, 1 + 1, 7));
	MakeTree2(glm::vec3(16, 2 + 1, 22));









	//Objects.insert(new CSheep{ glm::vec3(3,1+1,3) });
	//Objects.insert(new CPig{ glm::vec3(-3,1+1,3) });
	//Objects.insert(new CCow{ glm::vec3(5,1+2,-3) });
	//Objects.insert(new CChicken{ glm::vec3(3,1+3,-6) });

	MakeCloud(glm::vec3(-25, 0, -25));
	MakeCloud2(glm::vec3(-25, 0, -16));
	MakeCloud3(glm::vec3(-20, 0, -10));
	MakeCloud4(glm::vec3(-15, 0, -8));

	MakeCloud(glm::vec3(-23, 0, 3));
	MakeCloud2(glm::vec3(-19, 0, 14));
	MakeCloud3(glm::vec3(-10, 0, 10));
	MakeCloud4(glm::vec3(-16, 0, 23));

	MakeCloud(glm::vec3(3, 0, 16));
	MakeCloud2(glm::vec3(18, 0, 4));
	MakeCloud3(glm::vec3(10, 0, 10));
	MakeCloud4(glm::vec3(26, 0, 18));
	MakeCloud4(glm::vec3(7, 0, 24));

	MakeCloud(glm::vec3(6, 0, -3));
	MakeCloud2(glm::vec3(8, 0, -10));
	MakeCloud2(glm::vec3(18, 0, -14));
	MakeCloud3(glm::vec3(11, 0, -24));
	MakeCloud4(glm::vec3(25, 0, -18));
	

}

