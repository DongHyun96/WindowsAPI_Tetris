#pragma once
class CollisionScene : public Scene
{
public:
	CollisionScene();
	~CollisionScene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	Circle* circle1;
	Rect* rect1;
};
