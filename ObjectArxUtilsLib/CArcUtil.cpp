#include "pch.h"
#include "CArcUtil.h"
#include "CCalculation.h"
#include "CDwgDatebaseUtil.h"


AcDbObjectId CArcUtil::add(AcGePoint3d ptCenter, AcGeVector3d vec, double radius, double startAngle, double endAngle)
{
    AcDbArc* pArc = new AcDbArc(ptCenter, vec, radius, startAngle, endAngle);
    //(圆心，平面，半径，起点角度，终点角度)
    /*StartAngle和EndAngle并不是起终点的角度，StartAngle可以认为是个参考角，
    默认是0，如果将圆弧绕圆心旋转10度，那这个StartAngle就是10度，EndAngle始终不变，是圆弧的圆心角。*/
    AcDbObjectId arcId;
    arcId = CDwgDatebaseUtil::PostToModelSpace(pArc);
    return arcId;
}

AcDbObjectId CArcUtil::add(AcGePoint2d ptCenter, double radius, double startAngle, double endAngle)
{
    AcGeVector3d vec(0, 0, 1);
    return CArcUtil::add(CCalculation::Pt2dTo3d(ptCenter), vec, radius, startAngle, endAngle);
}

AcDbObjectId CArcUtil::add(AcGePoint2d ptStart, AcGePoint2d ptOnArc, AcGePoint2d ptEnd)
{
    //使用几何类获得圆心，半径
    AcGeCircArc2d geArc(ptStart, ptOnArc, ptEnd);
    AcGePoint2d ptCenter = geArc.center();
    double radius = geArc.radius();

    //计算起始和终止角度
    AcGeVector2d vecStart(ptStart.x - ptCenter.x, ptStart.y - ptCenter.y);
    AcGeVector2d vecEnd(ptEnd.x - ptCenter.x, ptEnd.y - ptCenter.y);
    double startAngle = vecStart.angle();
    double endAngle = vecEnd.angle();
    /*AcGeVector2d 类用来表示一个二维空间中的矢量，
    其成员函数 angle 返回该矢量和 X 轴正半轴的角度（用弧度来表示）。*/
    return CArcUtil::add(ptCenter, radius, startAngle, endAngle);
}

//这个函数的名称不再是 CreateArc，而是 CreateArcSCE，这是因为该函数的参数列表、返回值都与三点法的函数相同，无法实现函数的重载，就只能重新定义一个新的函数名称。
AcDbObjectId CArcUtil::addArc(AcGePoint2d ptStart, AcGePoint2d ptCenter, AcGePoint2d ptEnd)
{
    //计算半径
    double radius = ptCenter.distanceTo(ptStart);
    //计算起，终点角度
    AcGeVector2d vecStart(ptStart.x - ptCenter.x, ptStart.y - ptCenter.y);
    AcGeVector2d vecEnd(ptEnd.x - ptCenter.x, ptEnd.y - ptCenter.y);
    double startAngle = vecStart.angle();
    double endAngle = vecEnd.angle();
    //创建圆弧
    return CArcUtil::add(ptCenter, radius, startAngle, endAngle);
}

AcDbObjectId CArcUtil::add(AcGePoint2d ptStart, AcGePoint2d ptCenter, double angle)
{
    //计算半径
    double radius = ptCenter.distanceTo(ptStart);
    //计算起点，终点角度
    AcGeVector2d vecStart(ptStart.x - ptCenter.x, ptStart.y - ptCenter.y);
    double startAngle = vecStart.angle();
    double endAngle = startAngle + angle;

    //创建圆弧
    return CArcUtil::add(ptCenter, radius, startAngle, endAngle);
}
