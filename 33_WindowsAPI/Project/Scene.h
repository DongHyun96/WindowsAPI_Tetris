#pragma once

// Interface
class Scene
{
public:
	virtual ~Scene() = default; // �Ҹ��ڸ� ���������Լ��� ���� ���� default�� ����

	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;

};
