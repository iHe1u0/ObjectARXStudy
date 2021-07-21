#include "stdafx.h"
#include "CCreateEntity.h"
#include <CLineUtil.h>
#include <CArcUtil.h>


//"起点，圆心，圆弧角度"创建圆弧
Acad::ErrorStatus CCreateEntity::CreateArc(AcGePoint2d ptStartPoint, AcGePoint2d ptEndPoint, AcGePoint2d ptCenterPoint)
{
	CString msg;
	msg.Format(L"生成圆心(%lf,%lf)的圆弧 \n", ptCenterPoint.x, ptCenterPoint.y);
	acutPrintf(msg);

	CArcUtil::addArc(ptStartPoint, ptCenterPoint, ptEndPoint);
	return Acad::eOk;
}

Acad::ErrorStatus CCreateEntity::CreateLine(AcGePoint3d ptStart, AcGePoint3d ptEnd)
{
	CString msg;
	msg.Format(L"起点:(%f，%f)\n", ptStart.x, ptStart.y);
	acutPrintf(msg);

	CLineUtil::add(ptStart, ptEnd);

	msg.Format(L"终点:(%f，%f)\n", ptEnd.x, ptEnd.y);
	acutPrintf(msg);

	return Acad::eOk;

}

Acad::ErrorStatus CCreateEntity::CreateLayer(const TCHAR *layerName, AcDbObjectId &layerId)
{
	Acad::ErrorStatus errorStatus;
	AcDbDatabase *db = acdbHostApplicationServices()->workingDatabase();

	AcDbSymbolTable *layerTbl = NULL;
	errorStatus = db->getLayerTable(layerTbl, AcDb::kForRead);
	if (errorStatus != Acad::eOk) {
		acutPrintf(_T("\nCommand internal error: getLayerTable() = %d"), errorStatus);
		return errorStatus;
	}

	errorStatus = layerTbl->getAt(layerName, layerId);
	if (errorStatus == Acad::eOk) {
		layerTbl->close();
		acutPrintf(_T("\nFound layer <%s>: %d-%d"), layerName, layerId.handle().high(), layerId.handle().low());
		return Acad::eOk;
	}

	acutPrintf(_T("\nupgrading opened table for writing"));
	errorStatus = layerTbl->upgradeOpen();
	if ((errorStatus != Acad::eOk) && (errorStatus != Acad::eWasOpenForWrite)) {
		acutPrintf(_T("\nCommand internal error: upgradeOpen() = %d"), errorStatus);
		layerTbl->close();
		return errorStatus;
	}
	AcDbLayerTableRecord *pLayerTableRecord = new AcDbLayerTableRecord();
	//set layer name
	pLayerTableRecord->setName(layerName);
	//set color
	pLayerTableRecord->setLineWeight(AcDb::LineWeight::kLnWt035);
	errorStatus = static_cast<AcDbLayerTable *>(layerTbl)->add(layerId, pLayerTableRecord);
	if (errorStatus != Acad::eOk) {
		acutPrintf(_T("\nCommand internal error: add() = %d"), errorStatus);
		layerTbl->close();
		return errorStatus;
	}
	acutPrintf(_T("\nCreated layer <%s>: %d-%d"), layerName, layerId.handle().high(), layerId.handle().low());

	pLayerTableRecord->close();
	layerTbl->close();

	return Acad::eOk;
}
