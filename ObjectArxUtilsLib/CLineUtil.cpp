#include "pch.h"
#include "CLineUtil.h"
#include "CDwgDatebaseUtil.h"


CLineUtil::CLineUtil()
{
}


CLineUtil::~CLineUtil()
{
}

AcDbObjectId CLineUtil::add(const AcGePoint3d& pStartPoint, const AcGePoint3d& pEndPoint)
{
	return add(pStartPoint, pEndPoint, NULL);
}

AcDbObjectId CLineUtil::add(const AcGePoint3d& pStartPoint, const AcGePoint3d& pEndPoint, TCHAR* lineType)
{
	//创建直线实体
	AcDbLine* pLine = new AcDbLine(pStartPoint, pEndPoint);
	//acedAlert(lineType);
	if (lineType != NULL)
	{
		pLine->setLinetype(lineType);
	}
	//把直线实体添加到模型空间
	return CDwgDatebaseUtil::PostToModelSpace(pLine);
}

