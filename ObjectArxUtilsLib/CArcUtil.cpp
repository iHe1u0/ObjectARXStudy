#include "pch.h"
#include "CArcUtil.h"
#include "CCalculation.h"
#include "CDwgDatebaseUtil.h"

AcDbObjectId CArcUtil::add(AcGePoint3d ptCenter, double radius, double startRadius, double endRadius)
{
	//输入角度(
	AcDbArc* pArc = new AcDbArc(ptCenter, radius, CCalculation::radiusToAngel(startRadius), CCalculation::radiusToAngel(endRadius));
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
	if (pRec->appendAcDbEntity(objId, pArc) != Acad::eOk) //将线添加到dwg中
		return NULL;
	pArc->close();
	pRec->close();
	return AcDbObjectId();
}
