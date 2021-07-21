#pragma once


class CArcUtil
{
public:
	//创建位于XOY平面上的圆弧的函数
	static AcDbObjectId add(AcGePoint2d ptCenter, double radius, double startAngle, double endAngle);

	//三点法创建圆弧
	static AcDbObjectId add(AcGePoint2d ptStart, AcGePoint2d ptOnArc, AcGePoint2d ptEnd);

	//"起点，圆心，终点"创建圆弧
	static AcDbObjectId addArc(AcGePoint2d ptStart, AcGePoint2d ptCenter, AcGePoint2d ptEnd);

	//"起点，圆心，圆弧角度"创建圆弧
	static AcDbObjectId add(AcGePoint2d ptStart, AcGePoint2d ptCenter, double angle);

	//创建圆弧
	static AcDbObjectId add(AcGePoint3d ptCenter, AcGeVector3d vec, double radius, double starAngle, double endAngle);

};

