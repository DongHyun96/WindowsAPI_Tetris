// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <iostream>

#include <windows.h>
#include <vector>
#include <map>
#include <string>
#include <time.h>
#include <algorithm>

using namespace std;

#define WIN_WIDTH	720.f
#define WIN_HEIGHT	720.f

// Tetris define 값
#define RECT_SIZE			30.f
#define BOARD_HEIGHT		24
#define BOARD_WIDTH			12
#define BASE_TICK_LIMIT		1		// base tick은 1초
#define PLAYER_TICK_LIMIT	0.03f	// player tick은 0.2초
#define ROW_MADE_TICK_LIMIT 1.f


#include "Util.h"

#include "Point.h"
#include "Coord.h"

#include "Shape.h"
#include "Circle.h"
#include "Mino.h"
#include "Rect.h"

#include "TetrisUI.h"

#include "Scene.h"
#include "PaintScene.h"
#include "CollisionScene.h"
#include "AvoidingGameScene.h"
#include "TetrisScene.h"

#include "MainGame.h"

// extern - 전역변수를 뿌려주는 키워드
extern HWND hWnd; // 어딘가 이게 있으니 여기에 전방선언 한다
extern Point mousePos;
extern TCHAR lpOut[1024];
