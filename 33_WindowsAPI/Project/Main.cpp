// Project.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "Framework.h"
#include "Main.h"

#define MAX_LOADSTRING 100

Point mousePos;

MainGame* mainGame = nullptr;

HWND hWnd;

TCHAR lpOut[1024];

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다. 윈도우창을 다루는 객체
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.  문자열
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다. 문자열



// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다. -> 전역 문자열(위에 있는 세개의 전역변수)
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PROJECT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow)) // 본격적으로 창을 만드는 함수
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROJECT));

    MSG msg;

    // 기본 메시지 루프입니다: // 키보드 마우스 입력 등등을 여기서 처리
    while (GetMessage(&msg, nullptr, 0, 0)) // 메시지 큐
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg); // 메시지 번역
            DispatchMessage(&msg);  // Dispatch - 보내다, 전송하다 -> WndProc 함수로 보냄 (윈도우 프로시저)
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다. (윈도우 창을 만드는 클래스 등록)
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex; // 구조체 (구조체를 초기화해주는 과정)

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROJECT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    //wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PROJECT); // 메뉴 네임
    wcex.lpszMenuName   = nullptr;

    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    // 매개변수가 너무 길어지기 때문에 매개변수를 모두 들고 있는 구조체를 만들어 따로 빼주는 구조
    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   RECT rect = { 0, 0, WIN_WIDTH, WIN_HEIGHT };

   AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

   float width  = rect.right - rect.left;
   float height = rect.bottom - rect.top;

   hWnd = CreateWindowW
   (
       szWindowClass,
       szTitle,
       WS_OVERLAPPEDWINDOW,
           0,      0,
       width, height,
       nullptr, nullptr, hInstance, nullptr
   );

   if (!hWnd) // 만약 hWnd에 nullptr 즉, CreateWindow에서 문제가 생겼다면 종료
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
// 여기서 메시지를 받아서 case에 따라 동작을 처리
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE: // 윈도우가 최초로 실행될 때의 메시지
        
        srand(time(NULL));

        SetTimer(hWnd, 1, 10, nullptr);

        mainGame = new MainGame;

        break;
    case WM_TIMER:
        InvalidateRect(hWnd, nullptr, false);

        mainGame->Update();

        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT: // 매 프레임 그리는 메시지
        {
            /** 더블버퍼링 시작처리입니다. **/
            static HDC hdc, MemDC, tmpDC;
            static HBITMAP BackBit, oldBackBit;
            static RECT bufferRT;
            PAINTSTRUCT ps;
            hdc = BeginPaint(hWnd, &ps);

            GetClientRect(hWnd, &bufferRT);
            MemDC = CreateCompatibleDC(hdc);
            BackBit = CreateCompatibleBitmap(hdc, bufferRT.right, bufferRT.bottom);
            oldBackBit = (HBITMAP)SelectObject(MemDC, BackBit);
            PatBlt(MemDC, 0, 0, bufferRT.right, bufferRT.bottom, WHITENESS);
            tmpDC = hdc;
            hdc = MemDC;
            MemDC = tmpDC;

            //PAINTSTRUCT ps;
            //HDC hdc = BeginPaint(hWnd, &ps); // HDC - Handle device context

            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다... // 그리는 동작은 BeginPaint와 EndPaint 사이에 이뤄짐
            mainGame->Render(hdc);
            
            /** 더블버퍼링 끝처리 입니다. **/
            tmpDC = hdc;
            hdc = MemDC;
            MemDC = tmpDC;
            GetClientRect(hWnd, &bufferRT);
            BitBlt(hdc, 0, 0, bufferRT.right, bufferRT.bottom, MemDC, 0, 0, SRCCOPY);
            SelectObject(MemDC, oldBackBit);
            DeleteObject(BackBit);
            DeleteDC(MemDC);

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_MOUSEMOVE:
        mousePos.x = LOWORD(lParam); // 마우스 위치 저장
        mousePos.y = HIWORD(lParam);
        break;
    case WM_DESTROY:

        delete mainGame;

        PostQuitMessage(0); // Main 함수에서의 while문의 GetMessage에서 0을 반환 -> while문 탈출하여 프로그램 종료
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
