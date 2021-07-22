#pragma once


class CArcUtil
{
public:

	//创建圆弧(中心点、半径、起始角度、终止角度） 角度为度
	static AcDbObjectId add(AcGePoint3d ptCenter, double radius, double startRadius, double endRadius);

};

