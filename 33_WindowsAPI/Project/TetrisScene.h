#pragma once

#define RECT_SIZE 30.f

#define BOARD_HEIGHT 24
#define BOARD_WIDTH 12

enum InputKey
{
	UP,
	LEFT,
	RIGHT,
	DOWN,
	IDLE
};

class TetrisScene : public Scene
{
public:
	TetrisScene();
	~TetrisScene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;

	virtual void Render(HDC hdc) override;

private:
	
	map<BlockType, HBRUSH> brushMap =
	{
		{I_MINO,	CreateSolidBrush(RGB(255, 0, 0))},
		{Z_MINO,	CreateSolidBrush(RGB(0, 255, 0))},
		{N_MINO,	CreateSolidBrush(RGB(0, 0, 255))},
		{O_MINO,	CreateSolidBrush(RGB(255, 255, 0))},
		{J_MINO,	CreateSolidBrush(RGB(0, 255, 255))},
		{L_MINO,	CreateSolidBrush(RGB(255, 0, 255))},
		{T_MINO,	CreateSolidBrush(RGB(50, 255, 0))},
		{WALL,		CreateSolidBrush(RGB(125, 125, 125))},
		{NONE,		CreateSolidBrush(RGB(255, 255, 255))},
	};


	Rect board[BOARD_HEIGHT][BOARD_WIDTH] = {};


	/// <param name="arrayPos"> Point( [y], [x] )</param>
	/// <returns> worldPos(x, y) </returns>
	Point ArrayPosToWorldPos(int x, int y);
	InputKey GetPlayerInput();
};
