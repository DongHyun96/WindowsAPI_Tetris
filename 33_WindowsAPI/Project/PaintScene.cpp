#include "Framework.h"
#include "PaintScene.h"

PaintScene::PaintScene()
{
    hPen[BLACK] = CreatePen(PS_SOLID, penWidth, RGB(0, 0, 0));
    hPen[RED]   = CreatePen(PS_SOLID, penWidth, RGB(255, 0, 0));
    hPen[GREEN] = CreatePen(PS_SOLID, penWidth, RGB(0, 255, 0));
    hPen[BLUE]  = CreatePen(PS_SOLID, penWidth, RGB(0, 0, 255));

    hBrush[BLACK]   = CreateSolidBrush(RGB(0, 0, 0));
    hBrush[RED]     = CreateSolidBrush(RGB(255, 0, 0));
    hBrush[GREEN]   = CreateSolidBrush(RGB(0, 255, 0));
    hBrush[BLUE]    = CreateSolidBrush(RGB(0, 0, 255));
}

PaintScene::~PaintScene()
{
    for (UINT i = 0; i < 4; i++)
    {
        DeleteObject(hPen[i]);
        DeleteObject(hBrush[i]);
    }
}


void PaintScene::Update()
{
    InputKey();


}

void PaintScene::Render(HDC hdc)
{

    curPen = hPen[color];

    DrawObjects(hdc);

    if (GetAsyncKeyState(VK_LBUTTON))
    {
        if (isClick)
        {
            // PRESS
            if (type == Type::PEN)
                DrawPen(hdc);
            else
                Preview(hdc);

        }
        else
        {
            // DOWN
            LButtonDown();
        }
    }
    else
    {
        if (isClick)
        {
            // UP
            LButtonUp();
        }
        else
        {
            // NONE
        }
    }
}

void PaintScene::InputKey()
{
    if (GetAsyncKeyState('1'))
        type = Type::PEN;
    if (GetAsyncKeyState('2'))
        type = Type::LINE;
    if (GetAsyncKeyState('3'))
        type = Type::RECT;
    if (GetAsyncKeyState('4'))
        type = Type::ELLIPSE;

    if (GetAsyncKeyState(VK_F1))
        color = BLACK;
    if (GetAsyncKeyState(VK_F2))
        color = RED;
    if (GetAsyncKeyState(VK_F3))
        color = GREEN;
    if (GetAsyncKeyState(VK_F4))
        color = BLUE;
}

void PaintScene::LButtonDown()
{
    startPos = mousePos;
    isClick = true;
}

void PaintScene::LButtonUp()
{
    isClick = false;

    endPos = mousePos;

    Data data;

    data.startPos = this->startPos;
    data.endPos = this->endPos;
    data.color = this->color;
    data.type = this->type;

    objects.push_back(data);
}

void PaintScene::DrawPen(HDC hdc)
{
    //HDC hdc = GetDC(hWnd);

    Data data;

    data.startPos = startPos;
    data.endPos = mousePos;
    data.color = color;
    data.type = type;

    objects.push_back(data);

    startPos = mousePos;
}

void PaintScene::Preview(HDC hdc)
{
    SelectObject(hdc, hPen[color]);

    switch (type)
    {
    case Type::LINE:
        MoveToEx(hdc, startPos.x, startPos.y, nullptr);
        LineTo(hdc, mousePos.x, mousePos.y);

        break;
    case Type::RECT:
        Rectangle(hdc, startPos.x, startPos.y, mousePos.x, mousePos.y);
        break;
    case Type::ELLIPSE:
        Ellipse(hdc, startPos.x, startPos.y, mousePos.x, mousePos.y);
        break;
    default:
        break;
    }
}

void PaintScene::DrawObjects(HDC hdc)
{
    //HDC hdc = GetDC(hWnd); // WM_PAINT에서 생성된 hdc를 가져와 사용하는 느낌 (두 hdc는 약간 다름)


    for (const Data& data : objects)
    {
        SelectObject(hdc, hPen[data.color]);
        SelectObject(hdc, hBrush[data.color]);

        switch (data.type)
        {
        case Type::PEN:
        case Type::LINE:
            MoveToEx(hdc, data.startPos.x, data.startPos.y, nullptr);
            LineTo(hdc, data.endPos.x, data.endPos.y);

            break;
        case Type::RECT:
            Rectangle(hdc, data.startPos.x, data.startPos.y, data.endPos.x, data.endPos.y);
            break;
        case Type::ELLIPSE:
            Ellipse(hdc, data.startPos.x, data.startPos.y, data.endPos.x, data.endPos.y);
            break;
        default:
            break;
        }
    }
}
