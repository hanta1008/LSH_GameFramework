#pragma once

#include <Windows.h>

#include "iOpenGL.h"


extern HINSTANCE g_hInstance;
extern HWND g_hWnd;
extern HDC g_hDC;

class iWindow
{
public:
	HWND m_hWnd;
	HDC m_hDC;
	HGLRC m_hRC;
private:
	void dipose();
public:
	iWindow(int x, int y, int width, int height, int bits, const char* name, bool fullscreen);
	virtual ~iWindow();
};


wchar_t* utf8_to_utf16(const char* str);
char* utf16_to_utf8(const wchar_t* str);
void showMessageBox(const char* title, const char* msg);