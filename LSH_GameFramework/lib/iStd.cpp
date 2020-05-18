#include "iStd.h"

iSize monitorSize;
iSize devSize;
iRect viewport;
iSize wndSize;

ULONG_PTR gpToken;
DWORD prevTickCount;

void loadLib()
{
	initGdiplus();

	prevTickCount = GetTickCount();
}
void freeLib()
{
	GdiplusShutdown(gpToken);
}
bool drawLib(HDC hDC, DRAW_METHOD method)
{
	DWORD c = GetTickCount();
	float dt = (c - prevTickCount) / 1000.0f;
	if (dt > 0.0f)
	{
		prevTickCount = c;

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		method(dt);// drawGame
		glFlush();

		return true;
	}
	return false;
}
void keyLib()
{

}

void initGdiplus()
{
	GdiplusStartupInput gpInput;
	GdiplusStartup(&gpToken, &gpInput, NULL);
}