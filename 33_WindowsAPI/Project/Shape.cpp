#include "Framework.h"
#include "Shape.h"


Shape::Shape()
{
}

Shape::Shape(Point pos)
	:pos(pos)
{
}

Shape::Shape(Point pos, HBRUSH brush)
	:pos(pos), brush(brush)
{
}

Shape::Shape(Point pos, HPEN pen, HBRUSH brush, float fallingSpeed)
	:pos(pos), pen(pen), brush(brush), fallingSpeed(fallingSpeed)
{
}

Shape::~Shape()
{
	// HPEN HBRUSH -> วฺต้ -> id
	/*if (pen)
		DeleteObject(pen);

	if (brush)
		DeleteObject(brush);*/
}

void Shape::UpdatePos()
{
	pos.y += fallingSpeed;
}

bool Shape::DeleteIfOutOfRange()
{
	if (Top() > WIN_HEIGHT)
	{
		delete this;
		return true;
	}

	return false;
}

void Shape::Render(HDC hdc)
{
	SelectObject(hdc, pen);
	SelectObject(hdc, brush);
}
