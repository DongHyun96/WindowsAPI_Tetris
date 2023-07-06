#include "Framework.h"
#include "TetrisScene.h"


TetrisScene::TetrisScene()
{
	for (int y = 0; y < BOARD_HEIGHT; y++)
	{
		for (int x = 0; x < BOARD_WIDTH; x++)
		{
			Point pos = ArrayPosToWorldPos(x, y);

			if (x == 0 || x == BOARD_WIDTH - 1 || y == BOARD_HEIGHT - 1)
				board[y][x] = Rect(pos, Point(RECT_SIZE, RECT_SIZE), WALL, brushMap[WALL]);
			else
				board[y][x] = Rect(pos, Point(RECT_SIZE, RECT_SIZE), NONE, brushMap[NONE]);
		}
	}
}

TetrisScene::~TetrisScene()
{
	for (pair<BlockType, HBRUSH> pair : brushMap)
		DeleteObject(pair.second);

	brushMap.clear();
}

void TetrisScene::Update()
{
}

void TetrisScene::Render(HDC hdc)
{
	//Rectangle(hdc, 0, 0, 20, 20);
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
			board[i][j].Render(hdc);
	}
}

Point TetrisScene::ArrayPosToWorldPos(int x, int y)
{
	return Point((x + 0.5f) * RECT_SIZE, (y - 3.5f) * RECT_SIZE);
}

InputKey TetrisScene::GetPlayerInput()
{
	return IDLE;
}
