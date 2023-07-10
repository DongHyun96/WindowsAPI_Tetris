#pragma once
class Shape
{
public:
	Shape();
	Shape(Point pos);
	Shape(Point pos, HBRUSH brush);
	Shape(Point pos, HPEN pen, HBRUSH brush, float fallingSpeed);
	virtual ~Shape();

	void UpdatePos();
	bool DeleteIfOutOfRange();

	void SetBrush(HBRUSH brush) { this->brush = brush; }

	virtual void Render(HDC hdc); // 펜과 브러쉬 잡기

	virtual float Left()	const = 0;
	virtual float Right()	const = 0;
	virtual float Top()		const = 0;
	virtual float Bottom()	const = 0;

protected:
	Point	pos = {};
	
	HPEN	pen				= nullptr;
	HBRUSH	brush			= nullptr;

	float	fallingSpeed	= 0.f;
};
