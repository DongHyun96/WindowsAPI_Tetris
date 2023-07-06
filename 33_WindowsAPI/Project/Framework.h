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

using namespace std;

#define WIN_WIDTH	1280.f
#define WIN_HEIGHT	720.f

#include "Util.h"

#include "Point.h"

#include "Shape.h"
#include "Circle.h"
#include "Rect.h"

#include "Scene.h"
#include "PaintScene.h"
#include "CollisionScene.h"
#include "AvoidingGameScene.h"
#include "TetrisScene.h"

#include "MainGame.h"

// extern - 전역변수를 뿌려주는 키워드
extern HWND hWnd; // 어딘가 이게 있으니 여기에 전방선언 한다
extern Point mousePos;