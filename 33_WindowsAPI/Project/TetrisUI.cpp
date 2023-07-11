#include "Framework.h"
#include "TetrisUI.h"


TetrisUI::TetrisUI()
{
	scoreBoard		= Rect(Point(500, 100), Point(150, 100));
	nextMinoBoard	= Rect(Point(500, 320), Point(200, 200));

	hFont = CreateFont(
		30,				  // Desired font size
		0,                // Font width
		0,                // Font escapement
		0,                // Orientation
		FW_NORMAL,        // Font weight
		FALSE,            // Italic
		FALSE,            // Underline
		FALSE,            // Strikeout
		DEFAULT_CHARSET,  // Character set
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		TEXT("Impact")     // Font name
	);
}

TetrisUI::~TetrisUI()
{

}

void TetrisUI::Render(HDC hdc)
{
	if (isGameOver)
	{
		SetFont(hdc);

		wsprintf(lpOut, TEXT("GAME OVER!"));
		TextOut(hdc, nextMinoBoard.Pos().x, nextMinoBoard.Pos().y, lpOut, lstrlen(lpOut));

		wsprintf(lpOut, TEXT("==FINAL SCORE=="));
		TextOut(hdc, nextMinoBoard.Pos().x, nextMinoBoard.Pos().y + 40, lpOut, lstrlen(lpOut));

		SetTextColor(hdc, RGB(255, 0, 0));
		TextOut(hdc, nextMinoBoard.Pos().x, nextMinoBoard.Pos().y + 80, to_wstring(score).c_str(), to_wstring(score).size());


		return;
	}

	scoreBoard.Render(hdc);
	nextMinoBoard.Render(hdc);

	SetFont(hdc);

	wsprintf(lpOut, TEXT("== SCORE =="));
	TextOut(hdc, scoreBoard.Pos().x, scoreBoard.Pos().y - 63, lpOut, lstrlen(lpOut));

	SetTextColor(hdc, RGB(255, 0, 0));
	TextOut(hdc, scoreBoard.Pos().x, scoreBoard.Pos().y - 15, to_wstring(score).c_str(), to_wstring(score).size());

	SetTextColor(hdc, RGB(0, 0, 0));

	wsprintf(lpOut, TEXT("== NEXT =="));
	TextOut(hdc, nextMinoBoard.Pos().x, nextMinoBoard.Pos().y - 113, lpOut, lstrlen(lpOut));

	// Render next mino
	if (minoBrush)
	{
		for (const Coord& relativeCoord : nextMino.GetCurrentCoords())
		{
			Coord coord = { 16 + relativeCoord.x, 14 + relativeCoord.y};

			Point pos = TetrisScene::ArrayPosToWorldPos(coord.x, coord.y);

			Rect r = Rect(pos, Point(RECT_SIZE, RECT_SIZE), nextMino.GetType(), minoBrush);

			r.Render(hdc);
		}
	}
}

void TetrisUI::UpdateUIState(int score, Mino nextMino, HBRUSH minoBrush, bool isGameOver)
{
	this->score = score;
	this->nextMino = nextMino;
	this->minoBrush = minoBrush;
	this->isGameOver = isGameOver;
}

void TetrisUI::SetFont(HDC hdc)
{
	SelectObject(hdc, hFont);
	SetTextAlign(hdc, TA_CENTER);
}
