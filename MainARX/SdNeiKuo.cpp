#include "StdAfx.h"
#include "SdNeiKuo.h"
#include "CCreateEntity.h"
#include "EditorDlg.h"
#include <dbdim.h>
#include <acedCmdNF.h>
#include <iostream>
#include <objectarxutilslib.h>

Tunnel Tunnel::m_Sd;

Tunnel::Tunnel()
{
}

Tunnel::~Tunnel()
{
}

BOOL Tunnel::Read(CStdioFile *pFile)
{
	return 0;
}

BOOL Tunnel::Write(CStdioFile *pFile)
{
	return TRUE;
}

SdNeiKuo::SdNeiKuo()
{
}

SdNeiKuo::~SdNeiKuo()
{
}

SdNeiKuo &SdNeiKuo::operator=(const SdNeiKuo &data)
{
	Version = data.Version;
	R1 = data.R1;
	R2 = data.R2;
	R3 = data.R3;
	R4 = data.R4;
	R5 = data.R5;
	H1 = data.H1;
	H2 = data.H2;
	H_2 = data.H_2;
	ANGLE1 = data.ANGLE1;
	ANGLE_1 = data.ANGLE_1;
	ANGLE2 = data.ANGLE2;
	ANGLE3 = data.ANGLE3;
	ANGLE4 = data.ANGLE4;
	ANGLE5 = data.ANGLE5;
	return *this;
}

BOOL SdNeiKuo::Read(CString filePath, SdNeiKuo *pData)
{
	FILE *file;
	CStringA stra(filePath.GetBuffer(0));
	std::string path = stra.GetBuffer(0);
	stra.ReleaseBuffer();
	int errorCode = fopen_s(&file, path.c_str(), "r");
	if (!errorCode) {
		double *resultData = new double[20];
		for (int index = 0; index <= 14; index++) {
			fscanf_s(file, "%lf", &resultData[index]);
		}
		fclose(file);
		Version = *resultData;
		R1 = *(resultData + 1);
		R2 = *(resultData + 2);
		R3 = *(resultData + 3);
		R4 = *(resultData + 4);
		R5 = *(resultData + 5);
		H1 = *(resultData + 6);
		H2 = *(resultData + 7);
		H_2 = *(resultData + 8);
		ANGLE1 = *(resultData + 9);
		ANGLE_1 = *(resultData + 10);
		ANGLE2 = *(resultData + 11);
		ANGLE3 = *(resultData + 12);
		ANGLE4 = *(resultData + 13);
		ANGLE5 = *(resultData + 14);
		if (pData == NULL) {
			CEditorDlg readDlg;
			readDlg.m_Data = *this;
			readDlg.DoModal();
		} else {
			*pData = *this;
		}
		return TRUE;
	}
	return FALSE;
}

BOOL SdNeiKuo::Modify(CString filePath)
{
	CEditorDlg modifyDlg;
	Read(filePath, this);
	modifyDlg.m_Data = *this;
	if (modifyDlg.DoModal() == IDOK) {
		CStdioFile pFile;
		pFile.Open(filePath, CFile::modeWrite);
		*this = modifyDlg.m_Data;
		CString str;
		str.Format(L"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", VERSION, R1, R2, R3, R4, R5,
			   H1, H2, H_2, ANGLE1, ANGLE_1, ANGLE2, ANGLE3, ANGLE4, ANGLE5);
		pFile.Seek(0, CStdioFile::begin);
		pFile.WriteString(str);
		pFile.Close();
		AfxMessageBox(L"保存成功", MB_OK | MB_ICONINFORMATION);
		return TRUE;
	}
	return FALSE;
}

BOOL SdNeiKuo::Write(CStdioFile *pFile)
{
	CEditorDlg writeDlg;
	if (writeDlg.DoModal() == IDOK) {
		*this = writeDlg.m_Data;
		//写入文件
		CString str;
		str.Format(L"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", VERSION, R1, R2, R3, R4, R5,
			   H1, H2, H_2, ANGLE1, ANGLE_1, ANGLE2, ANGLE3, ANGLE4, ANGLE5);
		pFile->Seek(0, CStdioFile::end);
		pFile->WriteString(str);
		pFile->Close();
		AfxMessageBox(L"保存成功", MB_OK | MB_ICONINFORMATION);
		return TRUE;
	}
	return false;
}

BOOL Draw_Tunnel::Draw()
{
	Draw_SdNeiKuo TmpDraw;
	TmpDraw.m_data = m_data.m_nk;
	TmpDraw.Draw();

	return FALSE;
}

BOOL Draw_SdNeiKuo::Draw()
{
	AcGePoint3d ptStart;
	AcGePoint3d ptEnd;
	AcGePoint3d ptCenter;
	ads_real radius, x, y, startDegree, endDegree;

	//添加新图层
	CLayerUtil::add(L"起拱线", L"DASHED", CEntityUtil::Blue);
	CLayerUtil::add(L"中心线", L"CENTER", CEntityUtil::Color::Red);
	CLayerUtil::add(L"建筑限界", L"CENTER", CEntityUtil::Color::Red);
	CLayerUtil::add(L"标注", L"CONTINUOUS", CEntityUtil::Color::Green);

	// 起拱线
	AcDbObjectId layerId = CLayerUtil::GetLayerID(L"起拱线");
	ptStart.set(-m_data.R1, m_data.H1, 0);
	ptEnd.set(m_data.R1, m_data.H1, 0);
	//加载线型文件
	//acdbLoadLineTypeFile(_T("DASHED"), _T("ACADISO.LIN"), acdbHostApplicationServices()->workingDatabase());
	AcDbObjectId objId = CLineUtil::add(ptStart, ptEnd);
	CEntityUtil::setLayer(objId, L"起拱线");

	// 拱部
	ptCenter.set(0, m_data.H1, 0);
	radius = m_data.R1;
	objId = CArcUtil::add(ptCenter, m_data.R1, 0, 180, FALSE);
	//进行标注
	objId = CDimensionUtil::AddDimRadial(ptCenter, radius, CCalculation::GtoR(45));
	CEntityUtil::setLayer(objId, L"标注");

	//添加仰拱
	//左侧
	ptStart.set(-m_data.R1, m_data.H1, 0);
	ptCenter.set(m_data.R1, m_data.H1, 0);
	radius = ptStart.distanceTo(ptCenter);
	startDegree = CCalculation::GtoR(180.0);
	endDegree = CCalculation::GtoR(180.0 + m_data.ANGLE1);
	AcDbArc *leftArc = new AcDbArc(ptCenter, radius, startDegree, endDegree);
	CDwgDatebaseUtil::PostToModelSpace(leftArc);
	leftArc->close();
	//添加标注
	objId = CDimensionUtil::AddDimRadial(ptCenter, radius, (startDegree + endDegree) / 2.0);
	CEntityUtil::setLayer(objId, L"标注");

	//右侧
	ptCenter.set(-m_data.R1, m_data.H1, 0);
	startDegree = CCalculation::GtoR(-m_data.ANGLE1);
	endDegree = CCalculation::GtoR(0);
	AcDbArc *rightArc = new AcDbArc(ptCenter, radius, startDegree, endDegree);
	CDwgDatebaseUtil::PostToModelSpace(rightArc);
	rightArc->close();

	//绘制R3
	//获取R3的起点
	AcGePoint3dArray snapPoints;
	AcDbIntArray geomIds;
	rightArc->getOsnapPoints(OsnapMode::kOsModeEnd, 0, ptCenter, ptCenter, AcGeMatrix3d::kIdentity, snapPoints,
				 geomIds);
	radius = m_data.R3;
	x = snapPoints[0].x;
	y = snapPoints[0].y;
	ptStart.set(x, y, 0);
	ptCenter.set(x - radius, y, 0);
	startDegree = CCalculation::GtoR(0 - m_data.ANGLE3);
	endDegree = CCalculation::GtoR(0);
	//R3
	AcDbArc *pR3Arc = new AcDbArc(ptCenter, radius, startDegree, endDegree);
	CDwgDatebaseUtil::PostToModelSpace(pR3Arc);
	pR3Arc->close();
	objId = CDimensionUtil::AddDimRadial(ptCenter, radius, (startDegree + endDegree) / 2.0);
	CEntityUtil::setLayer(objId, L"标注");

	//绘制R4
	if (!snapPoints.isEmpty()) {
		snapPoints.removeAll();
	}
	pR3Arc->getOsnapPoints(OsnapMode::kOsModeEnd, 1, ptCenter, ptCenter, AcGeMatrix3d::kIdentity, snapPoints,
			       geomIds);
	x = snapPoints[0].x;
	y = snapPoints[0].y;
	radius = m_data.R4;
	//acutPrintf(L"端点：(%lf,%lf) \n", x, y);
	ptCenter = CCalculation::Pt2dTo3d(CCircleUtil::getPoint(AcGePoint2d(x, y), radius, 90.0 - m_data.ANGLE2));
	//acutPrintf(L"圆心：(%lf,%lf) \n", ptCenter.x, ptCenter.y);
	startDegree = CCalculation::GtoR(0.0 - 90.0);
	endDegree = CCalculation::GtoR(0.0 - 90.0 + m_data.ANGLE2);
	AcDbArc *pR4Arc = new AcDbArc(ptCenter, radius, startDegree, endDegree);
	//CArcUtil::add(ptCenter, radius, 0.0 - 90.0, 0.0 - 90.0 + m_data.ANGLE2);
	CDwgDatebaseUtil::PostToModelSpace(pR4Arc);
	pR4Arc->close();
	objId = CDimensionUtil::AddDimRadial(ptCenter, radius, (startDegree + endDegree) / 2.0);
	CEntityUtil::setLayer(objId, L"标注");

	// 路面
	ptStart.set(-m_data.R1, 0, 0);
	ptEnd.set(m_data.R1, 0, 0);
	AcDbLine *pRoadLine = new AcDbLine(ptStart, ptEnd);
	if (!snapPoints.isEmpty()) {
		snapPoints.removeAll();
	}
	pRoadLine->intersectWith(leftArc, kExtendThis, snapPoints);
	x = snapPoints[0].x, y = snapPoints[0].y;
	pRoadLine->setStartPoint(AcGePoint3d(-x, y, 0));
	pRoadLine->setEndPoint(AcGePoint3d(x, y, 0));
	//把直线实体添加到模型空间
	CDwgDatebaseUtil::PostToModelSpace(pRoadLine);
	pRoadLine->close();

	//绘制中心线
	layerId = CLayerUtil::GetLayerID(L"中心线");
	AcDbLine *centerLine = new AcDbLine;
	if (!snapPoints.isEmpty()) {
		snapPoints.removeAll();
	}
	//
	pR4Arc->getOsnapPoints(OsnapMode::kOsModeEnd, 1, ptCenter, ptCenter, AcGeMatrix3d::kIdentity, snapPoints,
			       geomIds);
	x = snapPoints[0].x, y = snapPoints[0].y - 20;
	centerLine->setStartPoint(AcGePoint3d(x, y, 0));
	y = ptCenter.y;
	centerLine->setEndPoint(AcGePoint3d(x, y, 0));
	CDwgDatebaseUtil::PostToModelSpace(centerLine);
	centerLine->close();
	CEntityUtil::setLayer(centerLine->id(), L"中心线");
	CEntityUtil::setColor(centerLine->id(), CEntityUtil::Color::Red);
	ptStart.set(-6, 36, 0);
	CTextUtil::addText(ptStart, L"隧道中心线", AcDbObjectId::kNull, 7.5, CCalculation::GtoR(90));

	return true;
}

BOOL SdProp::Read(CStdioFile *pFile)
{
	return 0;
}

BOOL SdProp::Write(CStdioFile *pFile)
{
	return FALSE;
}

BOOL SdProp::Modify()
{
	return FALSE;
}
