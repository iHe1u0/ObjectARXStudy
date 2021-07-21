#include "pch.h"
#include "CCalculation.h"
#include <math.h>

AcGePoint3d CCalculation::Pt2dTo3d(AcGePoint2d pt)
{
	AcGePoint3d ptTemp(pt.x, pt.y, 0);
	return ptTemp;
}
