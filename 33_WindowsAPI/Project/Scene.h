#pragma once

// Interface
class Scene
{
public:
	virtual ~Scene() = default; // 소멸자를 순수가상함수로 만들 때는 default로 해줌

	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;

};
