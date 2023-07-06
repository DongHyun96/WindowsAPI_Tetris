#pragma once

class Mino
{
public:
	Mino();
	~Mino();

	void RotateMino();
	
	void MoveLeft();
	void MoveRight();
	void MoveDown();

private:
	Point				mainPos = {}; // Array Coord
	vector<Point[4]>	minos	= {}; // All rotated case minos
};
