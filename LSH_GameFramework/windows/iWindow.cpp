#include "iWindow.h"

HINSTANCE g_hInstance;

iWindow::iWindow(int x, int y, int width, int height, int bits, const char* name, bool fullscreen)
{
	DWORD dwExStyle;
	DWORD dwStyle;
	if (fullscreen)
	{
		dwExStyle = WS_EX_APPWINDOW;
		dwStyle = WS_POPUP;
	}
	else// if( fullscreen==false )
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle = WS_OVERLAPPEDWINDOW;
	}
	RECT rect;
	rect.left = x;
	rect.right = x + width;
	rect.top = y;
	rect.bottom = y + height;
	AdjustWindowRectEx(&rect, dwStyle, FALSE, dwExStyle);

	/*윈도우 생성(hwnd)*/
	wchar_t* szWindowClass = utf8_to_utf16(name);
	HWND hwnd = CreateWindowEx(dwExStyle,
		szWindowClass,
		szWindowClass,
		dwStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		x, y,
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,
		g_hInstance,
		NULL);
	if (!hwnd)
	{
		showMessageBox("Error", "CreateWindow Failed");
		return;
	}
	free(szWindowClass);
	HDC hdc = GetDC(hwnd);

	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = bits;
	pfd.cDepthBits = bits;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int pixelFormat = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, pixelFormat, &pfd);

	/* wgl 함수들은 OpenGL과 윈도우즈 API를 연결시키는 역할을 담당한다.*/
	HGLRC hrc = wglCreateContext(hdc);	
	wglMakeCurrent(hdc, hrc);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	//	GLEW
	////////////////////////////////////////////////////////////////////////////////////////////////////
	glewExperimental = TRUE;
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		showMessageBox("Error", "glewInit - fail");
		dipose();
		return;
	}

	int attr[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
		WGL_CONTEXT_MINOR_VERSION_ARB, 2,
		WGL_CONTEXT_FLAGS_ARB, 0,
		0
	};
	if (wglewIsSupported("WGL_ARB_create_context"))
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(hrc);

		hrc = wglCreateContextAttribsARB(hdc, NULL, attr);

		wglMakeCurrent(hdc, hrc);
	}

#if 0// for checking gl version
	const char* strGL = (const char*)glGetString(GL_VERSION);
	const char* strGLEW = (const char*)glewGetString(GLEW_VERSION);
	const char* strGLSL = (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
	char s[256]; sprintf(s, "gl(%s), glew(%s), glsl(%s)", strGL, strGLEW, strGLSL);
	showMessageBox("Version", s);

	// user pc1 - opengl 4.6 / glsl 4.6		=> recently
	// user pc3 - opengl 3.0, 3.1, 3.2 / glsl 1.3, 1.4, 1.5 7~8 years ago
	// user pc2 - opengl 2.0 / glsl 1.1		=> once upon a time
#endif
	////////////////////////////////////////////////////////////////////////////////////////////////////

	m_hWnd = hwnd;
	m_hDC = hdc;
	m_hRC = hrc;
}
iWindow::~iWindow()
{
	dipose();
}

void iWindow::dipose()
{
	if (m_hRC)
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(m_hRC);
		m_hRC = NULL;
	}

	if (m_hWnd && m_hDC)
	{
		ReleaseDC(m_hWnd, m_hDC);
		m_hDC = NULL;
	}

	if (m_hWnd)
	{
		DestroyWindow(m_hWnd);
		m_hWnd = NULL;
	}
}



wchar_t* utf8_to_utf16(const char* str)
{
	int length = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	wchar_t* s = (wchar_t*)malloc(sizeof(wchar_t)*length);
	MultiByteToWideChar(CP_UTF8, 0, str, strlen(str) + 1, s, length);
	return s;
}
char* utf16_to_utf8(const wchar_t* str)
{
	int length = WideCharToMultiByte(CP_UTF8, 0, str, lstrlenW(str), NULL, 0, NULL, NULL);
	char* s = (char*)calloc(sizeof(char), 1 + length);
	WideCharToMultiByte(CP_UTF8, 0, str, lstrlenW(str), s, length, NULL, NULL);

	return s;
}
void showMessageBox(const char* title, const char* msg)
{
	wchar_t* wTitle = utf8_to_utf16(title);
	wchar_t* wMsg = utf8_to_utf16(msg);
	MessageBox(NULL, wMsg, wTitle, MB_OK);
	free(wTitle);
	free(wMsg);
}