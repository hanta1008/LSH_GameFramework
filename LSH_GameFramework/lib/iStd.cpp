#include "iStd.h"

iSize monitorSize;
iSize devSize;
iRect viewport;
iSize wndSize;

ULONG_PTR gpToken;

void loadLib()
{
	initGdiplus();
}
void freeLib()
{
	GdiplusShutdown(gpToken);
}
void initGdiplus()
{
	GdiplusStartupInput gpInput;
	GdiplusStartup(&gpToken, &gpInput, NULL);
}