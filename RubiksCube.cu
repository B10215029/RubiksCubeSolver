#include "RubiksCube.h"
#include <string>
#include <iostream>

RubiksCube::RubiksCube(int size) {
	this->size = size;
	this->data = new unsigned char[size * size * 6];
	Reset();
}

RubiksCube::~RubiksCube() {
	delete[] this->data;
}

void RubiksCube::Reset() {
	this->htm = 0;
	this->qtm = 0;
	this->lastFace = -1;
	memset(this->data + size * size * 0, 0, sizeof(unsigned char) * size * size);
	memset(this->data + size * size * 1, 1, sizeof(unsigned char) * size * size);
	memset(this->data + size * size * 2, 2, sizeof(unsigned char) * size * size);
	memset(this->data + size * size * 3, 3, sizeof(unsigned char) * size * size);
	memset(this->data + size * size * 4, 4, sizeof(unsigned char) * size * size);
	memset(this->data + size * size * 5, 5, sizeof(unsigned char) * size * size);
}

void RubiksCube::Shuffle() {
	for (size_t i = 0; i < 200; i++)
	{
		int type = rand() % 6;
		int column = (rand() % (size - 1)) + 1;
		int angle = (rand() % 3) + 1;
		Rotate(type, column, angle);
	}
}

void RubiksCube::Solve() {
	if (SolveTree(1, 15)) {
		std::cout << "success" << std::endl;
	}
	else {
		std::cout << "fail" << std::endl;
	}
}

bool RubiksCube::SolveTree(int turn, int maxTurn)
{
	if (turn > maxTurn)
		return false;
	for (size_t type = 0; type < 6; type++)
	{
		for (size_t column = 1; column < size; column++)
		{
			for (size_t angle = 1; angle < 4; angle++)
			{
				Rotate(type, column, angle);
				if (isSolved())
					return true;
				else if (SolveTree(turn + 1, maxTurn))
					return true;
				else
					Rotate(type, column, 4 - angle);
			}
		}
	}
	return false;
}

void RubiksCube::Rotate(OperateType type, int column, int angle) {
	Rotate((int)type, angle, column);
}

// 把矩陣旋轉然後寫到另一個矩陣
void RotateArray(unsigned char *dst, unsigned char *src, int size, int angle) {
	angle = (angle % 4 + 4) % 4;
	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			int index = y * size + x;
			int newIndex = 0;
			if (angle == 0) newIndex = y * size + x;
			if (angle == 1) newIndex = x * size + (size - 1 - y);
			if (angle == 2) newIndex = (size - 1 - y) * size + (size - 1 - x);
			if (angle == 3) newIndex = (size - 1 - x) * size + y;
			dst[newIndex] = src[index];
		}
	}
}

// 紀錄每個面周圍有哪幾個面(順時針，上右下左)
static const int relatedFace[6][4] = {
	{ 2, 1, 5, 4 },
	{ 2, 3, 5, 0 },
	{ 3, 1, 0, 4 },
	{ 2, 4, 5, 1 },
	{ 2, 0, 5, 3 },
	{ 0, 1, 3, 4 },
};

// 紀錄每個面周圍的面與自己相連的方向
static const int relatedFaceDirection[6][4] = {
	{ 2, 3, 0, 1 },
	{ 1, 3, 1, 1 },
	{ 0, 0, 0, 0 },
	{ 0, 3, 2, 1 },
	{ 3, 3, 3, 1 },
	{ 2, 2, 2, 2 },
};

void RubiksCube::Rotate(int type, int column, int angle) {
	htm += lastFace != type;
	lastFace = type;
	qtm += (angle == 2) + 1;
	// 旋轉整個面
	unsigned char *buffer = new unsigned char[size * size];
	RotateArray(buffer, data + size * size * type, size, angle);
	memcpy(data + (size * size * type), buffer, sizeof(unsigned char) * size * size);
	delete[] buffer;
	// 旋轉與面相鄰的其他面的列
	unsigned char *buffers[4];
	// 將整個面旋轉後存到buffers中
	for (int i = 0; i < 4; i++) {
		int dst = (i + angle) % 4;
		buffers[dst] = new unsigned char[size * size];
		RotateArray(buffers[dst], data + size * size * relatedFace[type][i], size, relatedFaceDirection[type][dst] - relatedFaceDirection[type][i]);
	}
	// 依據column將適量的資料存回data中
	for (int i = 0; i < 4; i++) {
		if (relatedFaceDirection[type][i] == 0) {
			memcpy(data + size * size * relatedFace[type][i], buffers[i], sizeof(unsigned char) * size * column);
		} else if (relatedFaceDirection[type][i] == 1) {
			for (int y = 0; y < size; y++) {
				memcpy(data + size * size * relatedFace[type][i] + size * y + (size - column), buffers[i] + size * y + (size - column), sizeof(unsigned char) * column);
			}
		} else if (relatedFaceDirection[type][i] == 2) {
			memcpy(data + size * size * relatedFace[type][i] + size * (size - column), buffers[i] + size * (size - column), sizeof(unsigned char) * size * column);
		} else if (relatedFaceDirection[type][i] == 3) {
			for (int y = 0; y < size; y++) {
				memcpy(data + size * size * relatedFace[type][i] + size * y, buffers[i] + size * y, sizeof(unsigned char) * column);
			}
		}
		delete[] buffers[i];
	}
}

void RubiksCube::Redo() {
	// TODO
}

void RubiksCube::Undo() {
	// TODO
}

bool RubiksCube::isSolved()
{
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			if (data[size*size * 0 + size*i + j] != 0)return false;
			if (data[size*size * 1 + size*i + j] != 1)return false;
			if (data[size*size * 2 + size*i + j] != 2)return false;
			if (data[size*size * 3 + size*i + j] != 3)return false;
			if (data[size*size * 4 + size*i + j] != 4)return false;
			if (data[size*size * 5 + size*i + j] != 5)return false;
		}
	}
	return true;
}

bool RubiksCube::checkMe()
{
	int t[100];
	int a[100];
	int c[100];
	std::cout << *this;
	for (size_t i = 0; i < 100; i++)
	{
		t[i] = rand() % 6;
		a[i] = (rand() % 3) + 1;
		c[i] = (rand() % (size - 1)) + 1;
		//	std::cout << cube;
	}
	for (size_t i = 0; i < 100; i++)
	{
		Rotate(t[i], c[i], a[i]);
	}
	std::cout << *this;
	for (size_t i = 0; i < 100; i++)
	{
		int index = 99 - i;
		Rotate(t[index], c[index], 4 - a[index]);
	}
	std::cout << *this;
	return false;
}

std::ostream& operator<<(std::ostream& outputStream, const RubiksCube& cube) {
	static const char color[] = { 'G', 'R', 'W', 'B', 'O', 'Y' };
	std::string padding(cube.size * 2, ' ');
	for (int i = 0; i < cube.size; i++) {
		outputStream << padding;
		for (int j = 0; j < cube.size; j++) {
			outputStream << color[cube.data[cube.size * cube.size * 2 + cube.size * i + j]] << ' ';
		}
		outputStream << std::endl;
	}
	for (int i = 0; i < cube.size; i++) {
		for (int j = 0; j < cube.size; j++) outputStream << color[cube.data[cube.size * cube.size * 4 + cube.size * i + j]] << ' ';
		for (int j = 0; j < cube.size; j++) outputStream << color[cube.data[cube.size * cube.size * 0 + cube.size * i + j]] << ' ';
		for (int j = 0; j < cube.size; j++) outputStream << color[cube.data[cube.size * cube.size * 1 + cube.size * i + j]] << ' ';
		for (int j = 0; j < cube.size; j++) outputStream << color[cube.data[cube.size * cube.size * 3 + cube.size * i + j]] << ' ';
		outputStream << std::endl;
	}
	for (int i = 0; i < cube.size; i++) {
		outputStream << padding;
		for (int j = 0; j < cube.size; j++) {
			outputStream << color[cube.data[cube.size * cube.size * 5 + cube.size * i + j]] << ' ';
		}
		outputStream << std::endl;
	}
	outputStream << "htm: " << cube.htm << ", qtm: " << cube.qtm << std::endl;
	return outputStream;
}
