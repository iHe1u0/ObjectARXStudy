#pragma once
class CCircleUtil
{
public:
	CCircleUtil();
	~CCircleUtil();

	//圆心、圆所在平面和半径作圆
	static AcDbObjectId add(const AcGePoint3d& Point, const AcGeVector3d& Normal, double radius);

	//圆心、XOY平面和半径作圆
	static AcDbObjectId add(AcGePoint3d& Point, double radius);

	//两点在XOY平面上作圆
	static AcDbObjectId add(AcGePoint2d& FirstPoint, AcGePoint2d& SecondPoint);

	//三点在XOY平面作圆
	static AcDbObjectId add(AcGePoint2d& FirstPoint, AcGePoint2d& SecondPoint, AcGePoint2d& ThirdPoint);

	//获取圆上一点的坐标，传入的是角度，若是弧度，则isDegree为false
	static AcGePoint2d getPoint(AcGePoint2d pointCenter, ads_real radius, ads_real angel, bool isDegree = true);
};

