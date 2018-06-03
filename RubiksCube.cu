#include "RubiksCube.h"
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
	// TODO
	for (int i = 0; i < cube.size * cube.size * 6; i++) {
		outputStream << color[cube.data[i]];
		if ((i + 1) % (cube.size * cube.size) == 0) {
			outputStream << std::endl;
		}
	}
	return outputStream;
}
