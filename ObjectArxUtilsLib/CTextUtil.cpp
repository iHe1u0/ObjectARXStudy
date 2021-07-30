#include "pch.h"
#include "CTextUtil.h"
#include "CDwgDatebaseUtil.h"

CTextUtil::CTextUtil()
{
}


CTextUtil::~CTextUtil()
{
}

AcDbObjectId CTextUtil::addText(const AcGePoint3d & InsertPoint, const TCHAR * text, AcDbObjectId style, double height, double rotation)
{
	AcDbText *pText = new AcDbText(InsertPoint, text, style, height, rotation);

	return CDwgDatebaseUtil::PostToModelSpace(pText);
}

AcDbObjectId CTextUtil::addMText(const AcGePoint3d & InsertPoint, const TCHAR * text, AcDbObjectId style, double height, double width)
{
	AcDbMText *pMText = new AcDbMText();
	pMText->setLocation(InsertPoint);
	pMText->setTextStyle(style);
	pMText->setContents(text);
	pMText->setHeight(height);
	pMText->setWidth(width);

	return CDwgDatebaseUtil::PostToModelSpace(pMText);
}
