#pragma once

#include "iType.h"

// 게임마다 개발자가 설정하는 사이즈
#define DEV_WIDTH 1280	
#define DEV_HEIGHT 720

#define DEV_ASPECT_MAX 2 / 1.0f// (세로를 기준으로) 가장 작은 사이즈
#define DEV_ASPECT_MIN 4 / 3.0f// (새로를 기준으로) 가장 큰 사이즈

extern iSize monitorSize;		//모니터 사이즈
extern iSize devSize;			//개발용 해상도
extern iRect viewport;			//윈도우 창에서 사용되는 영역
extern iSize wndSize;		// 윈도우 창 사이즈
