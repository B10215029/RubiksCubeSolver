#pragma once
#include <iostream>
#include <vector>
#include <algorithm>    // std::random_shuffle
#include <time.h>
#include <cuda_runtime.h>
#define CUDA_DATA_LEN 2
struct turn
{
	int a;
	int t;
	int c;
	turn() {
		a = 0; t = 0; c = 0;
	}
	turn(int type, int angle, int colum) {
		a = angle; t = type; c = colum;
	}
};
class RubiksCube {
public:
	//   U
	// L F R B
	//   D
	enum OperateType { F, R, U, B, L, D, X, Y, Z };
	int htm;
	int qtm;
	int size;
	//   2
	// 4 0 1 3
	//   5
	unsigned char* data;
	unsigned char* cudaData[CUDA_DATA_LEN];
	bool useHost;
	int cudaDataIndex;
	cudaArray *cudaImageArray;
	RubiksCube(int size);
	~RubiksCube();
	void MapTexture(unsigned char textureID);
	void Reset();
	void Shuffle(int time);
	void Solve();
	/// <summary>
	/// 旋轉某個面
	/// </summary>
	/// <param name="type">要轉的面</param>
	/// <param name="column">轉第幾列(從右邊數)</param>
	/// <param name="angle">順時針轉幾度(1 = 90, 2 = 180, 3 = 270)</param>
	void Rotate(OperateType type, int column = 0, int angle = 1);
	/// <summary>
	/// 旋轉某個面
	/// </summary>
	/// <param name="type">要轉的面</param>
	/// <param name="column">轉第幾列(從右邊數)</param>
	/// <param name="angle">順時針轉幾度(1 = 90, 2 = 180, 3 = 270)</param>
	void Rotate(int type, int column = 1, int angle = 1,bool unredo=false);
	void HostRotate(int type, int column, int angle);
	void Redo();
	void Undo();
	unsigned char* SynchronizeData() const;
	inline unsigned char* GetCudaData() const { return cudaData[cudaDataIndex]; };
	inline int SwitchCudaData() { return cudaDataIndex = (cudaDataIndex + 1) % CUDA_DATA_LEN; };
	friend std::ostream& operator<<(std::ostream& outputStream, const RubiksCube& cube);
	bool isSolved();
	bool isSolvedPart(int step);
	bool checkMe();
	bool directSearch2x2Tree(int turn, int maxTurn, int lastFace, std::vector<int> types,int phase);
	bool SolveTree(int turn, int maxTurn, int lastFace,int step, std::vector<int> limit_t);
	int rank2x2();
	void ConditionPush(std::vector<int> &v, int index, int color);
	bool SolveMiddle(int turn, int maxTurn, int lastFace, int step);
	bool SolveBCross(int turn, int maxTurn, int lastFace, int step);
	bool SolveBCorner(int turn, int maxTurn, int lastFace, int step);
	bool SolveBCornerSwap(int turn, int maxTurn, int lastFace, int step);
	bool SolveBCrossSwap(int turn, int maxTurn, int lastFace, int step);
	std::vector<int> condition;
	clock_t t;
	std::vector<turn> turnStacks;
	int turnNumber;
private:
	int lastFace;
};
