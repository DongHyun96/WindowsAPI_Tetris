#include "Framework.h"
#include "MainGame.h"

MainGame::MainGame()
{
	//scene = new PaintScene;
	//scene = new CollisionScene;
	//scene = new AvoidingGameScene;
	scene = new TetrisScene;
}

MainGame::~MainGame()
{
	delete scene;
}

void MainGame::Update()
{
	scene->Update();
}

void MainGame::Render(HDC hdc)
{
	scene->Render(hdc);
}
