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
	for (const Coord& coord : currentMino.GetCurrentCoords())
	{
		Point pos = ArrayPosToWorldPos(currentMino.GetMainPos().x + coord.x, currentMino.GetMainPos().y + coord.y);

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

Mino TetrisScene::GenerateMino()
{
	BlockType t = (BlockType)(rand() % 7);

	return Mino(t, Coord(5, 0));
}
