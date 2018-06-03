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
	/// ����Y�ӭ�
	/// </summary>
	/// <param name="type">�n�઺��</param>
	/// <param name="column">��ĴX�C(�q�k���)</param>
	/// <param name="angle">���ɰw��X��(1 = 90, 2 = 180, 3 = 270)</param>
	void Rotate(OperateType type, int column = 0, int angle = 1);
	/// <summary>
	/// ����Y�ӭ�
	/// </summary>
	/// <param name="type">�n�઺��</param>
	/// <param name="column">��ĴX�C(�q�k���)</param>
	/// <param name="angle">���ɰw��X��(1 = 90, 2 = 180, 3 = 270)</param>
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
