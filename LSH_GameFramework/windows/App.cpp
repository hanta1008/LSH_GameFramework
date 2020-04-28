#include "App.h"

#include "iStd.h"

WCHAR szWindowClass[20] = TEXT("LSH_Game");
int win_border_width = 0, win_border_height = 0;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int APIENTRY wWinMain(_In_ HINSTANCE hInstance_,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	g_hInstance = hInstance_; 

	//윈도우 클래스 설정
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEXW);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = g_hInstance;
	wcex.hIcon = LoadIcon(g_hInstance, MAKEINTRESOURCE(IDI_LSHGAMEFRAMEWORK));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	if (!RegisterClassExW(&wcex))
	{
		showMessageBox("Error", "Create wcex is failed");
		return 0;
	}

	if (loadApp() == false)
	{
		showMessageBox("Error", "loadApp failed");
		return 0;
	}

	runWnd = true;
	MSG msg;
	while (runWnd)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//if (drawLib(hDC, drawGame))
			//{
			//	drawCursor();
			//	SwapBuffers(hDC);
			//}
		}
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		break;
	case WM_DESTROY:
		break;
	case WM_CLOSE:
		break;
	case WM_SIZING:
		resizeWindow(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_SIZE:
		resizeWindow(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_LBUTTONDOWN:
		break;
	case WM_MOUSEMOVE:
		break;
	case WM_LBUTTONUP:
		break;
	case WM_SETCURSOR:
		break;
	case WM_KEYDOWN:
		break;
	case WM_KEYUP:
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

bool loadApp()
{
	monitorSettings();

	//loadLib();

	int wndPosX = monitorSize.width / 2 - wndSize.width / 2;	//좌상단의 X위치
	int wndPosY = monitorSize.height / 2 - wndSize.height/ 2;	//좌상단의 Y위치

	char* className = utf16_to_utf8(szWindowClass);
	iWindow* wnd = new iWindow(wndPosX, wndPosY, wndSize.width, wndSize.height, 32, className, false);
	free(className);

	ShowWindow(wnd->m_hWnd, SW_SHOW);// nCmdShow==SW_SHOWDEFAULT
	SetForegroundWindow(wnd->m_hWnd);	//윈도우 포커스 및 최상위로 올리기
	SetFocus(wnd->m_hWnd);

	return true;
}

// ------------------
// Window Reshape
// ------------------
void resizeWindow(float width, float height)
{
	if (width == 0 || height == 0)
		return;

	float rate = devSize.width / devSize.height;

	if (rate < width / height)		// 윈도우 창 가로 비율이 클때
	{// 왼쪽, 오른쪽 여백 남는때
		viewport.origin.y = 0; viewport.size.height = height;
		// monWidth : monHeight = viewport.width : viewport.height
		viewport.size.width = viewport.size.height * rate;
		viewport.origin.x = (width - viewport.size.width) / 2;
	}
	else if (rate > width / height)	// 윈도우 창 가로 비율이 작을때
	{// 위, 아래쪽 여백 남을때
		viewport.origin.x = 0; viewport.size.width = width;
		// monWidth : monHeight = viewport.width : viewport.height
		viewport.size.height = viewport.size.width / rate;
		viewport.origin.y = (height - viewport.size.height) / 2;
	}
	else// 종횡비 같은 경우
	{
		viewport.origin.x = viewport.origin.y = 0;
		viewport.size.width = width;
		viewport.size.height = height;
	}

	wndSize.width = width + win_border_width;
	wndSize.height = height + win_border_height;
}
void monitorSettings()
{
	monitorSize.width = GetSystemMetrics(SM_CXSCREEN);
	monitorSize.height = GetSystemMetrics(SM_CYSCREEN);

	devSize.width = DEV_WIDTH;
	devSize.height = DEV_HEIGHT;

	// 유동적 대응(개발 사이즈 : 가로 고정)
	float max = DEV_ASPECT_MAX;
	float min = DEV_ASPECT_MIN;
	float rate = monitorSize.width / monitorSize.height;
	if (rate < min)
		rate = min;
	else if (rate > max)
		rate = max;
	// devSize.width : devSize.height = monitorSize.width : monitorSize.height
	devSize.height = devSize.width / rate;

	float width = monitorSize.width * 2 / 3;
	//float height = width * (monitorSize.height / monitorSize.width);
	float height = width / rate;
	resizeWindow(width, height);
}

// ------------------
// Window Kill
// ------------------
bool runWnd;
void exitProgram()
{
	runWnd = false;
}

