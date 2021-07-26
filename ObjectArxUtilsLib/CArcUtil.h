#pragma once


class CArcUtil
{
public:

	//创建圆弧(中心点、半径、起始角度、终止角度） isRadian判读是否是弧度，默认用的角度
	static AcDbObjectId add(AcGePoint3d ptCenter, double radius, double startAngel, double endAngel, bool isRadian = false);

	//创建圆弧(起点、圆心、终点)
	static AcDbObjectId add(AcGePoint3d ptStart, AcGePoint3d ptCenter, AcGePoint3d ptEnd);

	//创建圆弧(起点、圆心、旋转角度） 
	static AcDbObjectId add(AcGePoint3d ptStart, AcGePoint3d ptCenter, double angle);

};

