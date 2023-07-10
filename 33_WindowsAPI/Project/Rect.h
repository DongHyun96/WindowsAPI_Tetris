#pragma once


class Rect : public Shape
{
public:
	Rect();
	Rect(Point pos, Point size);

	Rect(Point pos, Point size, BlockType type, HBRUSH brush);

	Rect(float left, float top, float right, float bottom);

	Rect(const Point& pos, const Point& size, HPEN pen, HBRUSH brush, const float& fallingSpeed=0);

	~Rect();

	void Render(HDC hdc) override;

	float Left()	const override	{ return pos.x - size.x * 0.5f; }
	float Right()	const override	{ return pos.x + size.x * 0.5f; }
	float Top()		const override	{ return pos.y - size.y * 0.5f; }
	float Bottom()	const override	{ return pos.y + size.y * 0.5f; }

	void SetType(const BlockType& type) { this->type = type; }
	BlockType GetType() const { return type; }
	
	
private:
	Point size	= {}; // width height

	BlockType type = NONE;
};
