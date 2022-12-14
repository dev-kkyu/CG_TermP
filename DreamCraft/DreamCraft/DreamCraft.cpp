#include "Header.h"

#include "CWorld.h"

#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "freeglut.lib")

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

CWorld World;

GLuint make_vertexShaders();
GLuint make_fragmentShaders();
GLuint make_shaderProgram();

void InitBuffer();
void InitTexture();

GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid KeyboardUP(unsigned char key, int x, int y);
GLvoid SpecialKeyboard(int key, int x, int y);
GLvoid SpecialKeyboardUP(int key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Motion(int x, int y);
GLvoid PassiveMotion(int x, int y);
GLvoid TimerFunction(int value);

int TimerValue = 10;		//타이머(루프) 새로고침 주기(ms)

char* filetobuf(string file);
void ReadObj(string file, vector<glm::vec3>& vertexInfo);

// 전역변수
GLint winWidth = 1500, winHeight = 900;		//--- 생성 창 크기
GLuint BlockVAO, BlockVBO;
GLuint InvenVAO, InvenVBO;
GLuint shaderID; //--- 세이더 프로그램 이름
pair<float, float> MouseAngle;

GLuint Texture[50];
GLuint ItemTexture[6][6];

float InvenWindow[4][8]{
	{-1, 1, 0,		0, 0, 1,	0, 1},
	{-1, -1, 0,		0, 0, 1,	0, 0},
	{1, -1, 0,		0, 0, 1,	1, 0},
	{1, 1, 0,		0, 0, 1,	1, 1}
};

float textureVertex[36][2]{
	{1,0},	{0,1},	{0,0},	{1,0},	{1,1},	{0,1},

	{0,0},	{1,1},	{0,1},	{0,0},	{1,0},	{1,1},

	{0,1},	{1,0},	{1,1},	{0,1},	{0,0},	{1,0},

	{1,0},	{1,1},	{0,1},	{1,0},	{0,1},	{0,0},

	{0,0},	{1,0},	{1,1},	{0,0},	{1,1},	{0,1},

	{0,0},	{1,0},	{1,1},	{0,0},	{1,1},	{0,1}
};

void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
{
	//--- 윈도우 생성하기
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("DreamCraft");

	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	glewInit();

	// 마우스 커서 모양 바꾸기
	glutSetCursor(GLUT_CURSOR_CROSSHAIR);
	//glutSetCursor(GLUT_CURSOR_NONE);

	//도형 쉐이더 생성 및 버퍼 생성
	shaderID = make_shaderProgram(); //--- 세이더 프로그램 만들기
	glUseProgram(shaderID);
	InitBuffer();	// VAO, VBO 생성
	InitTexture();

	glEnable(GL_DEPTH_TEST);	//은면제거
	glEnable(GL_DITHER);        // 표면을 매끄럽게
	glEnable(GL_CULL_FACE);     // 컬링
	glEnable(GL_LINE_SMOOTH);   // 안티 앨리어싱
	glEnable(GL_POLYGON_SMOOTH);// 안티 앨리어싱
	glShadeModel(GL_SMOOTH);    // 부드러운 음영을 수행합니다.

	glEnable(GL_BLEND);			// 블렌딩 기능을 활성화한다.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	//지수를 원본 컬러 벡터 Csource의 알파값으로 설정

	glClearColor(0.5f, 1.f, 1.f, 1.0f);					// 기본 하늘색은 하늘색

	glutDisplayFunc(drawScene); //--- 출력 콜백 함수
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyboardUP);
	glutSpecialFunc(SpecialKeyboard);
	glutSpecialUpFunc(SpecialKeyboardUP);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutPassiveMotionFunc(PassiveMotion);
	glutTimerFunc(TimerValue, TimerFunction, 1);
	glutMainLoop();
}

GLuint make_vertexShaders()
{
	//--- 버텍스 세이더 읽어 저장하고 컴파일 하기
	//--- filetobuf: 사용자정의 함수로 텍스트를 읽어서 문자열에 저장하는 함수
	GLchar* vertexSource = filetobuf("vertex.glsl");
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);		//--- 버텍스 세이더 객체
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		cerr << "ERROR: vertex shader 컴파일 실패\n" << errorLog << endl;
		return false;
	}
	else
		return vertexShader;
}

//--- 프래그먼트 세이더 객체 만들기
GLuint make_fragmentShaders()
{
	//--- 프래그먼트 세이더 읽어 저장하고 컴파일하기
	GLchar* fragmentSource = filetobuf("fragment.glsl"); // 프래그세이더 읽어오기
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);		//--- 프래그먼트 세이더 객체
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		cerr << "ERROR: fragment shader 컴파일 실패\n" << errorLog << endl;
		return false;
	}
	else
		return fragmentShader;
}

//--- 세이더 프로그램 만들기
GLuint make_shaderProgram()
{
	//--- 세이더 읽어와서 세이더 프로그램 만들기
	GLuint vertexShader = make_vertexShaders(); //--- 버텍스 세이더 만들기
	GLuint fragmentShader = make_fragmentShaders(); //--- 프래그먼트 세이더 만들기

	GLuint ShaderProgramID;
	ShaderProgramID = glCreateProgram(); //--- 세이더 프로그램 만들기
	glAttachShader(ShaderProgramID, vertexShader); //--- 세이더 프로그램에 버텍스 세이더 붙이기
	glAttachShader(ShaderProgramID, fragmentShader); //--- 세이더 프로그램에 프래그먼트 세이더 붙이기
	glLinkProgram(ShaderProgramID); //--- 세이더 프로그램 링크하기
	glDeleteShader(vertexShader); //--- 세이더 객체를 세이더 프로그램에 링크했음으로, 세이더 객체 자체는 삭제 가능
	glDeleteShader(fragmentShader);

	GLint result;
	GLchar errorLog[512];

	glGetProgramiv(ShaderProgramID, GL_LINK_STATUS, &result); // ---세이더가 잘 연결되었는지 체크하기
	if (!result) {
		glGetProgramInfoLog(ShaderProgramID, 512, NULL, errorLog);
		cerr << "ERROR: shader program 연결 실패\n" << errorLog << endl;
		return false;
	}
	glUseProgram(ShaderProgramID);			//--- 만들어진 세이더 프로그램 사용하기
											//--- 여러 개의 세이더프로그램 만들 수 있고, 그 중 한개의 프로그램을 사용하려면
											//--- glUseProgram 함수를 호출하여 사용 할 특정 프로그램을 지정한다.
											//--- 사용하기 직전에 호출할 수 있다.
	return ShaderProgramID;
}

void InitBuffer()					// 도형 버퍼 생성
{
	vector<glm::vec3> vertex;

	ReadObj("Block.obj", vertex);

	//--- VAO 객체 생성 및 바인딩
	glGenVertexArrays(1, &BlockVAO);
	glGenBuffers(1, &BlockVBO);

	//// 정점, 색상 접근 규칙 만들기
	glBindVertexArray(BlockVAO);

	glBindBuffer(GL_ARRAY_BUFFER, BlockVBO);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(glm::vec3), &vertex[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);		// 버텍스 속성 배열을 사용하도록 한다.(0번 배열 활성화)
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);		// 버텍스 속성 배열을 사용하도록 한다.(1번 배열 활성화)

		//--텍스처
	GLuint textureVBO;
	glGenBuffers(1, &textureVBO);
	glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(textureVertex), textureVertex, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0); //--- 텍스처 좌표 속성
	glEnableVertexAttribArray(2);


	glGenVertexArrays(1, &InvenVAO);
	glGenBuffers(1, &InvenVBO);
	glBindVertexArray(InvenVAO);
	glBindBuffer(GL_ARRAY_BUFFER, InvenVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(InvenWindow), InvenWindow, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);		// 버텍스 속성 배열을 사용하도록 한다.(0번 배열 활성화)
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);		// 버텍스 속성 배열을 사용하도록 한다.(1번 배열 활성화)
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 6)); //--- 텍스처 좌표 속성
	glEnableVertexAttribArray(2);
}

void InitTexture()
{
	glGenTextures(50, Texture);

	for (int i = 0; i < 50; ++i) {
		glBindTexture(GL_TEXTURE_2D, Texture[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		int ImageWidth, ImageHeight, numberOfChannel;
		stbi_set_flip_vertically_on_load(true); //--- 이미지가 거꾸로 읽힌다면 추가
		string filename;
		GLubyte* data;
		switch (i) {
		case 0:
			filename = "텍스처/바닥/노풀.png";		// 흙
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		case 1:
			filename = "텍스처/바닥/옆풀.png";		// 잔디
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		case 2:
			filename = "텍스처/바닥/윗풀2.png";		// 잔디 윗면
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			//glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;

			// 양
		case 3:
			filename = "텍스처/동물/양털.png";		// 양털
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			//glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		case 4:
			filename = "텍스처/동물/노털.png";		// 노털
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			//glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		case 5:
			filename = "텍스처/동물/양고기.png";		// 양고기
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		case 6:
			filename = "텍스처/동물/양다리.png";		// 양다리
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		case 7:
			filename = "텍스처/동물/양머리.png";		// 양머리
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			//glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;

			// 소
		case 8:
			filename = "텍스처/동물/소털.png";		// 소털
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			//glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		case 9:
			filename = "텍스처/동물/소고기.png";		// 소고기
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		case 10:
			filename = "텍스처/동물/소다리.png";		// 소다리
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		case 11:
			filename = "텍스처/동물/소머리.png";		// 소머리
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;

			// 돼지
		case 12:
			filename = "텍스처/동물/돼지털.png";		// 돼지털
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			//glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		case 13:
			filename = "텍스처/동물/돼지고기.png";		// 돼지고기
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		case 14:
			filename = "텍스처/동물/돼지다리.png";		// 돼지다리
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		case 15:
			filename = "텍스처/동물/돼지머리.png";		// 돼지머리
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			//glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;

			// 닭
		case 16:
			filename = "텍스처/동물/닭털.png";		// 닭털
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			//glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		case 17:
			filename = "텍스처/동물/닭고기.png";		// 닭고기
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		case 18:
			filename = "텍스처/동물/닭날개.png";		// 닭날개
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			//glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		case 19:
			filename = "텍스처/동물/닭다리.png";		// 닭다리
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		case 20:
			filename = "텍스처/동물/닭머리2.png";		// 닭머리
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			//glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;

			// 나무
		case 25:
			filename = "텍스처/나무/나무옆통.png";		// 나무옆통
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		case 26:
			filename = "텍스처/나무/나무윗통.png";		// 나무윗통
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			//glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		case 27:
			filename = "텍스처/나무/나무ㅅ잎.png";	// 나무잎파리
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;


		case 28:
			filename = "텍스처/나무/나무옆통2.png";		// 나무옆통
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		case 29:
			filename = "텍스처/나무/나무윗통2.png";		// 나무윗통
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
			//case 30:
			//	filename = "텍스처/나무/나무ㅅ잎2.png";	// 나무잎파리
			//	data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			//	//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			//	glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			//	stbi_image_free(data);
			//	break;

			// 벼
		case 31:
			filename = "텍스처/벼.png";	// 벼
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;

		}
		//GLubyte* data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
		////glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		//glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		//stbi_image_free(data);
	}



	for (int i = 0; i < 6; ++i) {
		glGenTextures(6, ItemTexture[i]);
	}

	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 6; ++j) {
			glBindTexture(GL_TEXTURE_2D, ItemTexture[i][j]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			int ImageWidth, ImageHeight, numberOfChannel;
			stbi_set_flip_vertically_on_load(true); //--- 이미지가 거꾸로 읽힌다면 추가
			string filename;
			GLubyte* data;

			switch (i) {
			case 0:
				switch (j) {
				case 0:
					filename = "텍스처/인벤/닭0.png";
					data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
					//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
					stbi_image_free(data);
					break;
				case 1:
					filename = "텍스처/인벤/닭1.png";
					data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
					//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
					stbi_image_free(data);
					break;
				case 2:
					filename = "텍스처/인벤/닭2.png";
					data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
					//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
					stbi_image_free(data);
					break;
				case 3:
					filename = "텍스처/인벤/닭3.png";
					data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
					//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
					stbi_image_free(data);
					break;
				case 4:
					filename = "텍스처/인벤/닭4.png";
					data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
					//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
					stbi_image_free(data);
					break;
				case 5:
					filename = "텍스처/인벤/닭5.png";
					data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
					//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
					stbi_image_free(data);
					break;
				}
				break;
			case 1:
				switch (j) {
				case 0:
					filename = "텍스처/인벤/돼지0.png";
					data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
					//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
					stbi_image_free(data);
					break;
				case 1:
					filename = "텍스처/인벤/돼지1.png";
					data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
					//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
					stbi_image_free(data);
					break;
				case 2:
					filename = "텍스처/인벤/돼지2.png";
					data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
					//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
					stbi_image_free(data);
					break;
				case 3:
					filename = "텍스처/인벤/돼지3.png";
					data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
					//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
					stbi_image_free(data);
					break;
				case 4:
					filename = "텍스처/인벤/돼지4.png";
					data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
					//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
					stbi_image_free(data);
					break;
				case 5:
					filename = "텍스처/인벤/돼지5.png";
					data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
					//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
					stbi_image_free(data);
					break;
				}
				break;
			case 2:
				switch (j) {
				case 0:
					filename = "텍스처/인벤/벼0.png";
					data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
					//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
					stbi_image_free(data);
					break;
				case 1:
					filename = "텍스처/인벤/벼1.png";
					data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
					//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
					stbi_image_free(data);
					break;
				case 2:
					filename = "텍스처/인벤/벼2.png";
					data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
					//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
					stbi_image_free(data);
					break;
				case 3:
					filename = "텍스처/인벤/벼3.png";
					data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
					//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
					stbi_image_free(data);
					break;
				case 4:
					filename = "텍스처/인벤/벼4.png";
					data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
					//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
					stbi_image_free(data);
					break;
				case 5:
					filename = "텍스처/인벤/벼5.png";
					data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
					//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
					stbi_image_free(data);
					break;
				}
				break;
			case 3:
				switch (j) {
				case 0:
					filename = "텍스처/인벤/소0.png";
					data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
					//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
					stbi_image_free(data);
					break;
				case 1:
					filename = "텍스처/인벤/소1.png";
					data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
					//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
					stbi_image_free(data);
					break;
				case 2:
					filename = "텍스처/인벤/소2.png";
					data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
					//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
					stbi_image_free(data);
					break;
				case 3:
					filename = "텍스처/인벤/소3.png";
					data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
					//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
					stbi_image_free(data);
					break;
				case 4:
					filename = "텍스처/인벤/소4.png";
					data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
					//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
					stbi_image_free(data);
					break;
				case 5:
					filename = "텍스처/인벤/소5.png";
					data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
					//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
					stbi_image_free(data);
					break;
				}
				break;
			case 4:
				switch (j) {
				case 0:
					filename = "텍스처/인벤/양0.png";
					data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
					//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
					stbi_image_free(data);
					break;
				case 1:
					filename = "텍스처/인벤/양1.png";
					data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
					//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
					stbi_image_free(data);
					break;
				case 2:
					filename = "텍스처/인벤/양2.png";
					data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
					//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
					stbi_image_free(data);
					break;
				case 3:
					filename = "텍스처/인벤/양3.png";
					data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
					//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
					stbi_image_free(data);
					break;
				case 4:
					filename = "텍스처/인벤/양4.png";
					data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
					//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
					stbi_image_free(data);
					break;
				case 5:
					filename = "텍스처/인벤/양5.png";
					data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
					//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
					stbi_image_free(data);
					break;
				}
				break;
			case 5:
				switch (j) {
				case 0:
					filename = "텍스처/인벤/양털0.png";
					data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
					//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
					stbi_image_free(data);
					break;
				case 1:
					filename = "텍스처/인벤/양털1.png";
					data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
					//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
					stbi_image_free(data);
					break;
				case 2:
					filename = "텍스처/인벤/양털2.png";
					data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
					//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
					stbi_image_free(data);
					break;
				case 3:
					filename = "텍스처/인벤/양털3.png";
					data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
					//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
					stbi_image_free(data);
					break;
				case 4:
					filename = "텍스처/인벤/양털4.png";
					data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
					//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
					stbi_image_free(data);
					break;
				case 5:
					filename = "텍스처/인벤/양털5.png";
					data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
					//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
					stbi_image_free(data);
					break;
				}
				break;
			}
		}
	}
}

GLvoid drawScene() //--- 콜백 함수: 그리기 콜백 함수
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	World.Render();

	glutSwapBuffers();							// 화면에 출력하기
}

GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수
{
	winWidth = w;
	winHeight = h;

	//// 투영변환 - 원근투영
	//glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)winWidth / (float)winHeight, 0.1f, 200.f);
	//GLuint projectionLocation = glGetUniformLocation(shaderID, "projectionTransform"); //--- 투영 변환 값 설정
	//glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

	glViewport(0, 0, w, h);
}

GLvoid Keyboard(unsigned char key, int x, int y) {

	World.Keyboard(key, GLUT_DOWN);
}

GLvoid KeyboardUP(unsigned char key, int x, int y)
{
	World.Keyboard(key, GLUT_UP);
}

GLvoid SpecialKeyboard(int key, int x, int y)
{
	World.SpecialKeyboard(key, GLUT_DOWN);
}

GLvoid SpecialKeyboardUP(int key, int x, int y)
{
	World.SpecialKeyboard(key, GLUT_UP);
}

GLvoid Mouse(int button, int state, int x, int y)
{
	World.Mouse(button, state);
}

GLvoid Motion(int x, int y)
{
	PassiveMotion(x, y);
}

GLvoid PassiveMotion(int x, int y)
{
	MouseAngle.first += ((x - winWidth / 2) / 12.5f);

	if ((y - winHeight / 2) < 0 && MouseAngle.second > -80.f)		// 하늘
		MouseAngle.second += ((y - winHeight / 2) / 12.5f);
	else if ((y - winHeight / 2) >= 0 && MouseAngle.second < 85.f)	//땅
		MouseAngle.second += ((y - winHeight / 2) / 12.5f);

	glutWarpPointer(winWidth / 2, winHeight / 2);
}

GLvoid TimerFunction(int value)
{
	World.Update();

	glutPostRedisplay();

	glutTimerFunc(TimerValue, TimerFunction, 1);
}

char* filetobuf(string file) {
	ifstream in(file);

	string* str_buf = new string;
	while (in) {
		string temp;
		getline(in, temp);
		str_buf->append(temp);
		str_buf->append("\n");
	}

	return const_cast<char*>(str_buf->c_str());
}

void ReadObj(string file, vector<glm::vec3>& vertexInfo)
{
	vector<glm::vec3> vertex;
	vector<glm::vec3> vNormal;

	vector<glm::ivec3> vFace;
	vector<glm::ivec3> vnFace;

	ifstream in(file);
	if (!in) {
		cout << "OBJ File NO Have" << endl;
		return;
	}

	while (in) {
		string temp;
		getline(in, temp);

		if (temp[0] == 'v' && temp[1] == ' ') {
			istringstream slice(temp);

			glm::vec3 vertemp;
			char tmpword;
			slice >> tmpword >> vertemp.x >> vertemp.y >> vertemp.z;

			vertex.push_back(vertemp);
		}

		else if (temp[0] == 'v' && temp[1] == 'n' && temp[2] == ' ') {
			istringstream slice(temp);

			glm::vec3 vertemp;
			string tmpword;
			slice >> tmpword >> vertemp.x >> vertemp.y >> vertemp.z;

			vNormal.push_back(vertemp);
		}

		else if (temp[0] == 'f' && temp[1] == ' ') {
			istringstream slice(temp);

			glm::ivec3 vfacetemp;
			glm::ivec3 vnfacetemp;
			for (int i = -1; i < 3; ++i) {
				string word;
				getline(slice, word, ' ');
				if (i == -1) continue;						// f 읽을땐 건너뛴다
				if (word.find("/") != string::npos) {
					istringstream slash(word);
					string slashtmp;
					getline(slash, slashtmp, '/');

					vfacetemp[i] = atoi(slashtmp.c_str()) - 1;			//f 읽을땐 첫번째값만(v)	//배열인덱스 쓸거라 -1해줌

					getline(slash, slashtmp, '/');
					getline(slash, slashtmp, '/');
					vnfacetemp[i] = atoi(slashtmp.c_str()) - 1;
				}
				else {
					vfacetemp[i] = atoi(word.c_str()) - 1;			//f 읽을땐 첫번째값만(v)	//배열인덱스 쓸거라 -1해줌
				}
			}
			vFace.push_back(vfacetemp);
			vnFace.push_back(vnfacetemp);
		}
	}

	for (int i = 0; i < vFace.size(); ++i) {
		vertexInfo.push_back(vertex[vFace[i].x]);
		vertexInfo.push_back(vNormal[vnFace[i].x]);

		vertexInfo.push_back(vertex[vFace[i].y]);
		vertexInfo.push_back(vNormal[vnFace[i].y]);

		vertexInfo.push_back(vertex[vFace[i].z]);
		vertexInfo.push_back(vNormal[vnFace[i].z]);
	}
}
