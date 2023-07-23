// 230608.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "230608.h"
#include "MainGame.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND	g_hWnd;
vector<HFONT>   g_hFonts;
bool    g_bWinActivate;
float   g_fDeltaTime;

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);		// 창 스타일을 제어하는 기능의 함수
BOOL                InitInstance(HINSTANCE, int);				// 인스턴스 핸들을 저장하고 주 창을 만듭니다.
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);		// 윈도우에서 발생한 메세지를 실제적으로 처리하는 기능을 담당
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);			// 생성된 창에 대한 정보를 알려주는 기능의 함수(지워도 그만)

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,		   // 현재 프로그램의 고유 식별 번호(메모리에 할당되는 실체, 즉 객체, 실행되는 프로그램을 프로그램 인스턴스라 말함)
                     _In_opt_ HINSTANCE hPrevInstance, // 전에 실행되었떤 인스턴스의 핸들 값(거의 null)
                     _In_ LPWSTR    lpCmdLine,	
                     _In_ int       nCmdShow)    // 실행한 창의 스타일(모양 / 최소화 모양 등)에 해당하는 인자값 
{
#ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DEFAULTWINDOW, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DEFAULTWINDOW));

    MSG msg;
	msg.message = WM_NULL;

	CMainGame		MainGame;
	MainGame.Initialize();

	// GetTickCount : 운영 체제가 시작된 후로 흐른 시간을 정수 형태로 반환하는 함수
	// 1 / 1000초의 DWORD 정수 값으로 반환(밀리 세컨드)

    ULONGLONG	ulTime = GetTickCount64();	// 30
    srand(unsigned int(time(NULL)));

#ifdef _DEBUG
#if _TEST_CONSOLE
    // 디버그용 콘솔창
    if (::AllocConsole() == TRUE)
    {
        FILE* nfp[3];
        freopen_s(nfp + 0, "CONOUT$", "rb", stdin);
        freopen_s(nfp + 1, "CONOUT$", "wb", stdout);
        freopen_s(nfp + 2, "CONOUT$", "wb", stderr);
        std::ios::sync_with_stdio();
    }
#endif
#endif // _DEBUG
	
    while (true)
    {
		// PeekMessage : 메세지를 읽어오면 TRUE, 읽을 메세지가 없으면 FALSE를 반환

		// PM_REMOVE	  : 메세지를 읽어옴과 동시에 메세지 큐에서 제거
		// PM_NOREMOVE    : 메세지 큐에 메세지가 존재하는지만 파악, 메세지를 읽어오기 위해선 GetMessage를 다시 호출해줘야 함

		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (WM_QUIT == msg.message)
				break;

			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
            ULONGLONG ulCurTime;
            ulCurTime = GetTickCount64();
			if (ulTime + 10ULL < GetTickCount64())
			{
                // 1초를 기준으로 현재 시간에 과거 시간을 뺀 값을 
                g_fDeltaTime = (static_cast<float>(ulCurTime - ulTime)) / 1000.f;

				MainGame.Update();
				MainGame.Late_Update();
				MainGame.Render();

                ulTime = ulCurTime;
			}			
		}        
    }

#ifdef _DEBUG
#if _TEST_CONSOLE
    // 콘솔 사용 해제
    FreeConsole();
#endif
#endif // _DEBUG

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;		// 윈도우 창을 만들때 각종 윈도우 클래스 정보를 저장하기 위한 구조체

    wcex.cbSize = sizeof(WNDCLASSEX);	// 자기 자신의 사이즈를 저장

    wcex.style          = CS_HREDRAW | CS_VREDRAW; // 가로를 다시 그림 | 세로를 다시 그림
    wcex.lpfnWndProc    = WndProc; // 저장해둔 함수가 호출되어 메세지를 처리함
    wcex.cbClsExtra     = 0; // 윈도우가 특수한 목적으로 사용하는 여분의 공간
    wcex.cbWndExtra     = 0; // 일종의 예약 영역이며 사용하지 않을 경우 0
    wcex.hInstance      = hInstance;		// 이 윈도우 클래스를 사용하는 프로그램의 번호
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_DEFAULTWINDOW));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);	// 배경 색
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;	// 실행 파일의 이름을 저장(가급적이면 프로젝트 이름과 일치시켜 변경할 일이 거의 없음)
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL)); // 윈도우 창 상단에 있는 작은 아이콘 모양을 지정

    return RegisterClassExW(&wcex);		// 구조체 멤버들의 설정을 완료한뒤, 함수의 매개 변수로 설정한 구조체를 전달하고 시스템에 등록시키는 매크로
}		

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   RECT	rc{ 0,0,WINCX, WINCY };

   

   // rc = rc + 기본 윈도우창 스타일 + 메뉴바 크기 고려 여부
   AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW,FALSE);

   HWND hWnd = CreateWindowW(szWindowClass, // 앞서 정의한 윈도우 클래스의 전달한 클래스의 이름을 넣어준다,.
							   szTitle,     //윈도우창 상단에 출력할 문자열의 이름
							   WS_OVERLAPPEDWINDOW, // 만들고자 하는 창의 스타일을 지정하는 매개 변수, WS_OVERLAPPEDWINDOW 기본 값으로 창 모양 생성 
							   CW_USEDEFAULT, 0, // 창이 생성되는 X,Y 좌표
							   rc.right - rc.left,
							   rc.bottom - rc.top, // 가로, 세로 사이즈
							   nullptr, // 부모 윈도우가 있다면 부모 윈도우의 핸들을 지정
							   nullptr, // 윈도우에서 사용할 메뉴의 핸들을 지정
							   hInstance,  // 윈도우를 만드는 주체, 프로그램의 핸들을 지정
							   nullptr); // 운영체제가 특수한 목적으로 사용하므로 건드릴 일 없음

   if (!hWnd)
   {
      return FALSE;
   }

   g_hWnd = hWnd;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   GetClientRect(hWnd, &rc);
   POINT lt, rb;

   lt.x = rc.left;
   lt.y = rc.top;
   rb.x = rc.right;
   rb.y = rc.bottom;

   ClientToScreen(hWnd, &lt);
   ClientToScreen(hWnd, &rb);

   rc.left = lt.x;
   rc.top = lt.y;
   rc.right = rb.x;
   rc.bottom = rb.y;

   //ClipCursor(&rc);


   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//


RECT			rc{100, 100, 200, 200};
list<RECT>		BulletList;


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// 윈도우(창)을 구성하는 세 가지 라이브러리
	// 1. KERNEL : 메모리를 관리하고 프로그램을 실행시키는 기능을 담당
	// 2. USER : 유저 인터페이스와 윈도우 창을 관리
	// 3. GDI : 화면 처리와 그래픽을 담당
	
    switch (message)
    {
	
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다.
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

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
			// DC : 출력에 관한 정보를 갖고 있는 데이터 구조체

            HDC hdc = BeginPaint(hWnd, &ps);
		    
            // 여백 까맣게 하는 코드
            RECT rect;
            GetClientRect(hWnd, &rect);

            HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0)); // 검은색 브러시 생성
            FillRect(hdc, &rect, hBrush); // 영역을 검은색으로 채우기

            DeleteObject(hBrush); // 브러시 삭제
			
            EndPaint(hWnd, &ps);
        }
        break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(g_hWnd);
			break;
		}
		break;
    case WM_SIZE:
    {
        int iNewWidth = LOWORD(lParam);
        int iNewHeight = LOWORD(lParam);

        float fAspectRatio = (float)WINCX / (float)WINCY;

        int iTargetWidth, iTargetHeight;
        if ((float)iNewWidth / (float)iNewHeight > fAspectRatio)
        {
            iTargetWidth = static_cast<int>(iNewHeight * fAspectRatio);
            iTargetHeight = iNewHeight;
        }
        else
        {
            iTargetHeight = static_cast<int>(iNewWidth / fAspectRatio);
            iTargetWidth = iNewWidth;
        }

        RECT rect = { 0, 0, iTargetWidth, iTargetHeight };
        AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
        SetWindowPos(g_hWnd, NULL, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_NOMOVE | SWP_NOZORDER);

        // 깜빡거리는거 거슬려
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        RECT rcClient;
        GetClientRect(hWnd, &rcClient);

        HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0)); // 검은색 브러시 생성
        FillRect(hdc, &rcClient, hBrush); // 영역을 검은색으로 채우기

        DeleteObject(hBrush); // 브러시 삭제

        EndPaint(hWnd, &ps);
        break;
    }
    case WM_ACTIVATE:
    {
        int iActivate = LOWORD(wParam);

        if (iActivate == WA_INACTIVE)
            g_bWinActivate = false;
        else
            g_bWinActivate = true;
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
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


// 함수 호출 규약 : 함수의 실행이 종료되면 할당되었던 스택 메모리를 정리해야 하는데 
// 함수를 호출한 호출원(caller)에서 정리할 것인가, 호출 받은 피호출자(callee)에서 정리할 것인가에 대한 약속, 또는 규약

// __cdecl   : c / c++언어의 기본 호출 규약, 호출자가 스택 메모리를 정리, '가변 인자 함수'의 작동 원리로 인해 본인이 스택 메모리를 정리할 수 없다.
// __stdcall : win32 api 기본 호출 규약, 피호출자가 스택 메모리를 정리, '고정 인자 함수'의 작동 원리로 인해 본인이 스택 메모리를 정리할 수 있다.

// __fastcall : 함수 호출을 빠르게 처리하기 위한 규약, 레지스터 메모리에 함수 코드를 저장하여 함수 호출이 빨라지는 근거가 됨
// __thiscall : this 포인터를 매개 변수 형태로 넘겨 받았을 때 사용하는 호출 규약

// __cdecl만 호출원에서 스택 메모리를 정리함

