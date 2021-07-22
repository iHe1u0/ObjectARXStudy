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

double CCalculation::radiusToAngel(double radius)
{
	return radius * PI / 180.0;
}
