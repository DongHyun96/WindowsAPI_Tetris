#include "Framework.h"
#include "Circle.h"


Circle::Circle()
{
}

Circle::Circle(Point pos, float radius)
	:Shape(pos), radius(radius)
{
}

Circle::Circle(const Point& pos, const float& radius, HPEN pen, HBRUSH brush, const float& fallingSpeed)
	:Shape(pos, pen, brush, fallingSpeed), radius(radius)
{
}

Circle::~Circle()
{
}

void Circle::Render(HDC hdc)
{
	Shape::Render(hdc);

	Ellipse(hdc, Left(), Top(), Right(), Bottom());
}
