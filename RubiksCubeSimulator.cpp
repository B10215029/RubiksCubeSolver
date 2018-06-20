#include "RubiksCubeSimulator.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <Windows.h>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const char* vertexShader = "#version 430\n";
const char* fragmentShader = "#version 430\n";
glm::vec3 rotation(0.5, 0.5, 0.0f);
glm::mat4 modelMatrix;
glm::mat4 viewMatrix;
glm::mat4 projectionMatrix;

GLuint loadShader(const char* shaderSource, GLenum shaderType);
GLuint loadProgram(const char* vertexShaderSource, const char* fragmentShaderSource);
const char* readFile(const char* filePath);

HGLRC RubiksCubeSolver::RubiksCubeSimulator::initializeOpenGLContext(HDC hDC)
{
	HGLRC hGLRC = NULL;
	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),    // size of this pfd 
		1,                                // version number 
		PFD_DRAW_TO_WINDOW |              // support window 
		PFD_SUPPORT_OPENGL,               // support OpenGL 
		PFD_TYPE_RGBA,                    // RGBA type 
		24,                               // 24-bit color depth 
		0, 0, 0, 0, 0, 0,                 // color bits ignored 
		0,                                // no alpha buffer 
		0,                                // shift bit ignored 
		0,                                // no accumulation buffer 
		0, 0, 0, 0,                       // accum bits ignored 
		32,                               // 32-bit z-buffer     
		0,                                // no stencil buffer 
		0,                                // no auxiliary buffer 
		PFD_MAIN_PLANE,                   // main layer 
		0,                                // reserved 
		0, 0, 0                           // layer masks ignored 
	};

	int cpf = ChoosePixelFormat(hDC, &pfd);
	if (!cpf) {
		std::cerr << "Choose Pixel Format Error\n";
		return false;
	}

	SetPixelFormat(hDC, cpf, &pfd);

	hGLRC = wglCreateContext(hDC);
	if (!hGLRC) {
		std::cerr << "Create Render Context Error\n";
		return false;
	}

	if (!wglMakeCurrent(hDC, hGLRC)) {
		hGLRC = NULL;
		std::cerr << "wglMakeCurrent Error\n";
		return false;
	}

	GLenum err = glewInit();
	if (GLEW_OK != err) {
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	//glViewport(0, 0, panel1->Width, panel1->Height);
	glClearColor(0, 0, 0, 1);
	//glEnable(GL_TEXTURE_2D);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	this->resize();
	this->initProgram();

	wglMakeCurrent(NULL, NULL);
	return hGLRC;
}

void RubiksCubeSolver::RubiksCubeSimulator::initProgram() {
	static const GLfloat vertexBufferData[] = {
		-1, -1, -1,
		+1, -1, -1,
		+1, +1, -1,
		+1, +1, -1,
		-1, +1, -1,
		-1, -1, -1,

		+1, -1, -1,
		+1, -1, +1,
		+1, +1, +1,
		+1, +1, +1,
		+1, +1, -1,
		+1, -1, -1,

		-1, +1, -1,
		+1, +1, -1,
		+1, +1, +1,
		+1, +1, +1,
		-1, +1, +1,
		-1, +1, -1,

		+1, -1, +1,
		-1, -1, +1,
		-1, +1, +1,
		-1, +1, +1,
		+1, +1, +1,
		+1, -1, +1,

		-1, -1, +1,
		-1, -1, -1,
		-1, +1, -1,
		-1, +1, -1,
		-1, +1, +1,
		-1, -1, +1,

		-1, -1, -1,
		+1, -1, -1,
		+1, -1, +1,
		+1, -1, +1,
		-1, -1, +1,
		-1, -1, -1,
	};
	static const GLfloat normalBufferData[] = {
		+0, +0, -1,
		+0, +0, -1,
		+0, +0, -1,
		+0, +0, -1,
		+0, +0, -1,
		+0, +0, -1,
		+1, +0, +0,
		+1, +0, +0,
		+1, +0, +0,
		+1, +0, +0,
		+1, +0, +0,
		+1, +0, +0,
		+0, +1, +0,
		+0, +1, +0,
		+0, +1, +0,
		+0, +1, +0,
		+0, +1, +0,
		+0, +1, +0,
		+0, +0, +1,
		+0, +0, +1,
		+0, +0, +1,
		+0, +0, +1,
		+0, +0, +1,
		+0, +0, +1,
		-1, +0, +0,
		-1, +0, +0,
		-1, +0, +0,
		-1, +0, +0,
		-1, +0, +0,
		-1, +0, +0,
		+0, -1, +0,
		+0, -1, +0,
		+0, -1, +0,
		+0, -1, +0,
		+0, -1, +0,
		+0, -1, +0,
	};
	static const GLfloat uvBufferData[] = {
		+1, -1, -1,
		-1, -1, -1,
		-1, -1, +1,
		-1, -1, +1,
		+1, -1, +1,
		+1, -1, -1,

		-1, -1, +1,
		-1, -1, -1,
		-1, +1, -1,
		-1, +1, -1,
		-1, +1, +1,
		-1, -1, +1,

		-1, +1, -1,
		+1, +1, -1,
		+1, +1, +1,
		+1, +1, +1,
		-1, +1, +1,
		-1, +1, -1,

		+1, -1, -1,
		+1, -1, +1,
		+1, +1, +1,
		+1, +1, +1,
		+1, +1, -1,
		+1, -1, -1,

		+1, -1, +1,
		-1, -1, +1,
		-1, +1, +1,
		-1, +1, +1,
		+1, +1, +1,
		+1, -1, +1,

		+1, -1, -1,
		-1, -1, -1,
		-1, +1, -1,
		-1, +1, -1,
		+1, +1, -1,
		+1, -1, -1,
	};

	modelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, -5));
	modelMatrix = glm::rotate(modelMatrix, rotation.x, glm::vec3(1, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, rotation.y, glm::vec3(0, 1, 0));
	this->modelMatrixPtr = glm::value_ptr(modelMatrix);

	this->programID = loadProgram(readFile("drawCube.vert"), readFile("drawCube.frag"));
	this->matrixLocationID = glGetUniformLocation(this->programID, "mvMatrix");
	this->projectionMatrixLocationID = glGetUniformLocation(this->programID, "projectionMatrix");
	this->textureLocationID = glGetUniformLocation(this->programID, "cubeTexture");
	this->sizeLocationID = glGetUniformLocation(this->programID, "size");

	GLuint vertexArrayID;
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);
	this->vertexArrayID = vertexArrayID;

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	GLuint normalbuffer;
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normalBufferData), normalBufferData, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvBufferData), uvBufferData, GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
}

void RubiksCubeSolver::RubiksCubeSimulator::initTexture() {
	cube->SynchronizeData();
	wglMakeCurrent(hDC, hGLRC);
	GLuint cubeTextureID = this->cubeTextureID;
	if (cubeTextureID == UINT_MAX) {
		glGenTextures(1, &cubeTextureID);
		this->cubeTextureID = cubeTextureID;
	}
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeTextureID);
	int width, height, nrChannels;
	for (GLuint i = 0; i < 6; i++) {
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_R8, cube->size, cube->size, 0, GL_RED, GL_UNSIGNED_BYTE, cube->data + cube->size * cube->size * i);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	//cube->MapTexture(cubeTextureID);
	wglMakeCurrent(NULL, NULL);
}

void RubiksCubeSolver::RubiksCubeSimulator::draw()
{
	wglMakeCurrent(hDC, hGLRC);
	glViewport(0, 0, panel1->Width, panel1->Height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(programID);
	glBindVertexArray(vertexArrayID);
	glUniformMatrix4fv(projectionMatrixLocationID, 1, GL_FALSE, projectionMatrixPtr);
	glUniformMatrix4fv(matrixLocationID, 1, GL_FALSE, modelMatrixPtr);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeTextureID);
	glUniform1i(textureLocationID, 0);
	glUniform1i(sizeLocationID, this->checkBox1->Checked ? cube->size : 0);
	glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
	glBindVertexArray(0);

	wglMakeCurrent(NULL, NULL);
	this->UpdateHTM();
	this->UpdateQTM();
}

void RubiksCubeSolver::RubiksCubeSimulator::resize() {
	//glViewport(0, 0, panel1->Width, panel1->Height);
	projectionMatrix = glm::perspective(glm::radians(45.0f), (float)panel1->Width / (float)panel1->Height, 0.1f, 100.0f);
	this->projectionMatrixPtr = glm::value_ptr(projectionMatrix);
}

void RubiksCubeSolver::RubiksCubeSimulator::mouseMove(int x, int y) {
	rotation.x += glm::radians((float)y);
	rotation.y += glm::radians((float)x);
	modelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, -5 * pow(2, zoom)));
	modelMatrix = glm::rotate(modelMatrix, rotation.x, glm::vec3(1, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, rotation.y, glm::vec3(0, 1, 0));
	this->modelMatrixPtr = glm::value_ptr(modelMatrix);
	this->draw();
}

GLuint loadShader(const char* shaderSource, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	//std::cout << shaderSource;
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);
	int compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (!compiled) {
		std::cout << "Error compile shader:" << std::endl;
		GLint infoLen = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
		if (infoLen > 1) {
			char* infoLog = new char[infoLen];
			glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
			std::cout << infoLog << std::endl;
			delete[] infoLog;
		}
		return 0;
	}
	return shader;
}

GLuint loadProgram(const char* vertexShaderSource, const char* fragmentShaderSource)
{
	int vertexShader = loadShader(vertexShaderSource, GL_VERTEX_SHADER);
	int fragmentShader = loadShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
	int program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	int linked;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	if (!linked) {
		std::cout << "Error linking program" << std::endl;
		GLint infoLen = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);
		if (infoLen > 1) {
			char* infoLog = new char[infoLen];
			glGetProgramInfoLog(program, infoLen, NULL, infoLog);
			std::cout << infoLog << std::endl;
			delete[] infoLog;
		}
		glDeleteProgram(program);
		return 0;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return program;
}

const char* readFile(const char* filePath) {
	std::ifstream file(filePath, std::ios::binary);
	int fileSize = file.tellg();
	file.seekg(0, std::ios::end);
	fileSize = (int)file.tellg() - fileSize;
	char *text = new char[fileSize + 1];
	file.seekg(0, std::ios::beg);
	file.read(text, fileSize);
	text[fileSize] = 0;
	return text;
}
