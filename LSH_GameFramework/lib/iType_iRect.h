#pragma once

#include "iType_iPoint.h"
#include "iType_iSize.h"

struct iRect
{
	iPoint origin;// 사각형의 좌상단 좌표
	iSize size;//사각형의 가로, 세로 길이
};

iRect iRectMake(float x, float y, float width, float height);
bool containPoint(const iPoint& point, const iRect& rect);	// 사각형에 점이 포함되었는지 확인
bool intersectRect(const iRect& src, const iRect& dst);	//두 사각형이 교차 하는지 확인
bool containRect(const iRect& src, const iRect& dst);

#define iRectZero iRectMake(0,0,0,0)