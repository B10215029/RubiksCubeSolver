#include "RubiksCube.h"
#include <string>
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
	memset(this->data + size * size * 0, 0, sizeof(unsigned char) * size * size);
	memset(this->data + size * size * 1, 1, sizeof(unsigned char) * size * size);
	memset(this->data + size * size * 2, 2, sizeof(unsigned char) * size * size);
	memset(this->data + size * size * 3, 3, sizeof(unsigned char) * size * size);
	memset(this->data + size * size * 4, 4, sizeof(unsigned char) * size * size);
	memset(this->data + size * size * 5, 5, sizeof(unsigned char) * size * size);
}

void RubiksCube::Shuffle() {
	// TODO
}

void RubiksCube::Solve() {
	// TODO
}

void RubiksCube::Rotate(OperateType type, int column, int angle) {
	Rotate((int)type, angle, column);
}

void RubiksCube::Rotate(int type, int column, int angle) {
	// TODO
}

void RubiksCube::Redo() {
	// TODO
}

void RubiksCube::Undo() {
	// TODO
}

std::ostream& operator<<(std::ostream& outputStream, const RubiksCube& cube) {
	static const char color[] = {'G', 'R', 'W', 'Y', 'O', 'B'};
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
		for (int j = 0; j < cube.size; j++) outputStream << color[cube.data[cube.size * cube.size * 5 + cube.size * i + j]] << ' ';
		outputStream << std::endl;
	}
	for (int i = 0; i < cube.size; i++) {
		outputStream << padding;
		for (int j = 0; j < cube.size; j++) {
			outputStream << color[cube.data[cube.size * cube.size * 3 + cube.size * i + j]] << ' ';
		}
		outputStream << std::endl;
	}
	return outputStream;
}
