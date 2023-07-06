#include "Framework.h"
#include "CollisionScene.h"


CollisionScene::CollisionScene()
{
	circle1 = new Circle(Point(200, 200), 50);

	rect1 = new Rect(Point(400, 200), Point(100, 200));
}

CollisionScene::~CollisionScene()
{
	delete circle1;
	delete rect1;
}

void CollisionScene::Update()
{
	//circle1->Pos().x++;
}

void CollisionScene::Render(HDC hdc)
{
	circle1->Render(hdc);

	rect1->Render(hdc);

	wstring str;

	str = L"MousePos : " + to_wstring((int)mousePos.x) + L", " + to_wstring((int)mousePos.y);

	TextOut(hdc, 0, 0, str.c_str(), str.size());
}
