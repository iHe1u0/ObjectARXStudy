#include "stdafx.h"
#include "CCreateEntity.h"

//"起点，圆心，圆弧角度"创建圆弧
void CCreateEntity::CreateArc(AcGePoint2d ptStartPoint, AcGePoint2d ptEndPoint, AcGePoint2d ptCenterPoint)
{
	AcGeVector2d vecStart(ptStartPoint.x - ptCenterPoint.x, ptStartPoint.y - ptCenterPoint.y);
	AcGeVector2d vecEnd(ptEndPoint.x - ptCenterPoint.x, ptEndPoint.y - ptCenterPoint.y);
	double StartAng = vecStart.angle();
	double EndAng = vecEnd.angle();

	AcGePoint3d pt(0, 0, 0);
	AcGeVector3d vec(0, 0, 1);
	AcDbArc *Acr = NULL;
	Acr = new AcDbArc(pt, vec, 100, StartAng, EndAng);

	AcDbBlockTable *pBlockTable = NULL;
	ErrorStatus es = acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForWrite);

	AcDbBlockTableRecord *pBlockTableRecord = NULL;
	es = pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord, AcDb::kForWrite);

	AcDbObjectId oid;
	es = pBlockTableRecord->appendAcDbEntity(oid, Acr);

	Acr->close();
	pBlockTableRecord->close();
	pBlockTable->close();

	CString msg;
	msg.Format(L"生成圆心(%lf,%lf)的圆弧 \n", ptCenterPoint.x, ptCenterPoint.y);
	acutPrintf(msg);
}

void CCreateEntity::CreateLine(AcGePoint3d ptStart, AcGePoint3d ptEnd)
{
	CString msg;
	msg.Format(L"起点:(%f，%f)\n", ptStart.x, ptStart.y);
	acutPrintf(msg);

	AcDbLine *pLine = new AcDbLine(ptStart, ptEnd);
	AcDbBlockTable *pBlockTable = NULL;
	acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForRead);
	AcDbBlockTableRecord *pBlockTableRecord;
	pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord, AcDb::kForWrite); //模型空间就是一个块表记录
	AcDbObjectId lineId;
	pBlockTableRecord->appendAcDbEntity(lineId, pLine);
	pBlockTable->close();
	pBlockTableRecord->close();
	pLine->close();

	msg.Format(L"终点:(%f，%f)\n", ptEnd.x, ptEnd.y);
	acutPrintf(msg);
}
