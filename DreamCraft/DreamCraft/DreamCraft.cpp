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

int TimerValue = 10;		//Ÿ�̸�(����) ���ΰ�ħ �ֱ�(ms)

char* filetobuf(string file);
void ReadObj(string file, vector<glm::vec3>& vertexInfo);

// ��������
GLint winWidth = 1500, winHeight = 900;		//--- ���� â ũ��
GLuint BlockVAO, BlockVBO;
GLuint shaderID; //--- ���̴� ���α׷� �̸�
pair<float, float> MouseAngle;

GLuint Texture[50];

float textureVertex[36][2]{
	{1,0},	{0,1},	{0,0},	{1,0},	{1,1},	{0,1},

	{0,0},	{1,1},	{0,1},	{0,0},	{1,0},	{1,1},

	{0,1},	{1,0},	{1,1},	{0,1},	{0,0},	{1,0},

	{1,0},	{1,1},	{0,1},	{1,0},	{0,1},	{0,0},

	{0,0},	{1,0},	{1,1},	{0,0},	{1,1},	{0,1},

	{0,0},	{1,0},	{1,1},	{0,0},	{1,1},	{0,1}
};

void main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ����
{
	//--- ������ �����ϱ�
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("DreamCraft");

	//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	glewInit();

	// ���콺 Ŀ�� ��� �ٲٱ�
	glutSetCursor(GLUT_CURSOR_CROSSHAIR);
	//glutSetCursor(GLUT_CURSOR_NONE);

	//���� ���̴� ���� �� ���� ����
	shaderID = make_shaderProgram(); //--- ���̴� ���α׷� �����
	glUseProgram(shaderID);
	InitBuffer();	// VAO, VBO ����
	InitTexture();

	glEnable(GL_BLEND);		// ���� Ȱ��ȭ

	glutDisplayFunc(drawScene); //--- ��� �ݹ� �Լ�
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
	//--- ���ؽ� ���̴� �о� �����ϰ� ������ �ϱ�
	//--- filetobuf: ��������� �Լ��� �ؽ�Ʈ�� �о ���ڿ��� �����ϴ� �Լ�
	GLchar* vertexSource = filetobuf("vertex.glsl");
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);		//--- ���ؽ� ���̴� ��ü
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		cerr << "ERROR: vertex shader ������ ����\n" << errorLog << endl;
		return false;
	}
	else
		return vertexShader;
}

//--- �����׸�Ʈ ���̴� ��ü �����
GLuint make_fragmentShaders()
{
	//--- �����׸�Ʈ ���̴� �о� �����ϰ� �������ϱ�
	GLchar* fragmentSource = filetobuf("fragment.glsl"); // �����׼��̴� �о����
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);		//--- �����׸�Ʈ ���̴� ��ü
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		cerr << "ERROR: fragment shader ������ ����\n" << errorLog << endl;
		return false;
	}
	else
		return fragmentShader;
}

//--- ���̴� ���α׷� �����
GLuint make_shaderProgram()
{
	//--- ���̴� �о�ͼ� ���̴� ���α׷� �����
	GLuint vertexShader = make_vertexShaders(); //--- ���ؽ� ���̴� �����
	GLuint fragmentShader = make_fragmentShaders(); //--- �����׸�Ʈ ���̴� �����

	GLuint ShaderProgramID;
	ShaderProgramID = glCreateProgram(); //--- ���̴� ���α׷� �����
	glAttachShader(ShaderProgramID, vertexShader); //--- ���̴� ���α׷��� ���ؽ� ���̴� ���̱�
	glAttachShader(ShaderProgramID, fragmentShader); //--- ���̴� ���α׷��� �����׸�Ʈ ���̴� ���̱�
	glLinkProgram(ShaderProgramID); //--- ���̴� ���α׷� ��ũ�ϱ�
	glDeleteShader(vertexShader); //--- ���̴� ��ü�� ���̴� ���α׷��� ��ũ��������, ���̴� ��ü ��ü�� ���� ����
	glDeleteShader(fragmentShader);

	GLint result;
	GLchar errorLog[512];

	glGetProgramiv(ShaderProgramID, GL_LINK_STATUS, &result); // ---���̴��� �� ����Ǿ����� üũ�ϱ�
	if (!result) {
		glGetProgramInfoLog(ShaderProgramID, 512, NULL, errorLog);
		cerr << "ERROR: shader program ���� ����\n" << errorLog << endl;
		return false;
	}
	glUseProgram(ShaderProgramID);			//--- ������� ���̴� ���α׷� ����ϱ�
											//--- ���� ���� ���̴����α׷� ���� �� �ְ�, �� �� �Ѱ��� ���α׷��� ����Ϸ���
											//--- glUseProgram �Լ��� ȣ���Ͽ� ��� �� Ư�� ���α׷��� �����Ѵ�.
											//--- ����ϱ� ������ ȣ���� �� �ִ�.
	return ShaderProgramID;
}

void InitBuffer()					// ���� ���� ����
{
	vector<glm::vec3> vertex;

	ReadObj("Block.obj", vertex);

	//--- VAO ��ü ���� �� ���ε�
	glGenVertexArrays(1, &BlockVAO);
	glGenBuffers(1, &BlockVBO);

	//// ����, ���� ���� ��Ģ �����
	glBindVertexArray(BlockVAO);

	glBindBuffer(GL_ARRAY_BUFFER, BlockVBO);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(glm::vec3), &vertex[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);		// ���ؽ� �Ӽ� �迭�� ����ϵ��� �Ѵ�.(0�� �迭 Ȱ��ȭ)
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);		// ���ؽ� �Ӽ� �迭�� ����ϵ��� �Ѵ�.(1�� �迭 Ȱ��ȭ)

		//--�ؽ�ó
	GLuint textureVBO;
	glGenBuffers(1, &textureVBO);
	glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(textureVertex), textureVertex, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0); //--- �ؽ�ó ��ǥ �Ӽ�
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
		stbi_set_flip_vertically_on_load(true); //--- �̹����� �Ųٷ� �����ٸ� �߰�
		string filename;
		GLubyte* data;
		switch (i) {
		case 0:
			filename = "�ؽ�ó/��Ǯ.png";		// ��
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		case 1:
			filename = "�ؽ�ó/��Ǯ.png";		// �ܵ�
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		case 2:
			filename = "�ؽ�ó/��Ǯ2.png";		// �ܵ� ����
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			//glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;

			// ��
		case 3:
			filename = "�ؽ�ó/����.png";		// ����
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			//glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		case 4:
			filename = "�ؽ�ó/����.png";		// ����
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			//glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		case 5:
			filename = "�ؽ�ó/����.png";		// ����
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		case 6:
			filename = "�ؽ�ó/��ٸ�.png";		// ��ٸ�
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		case 7:
			filename = "�ؽ�ó/��Ӹ�.png";		// ��Ӹ�
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			//glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;

			// ��
		case 8:
			filename = "�ؽ�ó/����.png";		// ����
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			//glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		case 9:
			filename = "�ؽ�ó/�Ұ��.png";		// �Ұ��
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		case 10:
			filename = "�ؽ�ó/�Ҵٸ�.png";		// �Ҵٸ�
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		case 11:
			filename = "�ؽ�ó/�ҸӸ�.png";		// �ҸӸ�
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;

			// ����
		case 12:
			filename = "�ؽ�ó/������.png";		// ������
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			//glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		case 13:
			filename = "�ؽ�ó/�������.png";		// �������
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		case 14:
			filename = "�ؽ�ó/�����ٸ�.png";		// �����ٸ�
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		case 15:
			filename = "�ؽ�ó/�����Ӹ�.png";		// �����Ӹ�
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			//glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;

			// ��
		case 16:
			filename = "�ؽ�ó/����.png";		// ����
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			//glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		case 17:
			filename = "�ؽ�ó/�߰��.png";		// �߰��
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		case 18:
			filename = "�ؽ�ó/�߳���.png";		// �߳���
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			//glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		case 19:
			filename = "�ؽ�ó/�ߴٸ�.png";		// �ߴٸ�
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		case 20:
			filename = "�ؽ�ó/�߸Ӹ�2.png";		// �߸Ӹ�
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			//glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;

			// ����
		case 25:
			filename = "�ؽ�ó/��������.png";		// ��������
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			//glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		case 26:
			filename = "�ؽ�ó/��������.png";		// ��������
			data = stbi_load(filename.c_str(), &ImageWidth, &ImageHeight, &numberOfChannel, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			//glTexImage2D(GL_TEXTURE_2D, 0, 4, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		case 27:
			filename = "�ؽ�ó/��������.png";	// �������ĸ�
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


}

GLvoid drawScene() //--- �ݹ� �Լ�: �׸��� �ݹ� �Լ�
{
	glEnable(GL_DEPTH_TEST);	//��������
	glEnable(GL_DITHER);        // ǥ���� �Ų�����
	glEnable(GL_CULL_FACE);     // �ø�
	glEnable(GL_LINE_SMOOTH);   // ��Ƽ �ٸ����
	glEnable(GL_POLYGON_SMOOTH);// ��Ƽ �ٸ����
	glShadeModel(GL_SMOOTH);    // �ε巯�� ������ �����մϴ�.

	glClearColor(0.f, 0.f, 0.f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//���� ����� ��ġ
	GLuint lightColorLocation = glGetUniformLocation(shaderID, "lightColor");	//--- lightColor �� ����: (1.0, 1.0, 1.0) ���
	glUniform3f(lightColorLocation, 1.f, 1.f, 1.f);
	GLuint lightPosLocation = glGetUniformLocation(shaderID, "lightPos"); //--- lightPos �� ����: (0.0, 0.0, 5.0);
	glUniform3f(lightPosLocation, 0.0, 10.0, 50.0);


	World.Render();

	glutSwapBuffers();							// ȭ�鿡 ����ϱ�
}

GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
{
	winWidth = w;
	winHeight = h;

	// ������ȯ - ��������
	glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)winWidth / (float)winHeight, 0.1f, 200.f);
	GLuint projectionLocation = glGetUniformLocation(shaderID, "projectionTransform"); //--- ���� ��ȯ �� ����
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

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

	if ((y - winHeight / 2) < 0 && MouseAngle.second > -80.f)		// �ϴ�
		MouseAngle.second += ((y - winHeight / 2) / 12.5f);
	else if ((y - winHeight / 2) >= 0 && MouseAngle.second < 85.f)	//��
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
				if (i == -1) continue;						// f ������ �ǳʶڴ�
				if (word.find("/") != string::npos) {
					istringstream slash(word);
					string slashtmp;
					getline(slash, slashtmp, '/');

					vfacetemp[i] = atoi(slashtmp.c_str()) - 1;			//f ������ ù��°����(v)	//�迭�ε��� ���Ŷ� -1����

					getline(slash, slashtmp, '/');
					getline(slash, slashtmp, '/');
					vnfacetemp[i] = atoi(slashtmp.c_str()) - 1;
				}
				else {
					vfacetemp[i] = atoi(word.c_str()) - 1;			//f ������ ù��°����(v)	//�迭�ε��� ���Ŷ� -1����
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
