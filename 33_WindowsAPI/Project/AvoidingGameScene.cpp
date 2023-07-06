#include "Framework.h"
#include "AvoidingGameScene.h"


AvoidingGameScene::AvoidingGameScene()
{
}

AvoidingGameScene::~AvoidingGameScene()
{
	for (Shape* obstacle : obstacles)
		delete obstacle;

	obstacles.clear();
}

void AvoidingGameScene::Update()
{
	// 스폰 시키기
	// spawn_tick = 200
	if (tickCnt * 10 > SPAWN_TICK)
	{
		SpawnObstacle();
		tickCnt = 0;
	}
	
	for (Shape* obstacle : obstacles)
		obstacle->UpdatePos();

	// 화면 밖으로 넘어간 오브젝트 삭제, 다중 삭제
	obstacles.erase(remove_if(obstacles.begin(), obstacles.end(), [this](Shape* shape) {

		return shape->DeleteIfOutOfRange();

	}), obstacles.end());
	
	tickCnt++;
}

void AvoidingGameScene::Render(HDC hdc)
{
	for (Shape* obstacle : obstacles)
		obstacle->Render(hdc);
}

// 크기, 색깔, 시작위치, 떨어지는 속도가 랜덤
void AvoidingGameScene::SpawnObstacle()
{
	UINT r = rand() % 256;
	UINT g = rand() % 256;
	UINT b = rand() % 256;

	HPEN	pen		= CreatePen(PS_SOLID, 1, RGB(r, g, b));
	HBRUSH	brush	= CreateSolidBrush(RGB(r, g, b));

	Point startPos(GetRandom(5.f, WIN_WIDTH - 5.f), 0);

	float speed = GetRandom(SPEED_MIN, SPEED_MAX);

	if (rand() % 2 == 0) // Spawn rect
	{
		Point size(GetRandom(SIZE_MIN, SIZE_MAX), GetRandom(SIZE_MIN, SIZE_MAX));

		obstacles.push_back(new Rect(startPos, size, pen, brush, speed));
	}
	else // Spawn circle
	{
		float radius = GetRandom(SIZE_MIN, SIZE_MAX);

		obstacles.push_back(new Circle(startPos, radius, pen, brush, speed));
	}
}

