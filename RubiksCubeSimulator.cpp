#include "RubiksCubeSimulator.h"
#include <iostream>
#include <Windows.h>
#include <gl\GL.h>

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

	glViewport(0, 0, panel1->Width, panel1->Height);
	glClearColor(0, 0, 0, 1);
	//glEnable(GL_TEXTURE_2D);
	//glPixelStorei(GL_PACK_ALIGNMENT, 1);
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	wglMakeCurrent(NULL, NULL);

	return hGLRC;
}

void DrawTile(int type, double x, double y, double size) {
	// 從代號對應到顏色
	static const float colorR[] = { 0.0, 1.0, 1.0, 0.0, 1.0, 1.0 };
	static const float colorG[] = { 1.0, 0.0, 1.0, 0.0, 0.5, 1.0 };
	static const float colorB[] = { 0.0, 0.0, 1.0, 1.0, 0.0, 0.0 };
	// 從影像處理坐標系轉到OpenGL坐標系
	x = x * 2.0 - 1.0;
	y = 1.0 - y * 8.0 / 3.0;
	size = size * 2.0;
	double sizeY = size * 4.0 / 3.0;
	// 畫方塊
	glColor3f(colorR[type], colorG[type], colorB[type]);
	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x, y - sizeY);
	glVertex2f(x + size, y - sizeY);
	glVertex2f(x + size, y);
	glEnd();
}

void RubiksCubeSolver::RubiksCubeSimulator::draw()
{
	wglMakeCurrent(hDC, hGLRC);
	glViewport(0, 0, panel1->Width, panel1->Height);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	double tileSize = 0.25 / cube->size;
	for (int subY = 0; subY < cube->size; subY++) {
		for (int subX = 0; subX < cube->size; subX++) {
			DrawTile(cube->data[cube->size * cube->size * 2 + cube->size * subY + subX], (subX + cube->size) * tileSize, subY * tileSize, tileSize);
		}
	}
	for (int subY = 0; subY < cube->size; subY++) {
		for (int subX = 0; subX < cube->size; subX++)
			DrawTile(cube->data[cube->size * cube->size * 4 + cube->size * subY + subX], (subX + cube->size * 0) * tileSize, (subY + cube->size) * tileSize, tileSize);
		for (int subX = 0; subX < cube->size; subX++)
			DrawTile(cube->data[cube->size * cube->size * 0 + cube->size * subY + subX], (subX + cube->size * 1) * tileSize, (subY + cube->size) * tileSize, tileSize);
		for (int subX = 0; subX < cube->size; subX++)
			DrawTile(cube->data[cube->size * cube->size * 1 + cube->size * subY + subX], (subX + cube->size * 2) * tileSize, (subY + cube->size) * tileSize, tileSize);
		for (int subX = 0; subX < cube->size; subX++)
			DrawTile(cube->data[cube->size * cube->size * 3 + cube->size * subY + subX], (subX + cube->size * 3) * tileSize, (subY + cube->size) * tileSize, tileSize);
	}
	for (int subY = 0; subY < cube->size; subY++) {
		for (int subX = 0; subX < cube->size; subX++) {
			DrawTile(cube->data[cube->size * cube->size * 5 + cube->size * subY + subX], (subX + cube->size) * tileSize, (subY + cube->size * 2) * tileSize, tileSize);
		}
	}

	wglMakeCurrent(NULL, NULL);
}
