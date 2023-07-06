#pragma once
class Circle : public Shape
{
public:
	Circle();
	Circle(Point pos, float radius);
	Circle(const Point& pos, const float& radius, HPEN pen, HBRUSH brush, const float& fallingSpeed);
	~Circle();

	void Render(HDC hdc) override;

	float Left()	const override { return pos.x - radius; }
	float Right()	const override { return pos.x + radius; }
	float Top()		const override { return pos.y - radius; }
	float Bottom()	const override { return pos.y + radius; }

	Point& Pos()		{ return pos; }
	float& Radius()		{ return radius; }
	
private:
	float radius = 0.f;

};
