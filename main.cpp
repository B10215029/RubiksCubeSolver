#include "RubiksCube.h"
#include <iostream>
#include <cstdlib>

int main() {
	RubiksCube cube(3);
	std::cout << cube;
	int type;
	int column;
	int angle;
	while (true) {
		std::cin >> type >> column >> angle;
		cube.Rotate(type, column, angle);
		std::cout << cube;
	}
	//cube.Rotate(RubiksCube::OperateType::B);
	system("pause");
	return 0;
}
