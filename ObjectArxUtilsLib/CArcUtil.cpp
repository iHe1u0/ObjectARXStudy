#include "pch.h"
#include "CArcUtil.h"
#include "CCalculation.h"
#include "CDwgDatebaseUtil.h"

AcDbObjectId CArcUtil::add(AcGePoint3d ptCenter, double radius, double startAngel, double endAngel, bool isRadian)
{
	if (!isRadian)
	{
		startAngel = CCalculation::radiusToAngel(startAngel);
		endAngel = CCalculation::radiusToAngel(endAngel);
	}
	AcDbArc* pArc = new AcDbArc(ptCenter, radius, startAngel, endAngel);
	if (pArc == NULL)
		return NULL;

	//将实体添加到模型空间是固定的代码，
	AcDbDatabase* pDb = NULL;
	pDb = acdbHostApplicationServices()->workingDatabase();
	if (pDb == NULL)
		return NULL;
	AcDbBlockTable* pBlkTable;
	if (pDb->getBlockTable(pBlkTable, AcDb::kForRead) != Acad::eOk)
		return NULL;
	AcDbBlockTableRecord* pRec;
	if (pBlkTable->getAt(ACDB_MODEL_SPACE, pRec, AcDb::kForWrite) != Acad::eOk)
		return NULL;
	pBlkTable->close();
	AcDbObjectId objId = AcDbObjectId::kNull;
	if (pRec->appendAcDbEntity(objId, pArc) != Acad::eOk)
		return NULL;
	pArc->close();
	pRec->close();
	return AcDbObjectId();
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

	//创建圆弧
	return CArcUtil::add(ptCenter, radius, startAngle, endAngle, false);
}
