#pragma once


class TetrisScene : public Scene
{
public:
	TetrisScene();
	~TetrisScene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;

	/// <summary> 렌더링 순서 : 보드 / Current Mino </summary>
	virtual void Render(HDC hdc) override;

private:
	
	map<BlockType, HBRUSH> brushMap =
	{
		{I_MINO,	CreateSolidBrush(RGB(150, 40, 180))},
		{Z_MINO,	CreateSolidBrush(RGB(128, 128, 0))},
		{N_MINO,	CreateSolidBrush(RGB(128, 0, 128))},
		{O_MINO,	CreateSolidBrush(RGB(0, 128, 0))},
		{J_MINO,	CreateSolidBrush(RGB(128, 0, 0))},
		{L_MINO,	CreateSolidBrush(RGB(0, 0, 128))},
		{T_MINO,	CreateSolidBrush(RGB(255, 127, 0))},
		{WALL,		CreateSolidBrush(RGB(125, 125, 125))},
		{NONE,		CreateSolidBrush(RGB(255, 255, 255))},
	};
	
	float baseTick	 = 0;
	float playerTick = 0;

	bool leftKeyPressed		= false;
	bool rightKeyPressed	= false;
	bool upKeyPressed		= false;
	
	bool isMovable			= true;
	
	Rect board[BOARD_HEIGHT][BOARD_WIDTH] = {};
	
	Mino currentMino;

	/// <param name="arrayPos"> Point( [y], [x] )</param>
	/// <returns> worldPos(x, y) </returns>
	Point ArrayPosToWorldPos(int x, int y);

	void HandlePlayerInput(float deltaTime);

	Mino GenerateMino();

};
