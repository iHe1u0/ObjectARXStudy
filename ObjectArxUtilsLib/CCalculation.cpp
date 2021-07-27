#include "pch.h"
#include "CCalculation.h"
#include <math.h>

AcGePoint3d CCalculation::Pt2dTo3d(AcGePoint2d pt)
{
	AcGePoint3d ptTemp(pt.x, pt.y, 0);
	return ptTemp;
}

AcGePoint2d CCalculation::Pt3dTo2d(AcGePoint3d pt)
{
	AcGePoint2d ptTemp(pt.x, pt.y);
	return ptTemp;
}

// 弧度转成角度
double CCalculation::RtoG(double angle)
{
	return angle * 180.0 / PI;
}
// 角度转成弧度
double CCalculation::GtoR(double angle)
{
	return angle * PI / 180.0;
}
