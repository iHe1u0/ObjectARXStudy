#pragma once


class CArcUtil
{
public:

	//创建圆弧(中心点、半径、起始角度、终止角度） 角度为度
	static AcDbObjectId add(AcGePoint3d ptCenter, double radius, double startRadius, double endRadius,bool isAngel);

	//创建圆弧(起点、圆心、终点)
	static AcDbObjectId add(AcGePoint3d ptStart, AcGePoint3d ptCenter, AcGePoint3d ptEnd);

};

