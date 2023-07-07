#pragma once

class Rect;

enum BlockType
{
	I_MINO,
	Z_MINO,
	N_MINO,
	O_MINO,
	J_MINO,
	L_MINO,
	T_MINO,
	WALL,
	NONE
};

class Mino
{
public:
	Mino();
	Mino(const BlockType& type, const Coord& mainPos);
	~Mino();

	bool RotateMino(const Rect (*board)[BOARD_WIDTH]);
	
	bool MoveLeft(const Rect (*board)[BOARD_WIDTH]);
	bool MoveRight(const Rect (*board)[BOARD_WIDTH]);

	bool MoveDown(const Rect (*board)[BOARD_WIDTH]);
	
	BlockType				GetType()				const	{ return type; }
	Coord					GetMainPos()			const	{ return mainPos; }
	vector<vector<Coord>>	GetMinos()				const	{ return minos; }
	vector<Coord>			GetCurrentCoords()		const	{ return minos[curIdx]; }
	int						GetCurIdx()				const	{ return curIdx; }

private:

	BlockType type = NONE;

	Coord mainPos = {}; // Array Coord

	/// <summary> vector < mainPos와의 상대좌표값 >  > </summary>
	vector<vector<Coord>> minos = {};
	
	UINT curIdx = 0;

	bool IsValidCoord(const Coord& coord, const Rect (*board)[BOARD_WIDTH]) const;
	bool IsValidCoord(const Coord& coord, const UINT& minoIdx, const Rect (*board)[BOARD_WIDTH]) const;
};
