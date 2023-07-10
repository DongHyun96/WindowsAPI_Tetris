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

	currentMino = GenerateMino();
}

TetrisScene::~TetrisScene()
{
	for (pair<BlockType, HBRUSH> pair : brushMap)
		DeleteObject(pair.second);

	brushMap.clear();
}

void TetrisScene::Update()
{
	float deltaTime = GetDeltaTime();

	if (gameState == GAME_OVER)
	{
		// Game Over
	}

	// Check board made
	CheckBoardMade();

	// Currently Row_Made, update the color
	if (gameState == ROW_MADE)
	{
		rowMadeTick += deltaTime;

		bool isOwnColor  = (rowMadeTick <= ROW_MADE_TICK_LIMIT * 0.25)	? false	:
						   (rowMadeTick <= ROW_MADE_TICK_LIMIT * 0.5)	? true  :
						   (rowMadeTick <= ROW_MADE_TICK_LIMIT * 0.75)	? false	: true;

		ChangeRowColor(isOwnColor);

		if (rowMadeTick >= ROW_MADE_TICK_LIMIT)
		{
			// Update board and add score here
			UpdateMadeRows();

			rowMadeTick = 0;
			madeRows.clear();
			gameState = IDLE;
		}
		return;
	}

	HandlePlayerInput(deltaTime);

	// Default MoveDown
	if (baseTick >= BASE_TICK_LIMIT)
	{
		isMovable = currentMino.MoveDown(board);
		baseTick = 0;
	}

	if (!isMovable) // Mino reached the end
	{
		// Fix mino in the board
		for (const Coord& relativeCoord : currentMino.GetCurrentCoords())
		{
			Coord coord = { currentMino.GetMainPos().x + relativeCoord.x, currentMino.GetMainPos().y + relativeCoord.y };
			Point pos = ArrayPosToWorldPos(coord.x, coord.y);
			board[coord.y][coord.x] = Rect(pos, Point(RECT_SIZE, RECT_SIZE), currentMino.GetType(), brushMap[currentMino.GetType()]);
		}

		// Generate random mino to current mino
		currentMino = GenerateMino();
		isMovable = true;
	}

	baseTick += deltaTime;
}

void TetrisScene::Render(HDC hdc)
{
	// Rendering board
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
			board[i][j].Render(hdc);
	}

	// Rendering currentMino
	for (const Coord& relativeCoord : currentMino.GetCurrentCoords())
	{
		Coord coord = { currentMino.GetMainPos().x + relativeCoord.x, currentMino.GetMainPos().y + relativeCoord.y };
		Point pos = ArrayPosToWorldPos(coord.x, coord.y);
		Rect r = Rect(pos, Point(RECT_SIZE, RECT_SIZE), currentMino.GetType(), brushMap[currentMino.GetType()]);

		r.Render(hdc);
	}
}

Point TetrisScene::ArrayPosToWorldPos(int x, int y)
{
	return Point((x + 0.5f) * RECT_SIZE, (y - 3.5f) * RECT_SIZE);
}

void TetrisScene::HandlePlayerInput(float deltaTime)
{
	if (GetAsyncKeyState(VK_DOWN))
	{
		if (playerTick >= PLAYER_TICK_LIMIT)
		{
			isMovable = currentMino.MoveDown(board);
			playerTick = 0;
		}
		playerTick += deltaTime;
		baseTick = 0;
	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		if (!leftKeyPressed)
			currentMino.MoveLeft(board);
		leftKeyPressed = true;

	}
	else
		leftKeyPressed = false;

	if (GetAsyncKeyState(VK_RIGHT))
	{
		if (!rightKeyPressed)
			currentMino.MoveRight(board);
		rightKeyPressed = true;
	}
	else
		rightKeyPressed = false;

	if (GetAsyncKeyState(VK_UP))
	{
		if (!upKeyPressed)
			currentMino.RotateMino(board);
		upKeyPressed = true;
	}
	else
		upKeyPressed = false;
}

void TetrisScene::CheckBoardMade()
{
	madeRows.clear();

	for (int y = 4; y < BOARD_HEIGHT - 1; y++)
	{
		bool flag = true;

		for (int x = 1; x < BOARD_WIDTH - 1; x++) // 벽을 제외하고 검사
		{
			if (board[y][x].GetType() == NONE)
			{
				flag = false;
				break;
			}
		}

		if (flag)
		{
			madeRows.push_back(y);
			gameState = ROW_MADE;
		}
	}
}

void TetrisScene::ChangeRowColor(bool isOwnColor)
{
	if (isOwnColor)
	{
		for (auto& row : madeRows)
		{
			for (int i = 1; i < BOARD_WIDTH - 1; i++)
			{
				BlockType t = board[row][i].GetType();
				board[row][i].SetBrush(brushMap[t]);
			}
		}
	}
	else
	{
		for (auto& row : madeRows)
		{
			for (int i = 1; i < BOARD_WIDTH - 1; i++)
				board[row][i].SetBrush(flickerBrush);
		}
	}
}

void TetrisScene::UpdateMadeRows()
{
	// Set madeRows as none
	for (auto& y : madeRows)
	{
		for (int x = 1; x < BOARD_WIDTH - 1; x++)
		{
			Point pos = ArrayPosToWorldPos(x, y);
			board[y][x] = Rect(pos, Point(RECT_SIZE, RECT_SIZE), NONE, brushMap[NONE]);
		}
	}

	// madeRows -> 4 6 7 10 이런 순
	
	for (int x = 1; x < BOARD_WIDTH - 1; x++)
	{
		


	}

}

Mino TetrisScene::GenerateMino()
{
	BlockType t = (BlockType)(rand() % 7);

	return Mino(t, Coord(5, 2));
}
