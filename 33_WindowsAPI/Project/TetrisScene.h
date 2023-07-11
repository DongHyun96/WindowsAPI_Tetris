#pragma once
#pragma comment(lib,"winmm.lib")

#define STACKING_SCORE	20
#define SINGLE_SCORE	100
#define DOUBLE_SCORE	300
#define TRIPLE_SCORE	500
#define TETRIS_SCORE	800

enum GameState
{
	IDLE,
	ROW_MADE,
	GAME_OVER
};

class TetrisScene : public Scene
{
public:
	TetrisScene();
	~TetrisScene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;

	/// <summary> 렌더링 순서 : 보드 / Current Mino </summary>
	virtual void Render(HDC hdc) override;

	/// <param name="arrayPos"> Point( [y], [x] )</param>
	/// <returns> worldPos(x, y) </returns>
	static Point ArrayPosToWorldPos(int x, int y);


private:


	void HandlePlayerInput(float deltaTime);

	void UpdateGameState();
	void ChangeRowColor(bool isOwnColor);
	void UpdateMadeRows();

	Mino GenerateMino();

private:
	
	GameState gameState = IDLE;

	bool paused	= false;

	map<BlockType, HBRUSH> brushMap =
	{
		{I_MINO,	CreateSolidBrush(RGB(0, 255, 255))},
		{Z_MINO,	CreateSolidBrush(RGB(255, 255, 0))},
		{N_MINO,	CreateSolidBrush(RGB(128, 0, 128))},
		{O_MINO,	CreateSolidBrush(RGB(0, 255, 0))},
		{J_MINO,	CreateSolidBrush(RGB(255, 0, 0))},
		{L_MINO,	CreateSolidBrush(RGB(0, 0, 255))},
		{T_MINO,	CreateSolidBrush(RGB(255, 127, 0))},
		{WALL,		CreateSolidBrush(RGB(125, 125, 125))},
		{NONE,		CreateSolidBrush(RGB(255, 255, 255))},
	};
	
	HBRUSH flickerBrush = CreateSolidBrush(RGB(255, 255, 255));
	
	float baseTick		= 0;
	float playerTick	= 0;
	float rowMadeTick	= 0;


	bool leftKeyPressed		= false;
	bool rightKeyPressed	= false;
	bool upKeyPressed		= false;
	
	bool isMovable			= true;
	
	Rect board[BOARD_HEIGHT][BOARD_WIDTH] = {};
	
	vector<int> madeRows = {};

	Mino nextMino;
	Mino currentMino;

	int score			= 0;

	TetrisUI tetrisUI;

	


};
