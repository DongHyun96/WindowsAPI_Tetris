#pragma once

#define SPEED_MIN 5.f
#define SPEED_MAX 20.f

#define SIZE_MIN 30.f
#define SIZE_MAX 100.f

#define SPAWN_TICK 200 // 해당 millisec마다 스폰

class AvoidingGameScene : public Scene
{
public:
	AvoidingGameScene();
	~AvoidingGameScene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	vector<Shape*> obstacles;

	UINT tickCnt = 0;

	void SpawnObstacle();

};
