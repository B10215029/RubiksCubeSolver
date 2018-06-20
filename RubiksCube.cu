#include "RubiksCube.h"
#include <string>
#include <iostream>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <GL/glew.h>
#include <cuda_gl_interop.h>

#define THREAD_NUM 1024
#define CHECK {\
	auto e = cudaDeviceSynchronize();\
	if (e != cudaSuccess) {\
		printf("At " __FILE__ ":%d, %s\n", __LINE__, cudaGetErrorString(e));\
	}\
}
__device__ __host__ int CeilDiv(int a, int b) { return (a - 1) / b + 1; }
__device__ __host__ int CeilAlign(int a, int b) { return CeilDiv(a, b) * b; }
void CHECK_CUDA(cudaError_t err) {
	if (err != cudaSuccess) {
		std::cerr << "Error: " << cudaGetErrorString(err) << std::endl;
	}
}

RubiksCube::RubiksCube(int size) {
	this->size = size;
	this->data = new unsigned char[size * size * 6];
	useHost = size < 100;
	cudaDataIndex = 0;
	cudaImageArray = NULL;
	for (int i = 0; i < CUDA_DATA_LEN; i++) {
		cudaMalloc(cudaData + i, sizeof(unsigned char) * size * size * 6);
	}
	if (size == 2) {
		//first face
		condition.push_back(0);
		condition.push_back(0);
		condition.push_back(1);
		condition.push_back(0);
		condition.push_back(2);
		condition.push_back(0);
		condition.push_back(3);
		condition.push_back(0);
		//up edge
		condition.push_back(10);
		condition.push_back(2);
		condition.push_back(11);
		condition.push_back(2);
		//left edge
		condition.push_back(17);
		condition.push_back(4);
		condition.push_back(19);
		condition.push_back(4);
		//down edge
		condition.push_back(20);
		condition.push_back(5);
		condition.push_back(21);
		condition.push_back(5);
		//right edge
		condition.push_back(4);
		condition.push_back(1);
		condition.push_back(6);
		condition.push_back(1);
		
		//up back edge
		condition.push_back(8);
		condition.push_back(2);
		condition.push_back(9);
		condition.push_back(2);
		//left back edge
		condition.push_back(16);
		condition.push_back(4);
		condition.push_back(18);
		condition.push_back(4);
		//down back edge
		condition.push_back(22);
		condition.push_back(5);
		condition.push_back(23);
		condition.push_back(5);
		//right back edge
		condition.push_back(5);
		condition.push_back(1);
		condition.push_back(7);
		condition.push_back(1);
		//back face
		condition.push_back(12);
		condition.push_back(3);
		condition.push_back(13);
		condition.push_back(3);
		condition.push_back(14);
		condition.push_back(3);
		condition.push_back(15);
		condition.push_back(3);
	}
	if (false) {
		int RULDIndex[4] = { 13,22,40,49 };
		int RULDColor[4] = { 1,2,4,5 };
		int crossIndex[4] = { -3,1,3,-1 };
		int cornerIndex[4] = { -4,-2,4,2 };
		int edgeLeft[3] = { -4,-1,2 };
		int edgeRight[3] = { -2,1,4 };
		int edgeUp[3] = { -4,-3,-2 };
		int edgeDown[3] = { 2,3,4 };
		int UDL [3] = { -3,0,3 };
		int RLL [3] = { -1,0,1 };
		int faceIndex = 4;
		int faceColor = 0;
		//F center
		condition.push_back(faceIndex);
		condition.push_back(0);
		//F cross
		for (size_t i = 0; i < 4; i++)
		{
			ConditionPush(condition, faceIndex + crossIndex[i], faceColor);
		}
		//F corner
		for (size_t i = 0; i < 4; i++)
		{
			ConditionPush(condition, faceIndex + cornerIndex[i], faceColor);
		}
		//R edge
		faceColor = 1;
		faceIndex = 13;
		for (size_t i = 0; i < 3; i++)
		{
			ConditionPush(condition, faceIndex + edgeLeft[i], faceColor);
		}
		//U edge
		faceColor = 2;
		faceIndex = 22;
		for (size_t i = 0; i < 3; i++)
		{
			ConditionPush(condition, faceIndex + edgeDown[i], faceColor);
		}
		//L edge
		faceColor = 4;
		faceIndex = 40;
		for (size_t i = 0; i < 3; i++)
		{
			ConditionPush(condition, faceIndex + edgeRight[i], faceColor);
		}
		//D edge
		faceColor = 5;
		faceIndex = 49;
		for (size_t i = 0; i < 3; i++)
		{
			ConditionPush(condition, faceIndex + edgeUp[i], faceColor);
		}
		//ring center
		for (size_t i = 0; i < 4; i++)
		{
			ConditionPush(condition, RULDIndex[i], RULDColor[i]);
		}
		//R middle
		faceColor = 1;
		faceIndex = 13;
		for (size_t i = 0; i < 3; i++)
		{
			ConditionPush(condition, faceIndex + UDL[i], faceColor);
		}
		//U middle
		faceColor = 2;
		faceIndex = 22;
		for (size_t i = 0; i < 3; i++)
		{
			ConditionPush(condition, faceIndex + RLL[i], faceColor);
		}
		//L middle
		faceColor = 4;
		faceIndex = 40;
		for (size_t i = 0; i < 3; i++)
		{
			ConditionPush(condition, faceIndex + UDL[i], faceColor);
		}
		//D middle
		faceColor = 5;
		faceIndex = 49;
		for (size_t i = 0; i < 3; i++)
		{
			ConditionPush(condition, faceIndex + RLL[i], faceColor);
		}
	}
	if (size == 3) {
		int RULDIndex[4] = { 13,22,40,49 };
		int RULDColor[4] = { 1,2,4,5 };
		int RULD2F[4] = { -1,3,1,-3 };
		int RULD2B[4] = { 1,-3,-1,3 };
		int RULD2FRC[4] = { 2,4,-2,-4 };
		int RULD2FLC[4] = { -4,2,4,-2 };
		int RULD2MLE[4] = {-3,-1,3,1};
		int RULD2MRE[4] = { 3,1,-3,-1 };
		int RULD2BRC[4] = {4,-2,-4,2};
		int RULD2BLC[4] = {-2,-4,2,4};

		int crossIndex[4] = { 1,-3,-1,3};
		int cornerIndex[4] = { -2,-4,2,4 };
		int edgeLeft[3] = { -4,-1,2 };
		int edgeRight[3] = { -2,1,4 };
		int edgeUp[3] = { -4,-3,-2 };
		int edgeDown[3] = { 2,3,4 };
		int UDL[3] = { -3,0,3 };
		int RLL[3] = { -1,0,1 };
		int faceIndex = 4;
		int faceColor = 0;
		//F center
		condition.push_back(faceIndex);
		condition.push_back(0);
		//F cross
		for (size_t i = 0; i < 4; i++)
		{
			ConditionPush(condition, faceIndex + crossIndex[i], faceColor);
			ConditionPush(condition, RULDIndex[i]+ RULD2F[i], RULDColor[i]);
		}
		//F conor
		for (size_t i = 0; i < 4; i++)
		{
			int plusIndex = (i + 1) % 4;
			ConditionPush(condition, faceIndex + cornerIndex[i], faceColor);
			ConditionPush(condition, RULDIndex[i] + RULD2FLC[i], RULDColor[i]);
			ConditionPush(condition, RULDIndex[plusIndex] + RULD2FRC[plusIndex], RULDColor[plusIndex]);
		}
		//middle conor
		for (size_t i = 0; i < 4; i++)
		{
			int plusIndex = (i + 1) % 4;
			ConditionPush(condition, RULDIndex[i] + RULD2MLE[i], RULDColor[i]);
			ConditionPush(condition, RULDIndex[plusIndex] + RULD2MRE[plusIndex], RULDColor[plusIndex]);
		}
		//B cross Face
		faceIndex = 31;
		faceColor = 3;
		for (size_t i = 0; i < 4; i++)
		{
			ConditionPush(condition, faceIndex + crossIndex[i], faceColor);
		}
		//B corner Face
		for (size_t i = 0; i < 4; i++)
		{
			ConditionPush(condition, faceIndex + cornerIndex[i], faceColor);
		}
		//RULD B Conr Face
		for (size_t i = 0; i < 4; i++)
		{
			int plusIndex = (i + 1) % 4;
			ConditionPush(condition, RULDIndex[i] + RULD2BLC[i], RULDColor[i]);
			ConditionPush(condition, RULDIndex[plusIndex] + RULD2BRC[plusIndex], RULDColor[plusIndex]);
		}
		//RULD B Cross Face
		for (size_t i = 0; i < 4; i++)
		{
			ConditionPush(condition, RULDIndex[i] + RULD2B[i], RULDColor[i]);
		}
	}
	Reset();
	t = clock();
}

RubiksCube::~RubiksCube() {
	delete[] this->data;
	for (int i = 0; i < CUDA_DATA_LEN; i++) {
		cudaFree(cudaData[i]);
	}
}

__global__ void CudaReset(unsigned char* data, int size) {
	const int index = blockIdx.x * blockDim.x + threadIdx.x;
	unsigned char type = index / (size * size);
	if (type < 6) {
		data[index] = type;
	}
}

void RubiksCube::MapTexture(unsigned char textureID) {
	cudaGraphicsResource *cudaImageResource;
	CHECK_CUDA(cudaGraphicsGLRegisterImage(&cudaImageResource, textureID, GL_TEXTURE_CUBE_MAP, cudaGraphicsRegisterFlagsSurfaceLoadStore));
	CHECK_CUDA(cudaGraphicsMapResources(1, &cudaImageResource, 0));
	CHECK_CUDA(cudaGraphicsSubResourceGetMappedArray(&cudaImageArray, cudaImageResource, 0, 0));
}

void RubiksCube::Reset() {
	this->htm = 0;
	this->qtm = 0;
	this->lastFace = -1;
	if (useHost) {
		memset(this->data + size * size * 0, 0, sizeof(unsigned char) * size * size);
		memset(this->data + size * size * 1, 1, sizeof(unsigned char) * size * size);
		memset(this->data + size * size * 2, 2, sizeof(unsigned char) * size * size);
		memset(this->data + size * size * 3, 3, sizeof(unsigned char) * size * size);
		memset(this->data + size * size * 4, 4, sizeof(unsigned char) * size * size);
		memset(this->data + size * size * 5, 5, sizeof(unsigned char) * size * size);
	} else {
		CudaReset << <dim3(CeilDiv(size * size * 6, THREAD_NUM)), dim3(THREAD_NUM) >> >(cudaData[0], size);
		//for (int i = 1; i < CUDA_DATA_LEN; i++) {
		//	cudaMemcpy(cudaData[i], cudaData[0], sizeof(unsigned char) * size * size * 6, cudaMemcpyDeviceToDevice);
		//}
		//cudaMemcpy(this->data, cudaData[0], sizeof(unsigned char) * size * size * 6, cudaMemcpyDeviceToHost);
	}
	turnNumber = 0;
	turnStacks.clear();
}

void RubiksCube::Shuffle(int time) {
	for (size_t i = 0; i < time; i++)
	{
		int type = rand() % 6;
		int column = (rand() % (int)(size /2))+1;

		int angle = (rand() % 3) + 1;
		Rotate(type, column, angle);
	}
}

void RubiksCube::Solve() {
	turnStacks.clear();
	turnNumber = 0;
	int step = 0;
	t = clock();
	if (size == 2) {
		std::vector<int> types{ 0,1,2 };
		int phase = 1;
		//solve to lasted 2 step
		if (!directSearch2x2Tree(1, 9, -1, types, phase)) {
			std::cout << "faild phase 1 QQ" << std::endl;
		}
		else {
			phase++;
			if (!directSearch2x2Tree(1, 3, -1, types, phase)) {
				std::cout << "faild phase 2 QQ" << std::endl;
			}
		}
		clock_t pass = clock() - t;
		std::cout << "pass time: " << (float)pass / CLOCKS_PER_SEC << " second." << std::endl;
		std::cout << "Stack turn: " << turnNumber << std::endl;
		return;
	}
	else if (size == 3) {
		//simple search in depth 6
		std::vector<int> limit_t{5,4,3,2,1,0 };
		SolveTree(1, 5, -1, condition.size() / 2, limit_t);
		limit_t.pop_back();
		for (size_t i = 0; i <= 21; i++)
		{
			if (!SolveTree(1, 6, -1, i, limit_t)) {
				std::cout << "step " << i << " fail" << std::endl;
				break;
			}
			step = i;
			std::cout << "step " << i << " pass" << std::endl;
		}
		//step 3 solve middle layer coner
		std::cout << "solve middle " << std::endl;
		for (size_t i = step; i <= 29; i++)
		{
			if (!SolveMiddle(1, 3, -1, i)) {
				std::cout << "step " << i << " fail" << std::endl;
				break;
			}
			step = i;
			std::cout << "step " << i << " pass" << std::endl;
		}
		//step 4 B cross face
		std::cout << "solve B cross" << std::endl;
		for (size_t i = step; i <= 33; i++)
		{
			if (!SolveBCross(1, 3, -1, i)) {
				std::cout << "step " << i << " fail" << std::endl;
				break;
			}
			step = i;
			std::cout << "step " << i << " pass" << std::endl;
		}
		//step 5 B Corner face
		if (!SolveBCorner(1, 4, -1, 37)) {
			std::cout << "solve BCorner fail" << std::endl;
		}
		else {
			std::cout << "BCorner pass" << std::endl;
		}
		//step6 B Coner Swape
		if (!SolveBCornerSwap(1, 3, -1, 37 + 8)) {
			std::cout << "solve BCornerSwap fail" << std::endl;
		}
		else {
			std::cout << "solve BCornerSwap pass" << std::endl;
		}
		//step7 B Cross swapeSolveBCrossSwap
		if (!SolveBCrossSwap(1, 2, -1, 37 + 8 + 4)) {
			std::cout << "solve BCrossSwap fail" << std::endl;
		}
		else {
			std::cout << "solve BCrossSwap pass" << std::endl;
		}
		if (isSolved()) {
			std::cout << "solved!!" << std::endl;
		}
		clock_t pass = clock() - t;
		std::cout << "pass time: " << (float)pass / CLOCKS_PER_SEC << " second." << std::endl;
		std::cout << "Stack turn: " << turnNumber << std::endl;
	}
	
}
bool RubiksCube::SolveMiddle(int turn,int maxTurn,int lastFace,int step) {
	if (isSolvedPart(step))
		return true;
	if (turn > maxTurn)
		return false;
	clock_t pass = clock() - t;
	//printf("It took me %d clicks (%f seconds).\n", t, ((float)t) / CLOCKS_PER_SEC);
	if ((float)pass / CLOCKS_PER_SEC > 120) {
		return false;
	}
	std::vector<int> table{ 4,2,1,5 };
	std::vector<int> angles{ 1,2,3 };
	std::random_shuffle(angles.begin(), angles.end());
	for (size_t i = 0; i < table.size(); i++)
	{
		int R = table[(i + 1) % table.size()];
		int F = table[i];
		int L = table[(i - 1 + table.size()) % table.size()];
		int U = 3;
		int D = 0;
		int column = 1;
		for (size_t angle = 0; angle < angles.size(); angle++)
		{
			for (size_t j = 0; j < 2; j++)
			{
				Rotate(U, column, angles[angle]);
				if (j == 0) {
					Rotate(U, column, 1);
					Rotate(R, column, 1);
					Rotate(U, column, 3);
					Rotate(R, column, 3);
					Rotate(U, column, 3);
					Rotate(F, column, 3);
					Rotate(U, column, 1);
					Rotate(F, column, 1);
				}
				else if (j == 1) {
					Rotate(U, column, 3);
					Rotate(L, column, 3);
					Rotate(U, column, 1);
					Rotate(L, column, 1);
					Rotate(U, column, 1);
					Rotate(F, column, 1);
					Rotate(U, column, 3);
					Rotate(F, column, 3);
				}
				if (SolveMiddle(turn + 1, maxTurn, -1, step))
					return true;
				else {
					if (j == 0) {
						for (size_t turnTimes = 0; turnTimes < 8; turnTimes++)
						{
							Undo();
						}
						//Rotate(F, column, 3);
						//Rotate(U, column, 3);
						//Rotate(F, column, 1);
						//Rotate(U, column, 1);
						//Rotate(R, column, 1);
						//Rotate(U, column, 1);
						//Rotate(R, column, 3);
						//Rotate(U, column, 3);
					}
					else if (j == 1) {
						for (size_t turnTimes = 0; turnTimes < 8; turnTimes++)
						{
							Undo();
						}
						//Rotate(F, column, 1);
						//Rotate(U, column, 1);
						//Rotate(F, column, 3);
						//Rotate(U, column, 3);
						//Rotate(L, column, 3);
						//Rotate(U, column, 3);
						//Rotate(L, column, 1);
						//Rotate(U, column, 1);
					}
					Undo();
					//Rotate(U, column, 4 - angles[angle]);
				}
				
			}	
		}
	}
	return false;
}
bool RubiksCube::SolveBCross(int turn, int maxTurn, int lastFace, int step)
{
	if (isSolvedPart(step))
		return true;
	if (turn > maxTurn)
		return false;
	clock_t pass = clock() - t;
	//printf("It took me %d clicks (%f seconds).\n", t, ((float)t) / CLOCKS_PER_SEC);
	if ((float)pass / CLOCKS_PER_SEC > 120) {
		return false;
	}
	std::vector<int> table{ 4,2,1,5 };
	for (size_t i = 0; i < table.size(); i++)
	{
		int R = table[(i + 1) % table.size()];
		int F = table[i];
		int L = table[(i - 1 + table.size()) % table.size()];
		int U = 3;
		int D = 0;
		int column = 1;
		for (size_t j = 0; j < 2; j++)
		{
			Rotate(F, column, 1);
			Rotate(R, column, 1);
			Rotate(U, column, 1);
			Rotate(R, column, 3);
			Rotate(U, column, 3);
			Rotate(F, column, 3);
			if (SolveMiddle(turn + 1, maxTurn, -1, step))
				return true;
			else {
				for (size_t turnTimes = 0; turnTimes < 6; turnTimes++)
				{
					Undo();
				}
				//Rotate(F, column, 1);
				//Rotate(U, column, 1);
				//Rotate(R, column, 1);
				//Rotate(U, column, 3);
				//Rotate(R, column, 3);
				//Rotate(F, column, 3);
			}
		}
	}
	return false;
}
bool RubiksCube::SolveBCorner(int turn, int maxTurn, int lastFace, int step)
{
	if (isSolvedPart(step))
		return true;
	if (turn > maxTurn)
		return false;
	clock_t pass = clock() - t;
	//printf("It took me %d clicks (%f seconds).\n", t, ((float)t) / CLOCKS_PER_SEC);
	if ((float)pass / CLOCKS_PER_SEC > 120) {
		return false;
	}
	std::vector<int> table{ 4,2,1,5 };
	for (size_t i = 0; i < table.size(); i++)
	{
		int R = table[(i + 1) % table.size()];
		int F = table[i];
		int L = table[(i - 1 + table.size()) % table.size()];
		int U = 3;
		int D = 0;
		int column = 1;
		Rotate(R, column, 3);
		Rotate(U, column, 2);
		Rotate(R, column, 1);
		Rotate(U, column, 1);
		Rotate(R, column, 3);
		Rotate(U, column, 1);
		Rotate(R, column, 1);
		if (SolveBCorner(turn + 1, maxTurn, -1, step))
			return true;
		else {
			for (size_t turnTimes = 0; turnTimes < 7; turnTimes++)
			{
				Undo();
			}
			//Rotate(R, column, 3);
			//Rotate(U, column, 3);
			//Rotate(R, column, 1);
			//Rotate(U, column, 3);
			//Rotate(R, column, 3);
			//Rotate(U, column, 2);
			//Rotate(R, column, 1);
		}
	}
	return false;
}
bool RubiksCube::SolveBCornerSwap(int turn, int maxTurn, int lastFace, int step)
{
	if (isSolvedPart(step))
		return true;
	if (turn > maxTurn)
		return false;
	clock_t pass = clock() - t;
	//printf("It took me %d clicks (%f seconds).\n", t, ((float)t) / CLOCKS_PER_SEC);
	if ((float)pass / CLOCKS_PER_SEC > 120) {
		return false;
	}
	std::vector<int> table{ 4,2,1,5 };
	std::vector<int> angles{ 1,2,3 };
	std::random_shuffle(angles.begin(), angles.end());
	for (size_t i = 0; i < table.size(); i++)
	{
		int R = table[(i + 1) % table.size()];
		int F = table[i];
		int L = table[(i - 1 + table.size()) % table.size()];
		int B = table[(i + 2) % table.size()];
		int U = 3;
		int D = 0;
		int column = 1;
		for (size_t angle = 0; angle < angles.size(); angle++)
		{
			Rotate(U, column, angles[angle]);
			Rotate(R, column, 3);
			Rotate(F, column, 1);
			Rotate(R, column, 3);
			Rotate(B, column, 2);
			Rotate(R, column, 1);
			Rotate(F, column, 3);
			Rotate(R, column, 3);
			Rotate(B, column, 2);
			Rotate(R, column, 2);
			if (SolveBCornerSwap(turn + 1, maxTurn, -1, step))
				return true;
			else {
				for (size_t turnTimes = 0; turnTimes < 10; turnTimes++)
				{
					Undo();
				}
				//Rotate(R, column, 2);
				//Rotate(B, column, 2);
				//Rotate(R, column, 1);
				//Rotate(F, column, 1);
				//Rotate(R, column, 3);
				//Rotate(B, column, 2);
				//Rotate(R, column, 1);
				//Rotate(F, column, 3);
				//Rotate(R, column, 1);
				//Rotate(U, column, 4 - angles[angle]);
			}
			
			
		}
		
	}
	return false;
}
bool RubiksCube::SolveBCrossSwap(int turn, int maxTurn, int lastFace, int step)
{
	if (isSolvedPart(step))
		return true;
	if (turn > maxTurn)
		return false;
	clock_t pass = clock() - t;
	//printf("It took me %d clicks (%f seconds).\n", t, ((float)t) / CLOCKS_PER_SEC);
	if ((float)pass / CLOCKS_PER_SEC > 120) {
		return false;
	}
	std::vector<int> table{ 4,2,1,5 };
	for (size_t i = 0; i < table.size(); i++)
	{
		int R = table[(i + 1) % table.size()];
		int F = table[i];
		int L = table[(i - 1 + table.size()) % table.size()];
		int U = 3;
		int D = 0;
		int column = 1;
		Rotate(R, column, 1);
		Rotate(U, column, 3);
		Rotate(R, column, 1);
		Rotate(U, column, 1);
		Rotate(R, column, 1);
		Rotate(U, column, 1);
		Rotate(R, column, 1);
		Rotate(U, column, 3);
		Rotate(R, column, 3);
		Rotate(U, column, 3);
		Rotate(R, column, 2);
		if (SolveBCrossSwap(turn + 1, maxTurn, -1, step))
			return true;
		else {
			for (size_t turnTimes = 0; turnTimes < 11; turnTimes++)
			{
				Undo();
			}
			//Rotate(R, column, 2);
			//Rotate(U, column, 1);
			//Rotate(R, column, 1);
			//Rotate(U, column, 1);
			//Rotate(R, column, 3);
			//Rotate(U, column, 3);
			//Rotate(R, column, 3);
			//Rotate(U, column, 3);
			//Rotate(R, column, 3);
			//Rotate(U, column, 1);
			//Rotate(R, column, 3);
		}
	}
	return false;
}
bool RubiksCube::SolveTree(int turn, int maxTurn,int lastFace,int step, std::vector<int> limit_t)
{
	if (isSolved())
		return true;
	if (isSolvedPart(step))
		return true;
	if (turn > maxTurn)
		return false;
	clock_t pass = clock() - t;
	//printf("It took me %d clicks (%f seconds).\n", t, ((float)t) / CLOCKS_PER_SEC);
	if ((float)pass / CLOCKS_PER_SEC > 120) {
		return false;
	}
	std::vector<int> types = limit_t;
	std::vector<int> angles{ 1,2,3 };
	std::random_shuffle(types.begin(), types.end());
	std::random_shuffle(angles.begin(), angles.end());
	for (size_t type = 0; type < types.size(); type++)
	{
		if (lastFace == types[type])
			continue;
		for (size_t column = 1; column <= (int)(size/2); column++)
		{
			for (size_t angle = 0; angle < angles.size(); angle++)
			{
				Rotate(types[type], column, angles[angle]);
				if (SolveTree(turn + 1, maxTurn, types[type], step, limit_t))
					return true;
				else {
					// Rotate(types[type], column, 4 - angles[angle]);
					Undo();
				}
					
			}
		}
	}
	return false;
}

int RubiksCube::rank2x2()
{
	if (size != 2)return 0;
	int rank = 0;
	int a = 0, b = 0;
	for (size_t i = 0; i < 6; i++)
	{
		//
		a = 0; b = 0;
		a += data[size*size*i + 0] == data[size*size*i + 1] ? 1 : 0;
		a += data[size*size*i + 2] == data[size*size*i + 3] ? 1 : 0;
		b += data[size*size*i + 0] == data[size*size*i + 2] ? 1 : 0;
		b += data[size*size*i + 1] == data[size*size*i + 3] ? 1 : 0;
		if (a == b&&a == 2)
			rank += 100;
		rank += a > b ? a : b;
	}
	return rank;
}

void RubiksCube::ConditionPush(std::vector<int> &v, int index, int color)
{
	v.push_back(index);
	v.push_back(color);
}

void RubiksCube::Rotate(OperateType type, int column, int angle) {
	Rotate((int)type, angle, column);
	
}

__global__ void CudaRotate(unsigned char *dst, unsigned char *src, int size, int type, int column, int angle) {
	// 紀錄每個面周圍有哪幾個面(順時針，上右下左前後)
	static const int relatedFace[6][6] = {
		{ 2, 1, 5, 4, 0, 3 },
		{ 2, 3, 5, 0, 1, 4 },
		{ 3, 1, 0, 4, 2, 5 },
		{ 2, 4, 5, 1, 3, 0 },
		{ 2, 0, 5, 3, 4, 1 },
		{ 0, 1, 3, 4, 5, 2 },
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
	int index = blockIdx.x * blockDim.x + threadIdx.x;
	const unsigned char indexType = index / (size * size);
	if (indexType < 6) {
		const int typeIndex = index % (size * size);
		const int x = typeIndex % size;
		const int y = typeIndex / size;
		unsigned char srcFace, dstFace;
		srcFace = dstFace = relatedFace[type][indexType];
		bool skip = false;

		if (indexType < 4) {
			dstFace = relatedFace[type][(indexType + angle) % 4];
			angle = relatedFaceDirection[type][(indexType + angle) % 4] - relatedFaceDirection[type][indexType];
			if (relatedFaceDirection[type][indexType] == 0) {
				skip = y >= column;
			}
			else if (relatedFaceDirection[type][indexType] == 1) {
				skip = x < size - column;
			}
			else if (relatedFaceDirection[type][indexType] == 2) {
				skip = y < size - column;
			}
			else if (relatedFaceDirection[type][indexType] == 3) {
				skip = x >= column;
			}
		}
		//else if (indexType == 4) {
		//	angle = angle;
		//}
		else if (indexType == 5) {
			angle = 4 - angle;
			skip = size != column;
		}

		int newIndex = index = size * size * srcFace + typeIndex;
		if (!skip) {
			newIndex = size * size * dstFace;
			angle = (angle % 4 + 4) % 4;
			if (angle == 0) newIndex += typeIndex; // y * size + x;
			if (angle == 1) newIndex += x * size + (size - 1 - y);
			if (angle == 2) newIndex += (size - 1 - y) * size + (size - 1 - x);
			if (angle == 3) newIndex += (size - 1 - x) * size + y;
		}
		dst[newIndex] = src[index];
	}
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

void RubiksCube::HostRotate(int type, int column, int angle) {
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
		}
		else if (relatedFaceDirection[type][i] == 1) {
			for (int y = 0; y < size; y++) {
				memcpy(data + size * size * relatedFace[type][i] + size * y + (size - column), buffers[i] + size * y + (size - column), sizeof(unsigned char) * column);
			}
		}
		else if (relatedFaceDirection[type][i] == 2) {
			memcpy(data + size * size * relatedFace[type][i] + size * (size - column), buffers[i] + size * (size - column), sizeof(unsigned char) * size * column);
		}
		else if (relatedFaceDirection[type][i] == 3) {
			for (int y = 0; y < size; y++) {
				memcpy(data + size * size * relatedFace[type][i] + size * y, buffers[i] + size * y, sizeof(unsigned char) * column);
			}
		}
		delete[] buffers[i];
	}
}

void RubiksCube::Rotate(int type, int column, int angle, bool unredo) {
	htm += lastFace != type;
	lastFace = type;
	qtm += (angle == 2) + 1;
	if (useHost) {
		HostRotate(type, column, angle);
	} else {
		unsigned char* src = GetCudaData();
		SwitchCudaData();
		unsigned char* dst = GetCudaData();
		CudaRotate << <dim3(CeilDiv(size * size * 6, THREAD_NUM)), dim3(THREAD_NUM) >> >(dst, src, size, type, column, angle);
	}
	if (!unredo) {
		
		turnStacks.resize(turnNumber);
		turnNumber++;
		turnStacks.push_back(turn{ (int)type,angle,column });
	}
	
}

void RubiksCube::Redo() {
	// TODO
	if (turnNumber >= turnStacks.size())
		return;
	Rotate(turnStacks[turnNumber].t, turnStacks[turnNumber].c, turnStacks[turnNumber].a,true);
	//std::cout << turnStacks[turnNumber].t << turnStacks[turnNumber].c << turnStacks[turnNumber].a;
	turnNumber++;
}

void RubiksCube::Undo() {
	// TODO
	if (turnNumber <= 0)
		return;
	turnNumber--;
	Rotate(turnStacks[turnNumber].t, turnStacks[turnNumber].c, 4-turnStacks[turnNumber].a,true);
	//std::cout << turnStacks[turnNumber].t << turnStacks[turnNumber].c << turnStacks[turnNumber].a;
}

unsigned char* RubiksCube::SynchronizeData() const {
	if (useHost) {
		cudaMemcpy(GetCudaData(), this->data, sizeof(unsigned char) * size * size * 6, cudaMemcpyHostToDevice);
	} else {
		cudaMemcpy(this->data, GetCudaData(), sizeof(unsigned char) * size * size * 6, cudaMemcpyDeviceToHost);
	}
	if (cudaImageArray) {
		cudaMemcpyToArray(cudaImageArray, 0, 0, GetCudaData(), sizeof(unsigned char) * size * size * 6, cudaMemcpyDeviceToDevice);
	}
	return data;
}

bool RubiksCube::isSolved()
{
	int tables[6];
	for (size_t i = 0; i < 6; i++)
	{
		tables[i] = data[size*size * i];
	}
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			if (data[size*size * 0 + size*i + j] != tables[0])return false;
			if (data[size*size * 1 + size*i + j] != tables[1])return false;
			if (data[size*size * 2 + size*i + j] != tables[2])return false;
			if (data[size*size * 3 + size*i + j] != tables[3])return false;
			if (data[size*size * 4 + size*i + j] != tables[4])return false;
			if (data[size*size * 5 + size*i + j] != tables[5])return false;
		}
	}
	return true;
}

bool RubiksCube::isSolvedPart(int step)
{
	if (size == 2) {
		bool flag = true;
		for (size_t i = 0; i < step; i++)
		{
			if (data[condition[i * 2]] != condition[i * 2 + 1]) {
				flag = false;
				break;
			}
		}
		return flag;
	}
	if (size == 3) {
		bool flag = true;
		for (size_t i = 0; i < step; i++)
		{
			if (data[condition[i * 2]] != condition[i * 2 + 1]) {
				flag = false;
				break;
			}
		}
		return flag;
	}
	return false;
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

bool RubiksCube::directSearch2x2Tree(int turn, int maxTurn, int lastFace, std::vector<int> types,int phase)
{
	if (phase == 1) {
		if (rank2x2() == 212)//in that condition we can solve in 4 step;
			return true;
	}else if(phase == 2)
		if (isSolved())//in that condition we can solve in 4 step;
			return true;
	if (turn > maxTurn)
		return false;
	//clock_t pass = clock() - t;
	//printf("It took me %d clicks (%f seconds).\n", t, ((float)t) / CLOCKS_PER_SEC);
	//if ((float)pass / CLOCKS_PER_SEC > 120) {
	//	return false;
	//}
	std::vector<int> angles{ 1,2,3 };
	std::random_shuffle(types.begin(), types.end());
	std::random_shuffle(angles.begin(), angles.end());
	for (size_t type = 0; type < types.size(); type++)
	{
		if (lastFace == types[type])
			continue;
		for (size_t column = 1; column <= (int)(size / 2); column++)
		{
			for (size_t angle = 0; angle < angles.size(); angle++)
			{
				Rotate(types[type], column, angles[angle]);
				if (directSearch2x2Tree(turn + 1, maxTurn, types[type], types, phase))
					return true;
				else {
					Undo();
					//Rotate(types[type], column, 4 - angles[angle]);
				}
					
			}
		}
	}
	return false;
}

std::ostream& operator<<(std::ostream& outputStream, const RubiksCube& cube) {
	static const char color[] = { 'G', 'R', 'W', 'B', 'O', 'Y' };
	std::string padding(cube.size * 2, ' ');
	cube.SynchronizeData();
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
