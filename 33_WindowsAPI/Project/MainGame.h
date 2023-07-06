#pragma once

class MainGame
{


public:
	MainGame();		// WM_CREATE
	~MainGame();	// WM_DESTROY

	void Update();			// 정보를 갱신하는 함수: WM_TIMER
	void Render(HDC hdc);	// 화면을 갱신하는 함수: WM_PAINT

private:

	Scene* scene = nullptr;

};
