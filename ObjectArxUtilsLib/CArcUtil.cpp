#include "pch.h"
#include "CArcUtil.h"
#include "CCalculation.h"
#include "CDwgDatebaseUtil.h"

AcDbObjectId CArcUtil::add(AcGePoint3d ptCenter, double radius, double startAngel, double endAngel, bool isGra)
{
	if (!isGra)
	{
		startAngel = CCalculation::GtoR(startAngel);
		endAngel = CCalculation::GtoR(endAngel);
	}
	AcDbArc* pArc = new AcDbArc(ptCenter, radius, startAngel, endAngel);
	return CDwgDatebaseUtil::PostToModelSpace(pArc);
}

AcDbObjectId CArcUtil::add(AcGePoint3d ptStart, AcGePoint3d ptCenter, AcGePoint3d ptEnd)
{

	//计算半径
	double radius = ptCenter.distanceTo(ptStart);
	//计算起，终点角度
	AcGeVector2d vecStart(ptStart.x - ptCenter.x, ptStart.y - ptCenter.y);
	AcGeVector2d vecEnd(ptEnd.x - ptCenter.x, ptEnd.y - ptCenter.y);
	double startAngle = vecStart.angle();
	double endAngle = vecEnd.angle();
	//创建圆弧
	return CArcUtil::add(ptCenter, radius, startAngle, endAngle, TRUE);
}

AcDbObjectId CArcUtil::add(AcGePoint3d ptStart, AcGePoint3d ptCenter, double angle)
{
	//计算半径
	double radius = ptCenter.distanceTo(ptStart);
	//计算起点，终点角度
	AcGeVector2d vecStart(ptStart.x - ptCenter.x, ptStart.y - ptCenter.y);
	double startAngle = vecStart.angle();
	double endAngle = startAngle + angle;

	acutPrintf(L"起始角度：%f，结束角度：%f \n", startAngle, endAngle);
	//创建圆弧
	return CArcUtil::add(ptCenter, radius, startAngle, endAngle, true);
}
