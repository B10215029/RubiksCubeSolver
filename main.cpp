#include "RubiksCube.h"
#include <iostream>
#include <cstdlib>

int main() {
	RubiksCube cube(3);
	std::cout << cube;
	cube.Rotate(0);
	cube.Rotate(RubiksCube::OperateType::B);
	system("pause");
	return 0;
}
