#pragma once

enum class Type // 그릴 도형의 타입
{
    PEN,
    LINE,
    RECT,
    ELLIPSE
};


enum Color
{
    BLACK,
    RED,
    GREEN,
    BLUE
};

struct Data
{
    Point startPos;
    Point endPos;

    Type type;
    Color color;
};

class PaintScene : public Scene
{
public:
	PaintScene();
	~PaintScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

    void InputKey();

    void LButtonDown(); // 마우스가 눌렸을 때의 행동
    void LButtonUp();

    void DrawPen(HDC hdc);
    void Preview(HDC hdc); // 미리보기

    void DrawObjects(HDC hdc);

private:
    HPEN    hPen[4] = {};
    HBRUSH  hBrush[4] = {};

    HPEN    curPen;
    HBRUSH  curBrush;

    Point   startPos;
    Point   endPos;

    bool isClick = false;

    const UINT penWidth = 2;

    Type type;
    Color color;

    vector<Data> objects;
};
