#pragma once

class TetrisScene;

class TetrisUI
{
public:
	TetrisUI();
	~TetrisUI();

	void Render(HDC hdc);

	void UpdateUIState(int score, Mino nextMino, HBRUSH minoBrush, bool isGameOver);

private:
	void SetFont(HDC hdc);

private:
	Rect scoreBoard;
	Rect nextMinoBoard;

	Mino	nextMino;
	HBRUSH	minoBrush = nullptr;

	int score = 0;

	bool isGameOver = false;

	HFONT hFont;

private:

};
