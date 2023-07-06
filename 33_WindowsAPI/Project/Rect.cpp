#include "Framework.h"
#include "Rect.h"


Rect::Rect()
{
}

Rect::Rect(Point pos, Point size)
	:Shape(pos), size(size)
{
}

Rect::Rect(Point pos, Point size, BlockType type, HBRUSH brush)
	: Shape(pos, brush), size(size), type(type)
{
}

Rect::Rect(float left, float top, float right, float bottom)
{
	pos.x = (left + right) * 0.5f;
	pos.y = (bottom + top) * 0.5f;

	size.x = right - left;
	size.y = bottom - top;
}

Rect::Rect(const Point& pos, const Point& size, HPEN pen, HBRUSH brush, const float& fallingSpeed)
	:Shape(pos, pen, brush, fallingSpeed), size(size)
{
}

Rect::~Rect()
{
}

void Rect::Render(HDC hdc)
{
	Shape::Render(hdc);

	Rectangle(hdc, Left(), Top(), Right(), Bottom());
}
