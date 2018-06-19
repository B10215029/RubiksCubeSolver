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
	return 0;
}
