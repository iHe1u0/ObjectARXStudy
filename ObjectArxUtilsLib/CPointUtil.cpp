#include "pch.h"
#include "CPointUtil.h"

double CPointUtil::getDistanceOfTwoPoints(AcGePoint3d point1, AcGePoint3d point2)
{
	double pt1X = point1.x, pt1Y = point1.y, pt1Z = point1.z,
		pt2X = point2.x, pt2Y = point2.y, pt2Z = point2.z;

	return sqrt((pt1X - pt2X) * (pt1X - pt2X) +
		(pt1Y - pt2Y) * (pt1Y - pt2Y) +
		(pt1Z - pt2Z) * (pt1Z - pt2Z));
}