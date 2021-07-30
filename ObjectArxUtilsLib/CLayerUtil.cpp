#include "pch.h"
#include "CLayerUtil.h"
#include "CEntityUtil.h"

CLayerUtil::CLayerUtil()
{
}


CLayerUtil::~CLayerUtil()
{
}


void CLayerUtil::add(TCHAR* LayerName, TCHAR* lineType, int colorindex)
{
	assert(LayerName != NULL);
	AcDbLayerTable* pLayerTable = NULL;
	AcDbDatabase* pDatabase;
	pDatabase = acdbHostApplicationServices()->workingDatabase();
	pDatabase->getLayerTable(pLayerTable, AcDb::kForWrite);
	if (!pLayerTable->has(LayerName))
	{
		AcDbLayerTableRecord* pLayerTableRecord = new AcDbLayerTableRecord();
		pLayerTableRecord->setName(LayerName);
		if (colorindex >= 1 && colorindex <= 255)
		{
			AcCmColor color;
			color.setColorIndex(colorindex);
			pLayerTableRecord->setColor(color);
		}
		if (lineType != NULL)
		{
			AcDbLinetypeTable* pLinetypeTbl;
			AcDbObjectId layerId;
			//加载线型文件
			acdbLoadLineTypeFile(lineType, _T("acadiso.lin"), pDatabase);
			pLinetypeTbl = new AcDbLinetypeTable;
			pDatabase->getLinetypeTable(pLinetypeTbl, AcDb::kForRead);
			pLinetypeTbl->getAt(lineType, layerId);
			pLayerTableRecord->setLinetypeObjectId(layerId);
			pLinetypeTbl->close();

		}
		pLayerTable->add(pLayerTableRecord);
		pLayerTableRecord->close();
	}
	pLayerTable->close();
}

AcDbObjectId CLayerUtil::GetLayerID(TCHAR* LayerName)
{
	assert(LayerName);
	AcDbLayerTable* pLayerTable = NULL;
	acdbHostApplicationServices()->workingDatabase()->getLayerTable(pLayerTable);
	AcDbObjectId Layerid = AcDbObjectId::kNull;
	if (pLayerTable->has(LayerName))
	{
		pLayerTable->getAt(LayerName, Layerid);
	}
	pLayerTable->close();
	return Layerid;
}

bool CLayerUtil::SetLayerColor(TCHAR* layerName, int colorindex)
{
	bool result = false;
	AcDbObjectId layerid = GetLayerID(layerName);

	AcDbLayerTableRecord* pLayerTableRecord = NULL;
	if (acdbOpenObject(pLayerTableRecord, layerid, AcDb::kForWrite) == Acad::eOk)
	{
		AcCmColor color;
		color.setColorIndex(colorindex);
		pLayerTableRecord->setColor(color);
		result = true;
		pLayerTableRecord->close();
	}
	return result;
}

void CLayerUtil::GetAllLayerIDList(AcDbObjectIdArray& layerids)
{
	AcDbLayerTable* pLayerTable = NULL;
	acdbHostApplicationServices()->workingDatabase()->getLayerTable(pLayerTable);
	AcDbLayerTableIterator* it;
	pLayerTable->newIterator(it);
	for (it->start(); !it->done(); it->step())
	{
		AcDbLayerTableRecord* pLayerTableRecord = NULL;
		if (it->getRecord(pLayerTableRecord) == Acad::eOk)
		{
			layerids.append(pLayerTableRecord->objectId());
			pLayerTableRecord->close();
		}
	}
	delete it;
	pLayerTable->close();
}

void CLayerUtil::DeleteLayer(TCHAR* LayerName)
{
	AcDbObjectId Layerid = GetLayerID(LayerName);
	AcDbLayerTableRecord* pLayerRecord = NULL;
	if (acdbOpenObject(pLayerRecord, Layerid, AcDb::kForWrite) == Acad::eOk)
	{
		pLayerRecord->erase();
		pLayerRecord->close();
	}
}
