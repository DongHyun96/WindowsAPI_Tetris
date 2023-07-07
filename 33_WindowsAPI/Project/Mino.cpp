#include "Framework.h"
#include "Mino.h"


Mino::Mino()
{
}

Mino::Mino(const BlockType& type, const Coord& mainPos)
	:type(type), mainPos(mainPos)
{
	switch (type)
	{
	case I_MINO:
		minos =
		{
			{{0, -1}, {0, 0}, {0, 1}, {0, 2}},
			{{-1, 0}, {0, 0}, {1, 0}, {2, 0}},
			{{1, -1}, {1, 0}, {1, 1}, {1, 2}},
			{{-1, 1}, {0, 1}, {1, 1}, {2, 1}},
		};

		break;
	case Z_MINO:
		minos =
		{
			{{-1, -1},	{0, -1},	{0, 0},		{1, 0}},
			{{1, -1},	{1, 0},		{0, 0},		{0, 1}},
			{{-1, 0},	{0, 0},		{0, 1},		{1, 1}},
			{{0, -1},	{0, 0},		{-1, 0},	{-1, 1}},
		};
		break;
	case N_MINO:
		minos =
		{
			{{-1, 0}, {0, 0}, {0, -1}, {1, -1}},
			{{0, -1}, {0, 0}, {1, 0},  {1, 1}},
			{{-1, 1}, {0, 1}, {0, 0},  {1, 0}},
			{{0, -1}, {0, 0}, {-1, 0}, {-1, 1}},
		};
		break;
	case O_MINO:
		minos =
		{
			{{0, 0}, {1, 0}, {0, 1}, {1, 1}}
		};
		break;
	case J_MINO:
		minos =
		{
			{{0, -1}, {0, 0}, {0, 1}, {-1, 1}},
			{{-1, -1}, {-1, 0}, {0, 0}, {1, 0}},
			{{1, -1}, {0, -1}, {0, 0}, {0, 1}},
			{{-1, 0}, {0, 0}, {1, 0}, {1, 1}},
		};
		break;
	case L_MINO:
		minos =
		{
			{{0, -1}, {0, 0}, {0, 1}, {1, 1}},
			{{-1, 1}, {-1, 0}, {0, 0}, {1, 0}},
			{{-1, -1}, {0, -1}, {0, 0}, {0, 1}},
			{{-1, 0}, {0, 0}, {1, 0}, {1, -1}},
		};
		break;
	case T_MINO:
		minos =
		{
			{{-1, 0}, {0, 0}, {1, 0}, {0, 1}},
			{{0, -1}, {0, 0}, {0, 1}, {-1, 0}},
			{{-1, 0}, {0, 0}, {1, 0}, {0, -1}},
			{{0, -1}, {0, 0}, {0, 1}, {1, 0}},
		};
		break;
	default:
		break;
	}
}


Mino::~Mino()
{
}

bool Mino::RotateMino(const Rect(*board)[BOARD_WIDTH])
{
	UINT attemptCnt = 0;
	UINT nextIdx = curIdx;

	while (attemptCnt < minos.size())
	{
		nextIdx = (nextIdx + 1 < minos.size()) ? nextIdx + 1 : 0; // 다음 모양의 idx

		if (IsValidCoord(mainPos, nextIdx, board)) // 다음 모양이 겹치는 부분이 없다면 valid
		{
			curIdx = nextIdx;
			return true;
		}

		// 현재 다음으로 회전할 수 없는 위치라면 오른쪽이나 왼쪽으로 한칸 이동하여 회전해봄, 왼쪽 오른쪽 차례로 시도
		for (int i = -1; i <= 1; i += 2)
		{
			Coord tempPos = { mainPos.x + i, mainPos.y };

			if (IsValidCoord(tempPos, nextIdx, board))
			{
				mainPos = tempPos;
				curIdx = nextIdx;
				return true;
			}
		}
		attemptCnt++;
	}

	return false;
}

bool Mino::MoveLeft(const Rect(*board)[BOARD_WIDTH])
{
	Coord nextPos = { mainPos.x - 1, mainPos.y };

	// Check if nextPos is valid
	if (!IsValidCoord(nextPos, board))
		return false;

	mainPos = nextPos; // Update mainPos

	return true;
}

bool Mino::MoveRight(const Rect(*board)[BOARD_WIDTH])
{
	Coord nextPos = { mainPos.x + 1, mainPos.y };

	// Check if nextPos is valid
	if (!IsValidCoord(nextPos, board))
		return false;

	mainPos = nextPos; // Update mainPos

	return true;
}

bool Mino::MoveDown(const Rect (*board)[BOARD_WIDTH])
{
	Coord nextPos = { mainPos.x, mainPos.y + 1 };
	
	// Check if nextPos is valid
	if (!IsValidCoord(nextPos, board))
		return false;

	mainPos = nextPos; // Update mainPos

	return true;
}

bool Mino::IsValidCoord(const Coord& coord, const Rect(*board)[BOARD_WIDTH]) const
{
	// Check if nextPos is valid
	for (const Coord& blockCoord : minos[curIdx])
	{
		UINT y = coord.y + blockCoord.y;
		UINT x = coord.x + blockCoord.x;

		// Check range
		if (x < 0 || x >= BOARD_WIDTH || y < 0 || y >= BOARD_HEIGHT)
			return false;

		BlockType t = board[y][x].GetType();

		if (t != NONE) // Hit mino or wall
			return false;
	}
	return true;
}

bool Mino::IsValidCoord(const Coord& coord, const UINT& minoIdx, const Rect(*board)[BOARD_WIDTH]) const
{
	// Check if nextPos is valid
	for (const Coord& blockCoord : minos[minoIdx])
	{
		UINT y = coord.y + blockCoord.y;
		UINT x = coord.x + blockCoord.x;

		// Check range
		if (x < 0 || x >= BOARD_WIDTH || y < 0 || y >= BOARD_HEIGHT)
			return false;

		BlockType t = board[y][x].GetType();

		if (t != NONE) // Hit mino or wall
			return false;
	}
	return true;
}
