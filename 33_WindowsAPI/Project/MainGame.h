#pragma once

class MainGame
{


public:
	MainGame();		// WM_CREATE
	~MainGame();	// WM_DESTROY

	void Update();			// ������ �����ϴ� �Լ�: WM_TIMER
	void Render(HDC hdc);	// ȭ���� �����ϴ� �Լ�: WM_PAINT

private:

	Scene* scene = nullptr;

};
