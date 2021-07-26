#pragma once
class CCalculation
{
public:
	// 二维坐标转化为三维坐标
	static AcGePoint3d Pt2dTo3d(AcGePoint2d pt);

	// 三维坐标转为二维
	static AcGePoint2d Pt3dTo2d(AcGePoint3d pt);


	// 弧度转成角度
	static double RtoG(double angle);

	// 角度转成弧度
	static double GtoR(double angle);
};

