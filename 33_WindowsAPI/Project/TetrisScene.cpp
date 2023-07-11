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
	nextMino	= GenerateMino();
	
	tetrisUI	= TetrisUI();

	PlaySound(TEXT("TetrisMainTheme.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);
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
	
	if (gameState != GAME_OVER && paused)
	{
		HandlePlayerInput(deltaTime);
		return;
	}

	if (gameState == GAME_OVER)
	{
		// Game Over
		return;
	}

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
			
			switch (madeRows.size())
			{
			case 1:
				score += SINGLE_SCORE;
				break;
			case 2:
				score += DOUBLE_SCORE;
				break;
			case 3:
				score += TRIPLE_SCORE;
				break;
			case 4:
				score += TETRIS_SCORE;
				break;
			default:
				break;
			}

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
		// Add stacking score
		score += STACKING_SCORE;

		// Fix mino in the board
		for (const Coord& relativeCoord : currentMino.GetCurrentCoords())
		{
			Coord coord = { currentMino.GetMainPos().x + relativeCoord.x, currentMino.GetMainPos().y + relativeCoord.y };
			Point pos = ArrayPosToWorldPos(coord.x, coord.y);
			board[coord.y][coord.x] = Rect(pos, Point(RECT_SIZE, RECT_SIZE), currentMino.GetType(), brushMap[currentMino.GetType()]);
		}

		// Generate random mino to nextMino and update current mino
		currentMino = nextMino;
		nextMino	= GenerateMino();

		isMovable = true;
	}

	UpdateGameState();

	if (gameState == ROW_MADE)
		tetrisUI.UpdateUIState(score, currentMino, brushMap[currentMino.GetType()], gameState == GAME_OVER);
	else
		tetrisUI.UpdateUIState(score, nextMino, brushMap[nextMino.GetType()], gameState == GAME_OVER);

	baseTick += deltaTime;
}

void TetrisScene::Render(HDC hdc)
{
	// Rendering UI
	tetrisUI.Render(hdc);

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

	if (paused)
	{
		SetTextColor(hdc, RGB(255, 0, 0));
		wsprintf(lpOut, TEXT("PAUSED"));
		TextOut(hdc, 500, 500, lpOut, lstrlen(lpOut));
	}
}

Point TetrisScene::ArrayPosToWorldPos(int x, int y)
{
	return Point((x + 0.5f) * RECT_SIZE, (y - 3.5f) * RECT_SIZE);
}

void TetrisScene::HandlePlayerInput(float deltaTime)
{
	static bool pPressed = false;

	if (GetAsyncKeyState('P'))
	{
		if (!pPressed)
		{
			paused = !paused;

			pPressed = true;
		}

		return; // Do not handle other key input while paused
	}
	else pPressed = false;

	if (paused) // Do not handle other key input while paused
		return;

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

void TetrisScene::UpdateGameState()
{
	// Check GameOver
	for (int i = 1; i < BOARD_WIDTH - 1; i++)
	{
		if (board[3][i].GetType() != NONE)
		{
			gameState = GAME_OVER;
			break;
		}
	}

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

	 //madeRows -> 4 6 7 10 이런 순
	for (int y = BOARD_HEIGHT - 2; y >= 4; y--)
	{
		auto it = find(madeRows.begin(), madeRows.end(), y);

		if (it != madeRows.end()) // 만일 현재 y가 madeRow라면 continue
			continue;

		// 자신의 아래로 만들어진 row의 개수를 파악
		int madeCnt = 0;
		for (auto& row : madeRows)
		{
			if (y < row)
				madeCnt++;
		}
		
		if (madeCnt == 0) // 자신의 아래로 만들어진 row가 없다면 넘어감
			continue;
		
		// 아래의 만들어진 row만큼 아래로 내림
		for (int x = 1; x < BOARD_WIDTH - 1; x++)
		{
			// Type과 Brush를 바꿔줌
			board[y + madeCnt][x].SetType(board[y][x].GetType());
			board[y + madeCnt][x].SetBrush(brushMap[board[y][x].GetType()]);
				
			// 원래의 자리는 none으로 만듦
			Point pos = ArrayPosToWorldPos(x, y);
			board[y][x] = Rect(pos, Point(RECT_SIZE, RECT_SIZE), NONE, brushMap[NONE]);
		}
	}
}

Mino TetrisScene::GenerateMino()
{
	BlockType t = (BlockType)(rand() % 7);

	return Mino(t, Coord(5, 2));
}
