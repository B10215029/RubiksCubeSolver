#pragma once
#include <iostream>

class RubiksCube {
public:
	//   U
	// L F R D
	//   B
	enum OperateType { F, R, U, B, L, D, X, Y, Z };
	int htm;
	int qtm;
	int size;
	RubiksCube(int size);
	~RubiksCube();
	void Reset();
	void Shuffle();
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
	void Rotate(int type, int column = 0, int angle = 1);
	void Redo();
	void Undo();
	friend std::ostream& operator<<(std::ostream& outputStream, const RubiksCube& cube);

private:
	//   2
	// 4 0 1 5
	//   3
	unsigned char* data;
};
