#include "iType_iPoint.h"

#include <math.h>
bool iPoint::operator == (const iPoint& p)
{
	return (x == p.x && y == p.y);
	//return (fabsf(x-p.x)<0.00001f && fabsf(y-p.y)<0.00001f);
}

bool iPoint::operator != (const iPoint& p)
{
	//return !(x==p.x && y==p.y);
	return (x != p.x || y != p.y);
}

iPoint iPoint::operator + (const iPoint& p)
{
	iPoint r;
	r.x = x + p.x;
	r.y = y + p.y;
	return r;
}

iPoint iPoint::operator += (const iPoint& p)
{
	x += p.x;
	y += p.y;
	return (*this);
}

iPoint iPoint::operator - (const iPoint& p)
{
	iPoint r;
	r.x = x - p.x;
	r.y = y - p.y;
	return r;
}
iPoint iPoint::operator -= (const iPoint& p)
{
	x -= p.x;
	y -= p.y;
	return (*this);
}

iPoint iPoint::operator * (const iPoint& p)
{
	iPoint r;
	r.x = x * p.x;
	r.y = y * p.y;
	return r;
}
iPoint iPoint::operator *= (const iPoint& p)
{
	x *= p.x;
	y *= p.y;
	return (*this);
}

iPoint iPoint::operator / (const iPoint& p)
{
	iPoint r;
	r.x = x / p.x;
	r.y = y / p.y;
	return r;
}
iPoint iPoint::operator /= (const iPoint& p)
{
	x /= p.x;
	y /= p.y;
	return (*this);
}

iPoint iPoint::operator * (float f)
{
	iPoint r;
	r.x = x * f;
	r.y = y * f;
	return r;
}
iPoint iPoint::operator *= (float f)
{
	x *= f;
	y *= f;
	return (*this);
}

iPoint iPoint::operator / (float f)
{
	iPoint r;
	r.x = x / f;
	r.y = y / f;
	return r;
}
iPoint iPoint::operator /= (float f)
{
	x /= f;
	y /= f;
	return (*this);
}

iPoint iPointMake(float x, float y)
{
	iPoint p;
	p.x = x;
	p.y = y;
	return p;
}

bool iPointEqual(const iPoint& p0, const iPoint& p1)
{
	return (p0.x == p1.x && p0.y == p1.y);
	//return (fabsf(x-p.x)<0.00001f && fabsf(y-p.y)<0.00001f);
}

iPoint iPointAdd(const iPoint& p0, const iPoint& p1)
{
	iPoint p;
	p.x = p0.x + p1.x;
	p.y = p0.y + p1.y;
	return p;
}
iPoint iPointSub(const iPoint& p0, const iPoint& p1)
{
	iPoint p;
	p.x = p0.x - p1.x;
	p.y = p0.y - p1.y;
	return p;
}

iPoint iPointDot(const iPoint& p)
{
	iPoint r;
	r.x = p.x*p.x;
	r.y = p.y*p.y;
	return r;
}

iPoint iPointMult(const iPoint& p0, const iPoint& p1)
{
	iPoint p;
	p.x = p0.x * p1.x;
	p.y = p0.y * p1.y;
	return p;
}
float iPointLength(const iPoint& p)
{
	return sqrtf(p.x*p.x + p.y*p.y);
}
float iPointDistance(const iPoint& p0, const iPoint& p1)
{
	iPoint p;
	p.x = p0.x - p1.x;
	p.y = p0.y - p1.y;
	return sqrtf(p.x*p.x + p.y*p.y);
}
float iPointDistanceFast(const iPoint& p0, const iPoint& p1)
{
	iPoint p;
	p.x = p0.x - p1.x;
	p.y = p0.y - p1.y;
	return (p.x*p.x + p.y*p.y);
}

iPoint iPointNormalize(const iPoint& p)
{
	float length = sqrtf(p.x*p.x + p.y*p.y);
	iPoint r;
	r.x = p.x / length;
	r.y = p.y / length;
	return r;
}
iPoint iPointVector(const iPoint& p0, const iPoint& p1)
{
	iPoint p;
	p.x = p1.x - p0.x;
	p.y = p1.y - p1.y;
	return p;
}