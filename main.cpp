#include "RubiksCube.h"
#include "RubiksCubeSimulator.h"
#include <iostream>
#include <cstdlib>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
int main() {
	srand(time(NULL));
	RubiksCubeSolver::RubiksCubeSimulator form;
	System::Windows::Forms::Application::Run(%form);
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
